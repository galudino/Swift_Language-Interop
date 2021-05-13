#  Swift Language Interoperability Tests

This Xcode project demonstrates how to call C, Objective-C, and Objective-C++ code from within Swift.

Tested on macOS Big Sur 11.3.1 with Xcode 12.5.

# Table of contents
  * [Targets](#targets)
  * [Main points](#main-points)
    + [The bridging header file](#the-bridging-header-file)
      - [Creating the bridging header yourself](#creating-the-bridging-header-yourself)
      - [Configuring your Xcode project](#configuring-your-xcode-project)
    + [Language compatibility](#language-compatibility)
      - [C and Objective-C](#c-and-objective-c)
      - [Cpp](#cpp)
  * [Usage of bridged code](#usage-of-bridged-code)
    + [C](#c)
    + [Objective-C](#objective-c)
    + [Objective-Cpp](#objective-cpp)

## Targets

We have three (3) separate examples/targets -- 
each target contains a Swift client source file (`main.swift`)
that demonstrates the usage of a stack data structure of `int` (`StackInt`)

- StackTest-C: a `StackInt` (`typedef struct stack StackInt`) type
  written in C, with procedural code acting upon instances of
  `StackInt`. This target demonstrates the invocation of C code from
  within Swift.

- StackTest-ObjC: a `StackInt` class written in Objective-C. This target
  demonstrates the invocation of Objective-C code from within Swift.

- StackTest-ObjCPP: a `class stack` type written in C++, wrapped in an
  Objective-C++ class, named `StackInt`. This target demonstrates the
  invocation of Objective-C++ code from within Swift.

Each `main.swift` does the following:
- Creates and initializes a `StackInt` s of size 1
- Push elements [10, 9, 8, ... 1] to s
- While the stack isn't empty, peek/print the stack top, then pop s.

## Main points

### The bridging header file

Calling C, Objective-C, and Objective-C++ code requires the use of the bridging header file.

If you use Xcode to create a new `.c`, `.cpp`, or `.m` file -- 
Xcode will automatically ask you if you want a bridging header
created for you. Say yes -- it will then be configured for your target.
This is the easiest way to have a bridging header configured for your target.

C and Objective-C code will work natively with Swift, once a bridging header is configured.
C++ code must be wrapped in an Objective-C API, requiring Objective-C++.

If you want to know how to create/configure the bridging header on your own, read below:

#### Creating the bridging header yourself
Let's say you have a C header, named `c_stack_int.h`.
It contains a `struct` definition for a stack of `int`'s, as well as forward-declarations of functions
to use with instances of that `struct`.

You will need to create a bridging header file to use the declarations in `c_stack_int.h`.
(For this example, we'll call this bridging header `StackTest-C-Bridging-Header.h` -- but it can be any name you'd like)

The contents of `StackTest-C-Bridging-Header.h`, should contain the following:

```objc
#import "c_stack_int.h"
```

Any other headers you would like to use in your Swift project should be `#import`ed here as well.

#### Configuring your Xcode project
On the left hand side of your Xcode window, left-click the project icon. (The blue Xcode project icon).
Then, to the center-left of the screen, under 'TARGETS', choose the desired target.

Next, click the 'Build Settings' tab. In the search bar on the right-hand side, type 'Bridging Header'.
You will see the 'Objective-C Bridging Header' box.

Type the relative path of your bridging header in the box. For this project/target, the path provided is:
`StackTest-C/StackTest-C-Bridging-Header.h`.

### Language compatibility
#### C and Objective-C

C code and Objective-C classes can be called directly from within Swift.

Once you have configured a bridging header for your Xcode project,
and the bridging header `#import`s your API's header file,
you are now able to call your C/Objective-C code from within Swift.

#### Cpp

C++ classes must be wrapped inside an Objective-C class.

Source code using both the C++ and Objective-C languages must be stored in a (`.mm`) file.
This denotes that the source is Objective-C++.

Summary:
- Configure your bridging header. Insure that it imports the Objective-C header you intend to use.
- Write your Objective-C header (`.h`). This header should not contain any C++ code.
- Prepare the C++ files (header `.hpp`, source `.cpp`) for the class you will wrap.
- Write your Objective-C++ source file (`.mm`). Now you may use C++ and Objective-C code together.
    - You may `#include` any C++ headers you require, including the `.hpp` file for your C++ class.
    - Store a 'private' field for your C++ class by creating a class extension.
    - When implementing the Objective-C wrapper methods, call your C++ member functions through the 'private' field.  

Described below is the process of wrapping a C++ class in an Objective-C API.

Below is the contents of our bridging header, `StackTest-ObjCPP-Bridging-Header.h`.
We import our Objective-C header file for our `StackInt` type here.

```objc
#import "objcpp_stack_int.h"
```

Here is the Objective-C header file for `StackInt`, `objcpp_stack_int.h`.

Notice that we have not introduced any C++ code in this header file --
the implementation details of this class will invoke C++ code.

```objc
#ifndef OBJCPP_STACK_INT_H
#define OBJCPP_STACK_INT_H

#import <Foundation/Foundation.h>

@interface StackInt : NSObject

- (id)init:(size_t)capacity;
- (id)deinit;

- (void)push:(int)val;
- (void)pop;

- (int)top;
- (BOOL)empty;

- (void)clear;

@end

#endif /* OBJCPP_STACK_INT_H */
```

Below is the Objective-C source file for `StackInt`, `objcpp_stack_int.mm`.

Notice the `.mm` extension -- this denotes that we are dealing with
an Objective-C++ source file, as opposed to an Objective-C source file,
which has a `.m` extension.

In this `.mm` file, we are able to use C++ code/libraries.
We `#include "cpp_stack_int.hpp"`, in addition to `#import "objcpp_stack_int.h"`.
(`#include` is used for C and C++ headers, `#import` is used for Objective-C headers)

`stack` is our C++ class, `_impl` is a field within a class extension for StackInt.
This class extension (and any fields/properties/methods within it) will not be accessible
in the public interface -- our `_impl` field is effectively 'private'.

We use the `_impl` field to invoke `stack`'s member functions.

```objc
#import "objcpp_stack_int.h"

#include "cpp_stack_int.hpp"

@interface StackInt() {
    stack _impl;
}
@end

@implementation StackInt

- (id)init:(size_t)capacity {
    if (self == [super init]) {
        auto s = stack(capacity);
        _impl = std::move(s);
    }
    
    return self;
}

- (id)deinit {
    return self;
}

- (void)push:(int)val {
    _impl.push(val);
}

- (void)pop {
    _impl.pop();
}

- (int)top {
    return _impl.top();
}

- (BOOL)empty {
    return _impl.empty();
}

- (void)clear {
    return _impl.clear();
}

@end

```

Our C++ header file, `cpp_stack_int.hpp`, is vanilla C++:

```cpp
#ifndef CPP_STACK_INT_HPP
#define CPP_STACK_INT_HPP

#include <cstddef>

class stack {
public:
    stack() = default;
    
    stack(size_t capacity);
    
    stack(const stack &s);
    stack(stack &&s);
    
    ~stack() {
        delete m_start;
        m_start = m_finish = m_end_of_storage = nullptr;
    }
    
    void push(int val);
    
    void pop() {
        if (m_finish > m_start) {
            --m_finish;
        }
    }
    
    int top() const { return *(m_finish - 1); }
    bool empty() const { return m_finish == m_start; }
    
    void clear();
    
    stack &operator=(const stack &s);
    stack &operator=(stack &&s);
private:
    static constexpr auto DEFAULT_CAPACITY = 16;
    
    size_t capacity() const {
        return m_end_of_storage - m_start;
    }
    
    size_t size() const {
        return m_finish - m_start;
    }
    
    void resize(size_t old_capacity, size_t new_capacity);
    
    int *m_start;
    int *m_finish;
    int *m_end_of_storage;
};


#endif /* CPP_STACK_INT_HPP */
```

Same with our `cpp_stack_int.cpp` source file:

```cpp
#include "cpp_stack_int.hpp"

#include <memory>
#include <algorithm>
#include <iostream>

stack::stack(size_t capacity) {
    auto *start = new int[capacity];
    
    m_start = m_finish = start;
    m_end_of_storage = start + capacity;
}

stack::stack(const stack &s) {
    auto *start = new int[s.capacity()];
    
    std::copy(s.m_start, s.m_finish, start);
    
    m_finish = m_start + s.size();
    m_end_of_storage = m_start + s.capacity();
}

stack::stack(stack &&s) :
    m_start(std::exchange(s.m_start, nullptr)),
    m_finish(m_start + s.size()),
    m_end_of_storage(m_start + s.capacity()) {

}

void stack::push(int val) {
    if (!m_start) {
        auto *start = new int[DEFAULT_CAPACITY];
        
        m_start = m_finish = start;
        m_end_of_storage = start + DEFAULT_CAPACITY;
    }
    
    if (size() == capacity()) {
        resize(capacity(), capacity() * 2);
    }
    
    *(m_finish++) = val;
}

void stack::clear() {
    std::fill(m_start, m_finish, 0);
    m_finish = m_start;
}

stack &stack::operator=(const stack &s) {
    auto *new_start = new int[s.capacity()];
    
    delete m_start;
    
    std::copy(s.m_start, s.m_finish, new_start);
    
    m_start = new_start;
    return *this;
}

stack &stack::operator=(stack &&s) {
    m_start = std::exchange(s.m_start, nullptr);
    m_finish = std::exchange(s.m_finish, nullptr);
    m_end_of_storage = std::exchange(s.m_end_of_storage, nullptr);
    
    return *this;
}

void stack::resize(size_t old_capacity, size_t new_capacity) {
    if (old_capacity == new_capacity) { return; }
    
    auto *new_start = new int[new_capacity];
    delete m_start;
    
    if (old_capacity < new_capacity) {
        std::copy(m_start, m_finish, new_start);
        
        m_start = new_start;
        m_finish = m_start + old_capacity;
        m_end_of_storage = m_start + new_capacity;
    } else {
        std::copy(m_start, m_start + new_capacity, new_start);
        
        m_start = new_start;
        m_finish = m_end_of_storage = m_start + new_capacity;
    }
}
```

## Usage of bridged code

### C
```swift
func useCStack() {
    // Declare a StackInt
    var s = StackInt();
    
    // Initialize the stack to a capacity of 1
    StackInt_init(&s, 1)
    
    // Push integers 10, 9, 8 ... 1 to the stack
    for i: Int32 in (1...10).reversed() {
        StackInt_push(&s, i)
    }
    
    // For all stack members,
    // peek the stack top, print the element, then pop it off
    while !StackInt_empty(&s) {
        let n = StackInt_top(&s)
        print("[useCStack] stack_int just popped: \(n)")
        
        StackInt_pop(&s)
    }
}

useCStack()
```

### Objective-C
```swift
func useObjCStack() {
    // Declare a StackInt
    // Initialize the stack to a capacity of 1
    let s: StackInt = StackInt(1)

    // Push integers 10, 9, 8 ... 1 to the stack
    for i: Int32 in (1...10).reversed() {
        s.push(i)
    }
    
    // For all stack members,
    // peek the stack top, print the element, then pop it off
    while !s.empty() {
        let n = s.top()
        print("[useObjCStack] StackInt just popped: \(n)")
        
        s.pop()
    }
}

useObjCStack()
```

### Objective-Cpp
```swift
func useObjCPPStack() {
    // Declare a StackInt
    // Initialize the stack to a capacity of 1
    let s: StackInt = StackInt(1)
    
    // Push integers 10, 9, 8 ... 1 to the stack
    for i: Int32 in (1...10).reversed() {
        s.push(i)
    }
    
    // For all stack members,
    // peek the stack top, print the element, then pop it off
    while !s.empty() {
        let n = s.top()
        print("[useObjCPPStack] StackInt just popped: \(n)")
        
        s.pop()
    }
}

useObjCPPStack()
```
