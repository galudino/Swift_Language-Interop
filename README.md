#  Swift Language Interoperability Tests

This Xcode project demonstrates how to call C, Objective-C, and Objective-C++ code from within Swift.

We have three (3) separate examples/targets -- one for each programming language described above.
Each example features a `main.swift` client source file that calls `StackInt` data structure, written in one of the languages described above.

## Main points:

### The bridging header file

Calling C, Objective-C, and Objective-C++ code requires the use of the bridging header file.

If you use Xcode to create a new `.c`, `.cpp`, or `.m` file -- Xcode will automatically ask you if you want a bridging header
created for you. Say yes -- it will then be configured for your target.

C and Objective-C code will work natively with Swift, once a bridging header is configured.
C++ code must be wrapped in an Objective-C API, requiring Objective-C++.

If you want to know how to create/configure the bridging header on your own, read below:

#### Creating the bridging header
Let's say you have a C header, named `c_stack_int.h`.
It contains a `struct` definition for a stack of `int`'s, as well as forward-declarations of functions
to use with instances of that `struct`.

You will need to create a bridging header file to use the declarations in `c_stack_int.h`.
(For this example, we'll call this bridging header `StackTest-C-Bridging-Header.h` -- but it can be any name you'd like)

The contents of `StackTest-C-Bridging-Header.h`, should contain the following:

```c
#import "c_stack_int.h"
```

Any other C headers you would like to use in your Swift project should be `#import`ed here as well.

#### Configuring your Xcode project
On the left hand side of your Xcode window, left-click the project icon. (The blue Xcode project icon).
Then, to the center-left of the screen, under 'TARGETS', choose the desired target.

Next, click the 'Build Settings' tab. In the search bar on the right-hand side, type 'Bridging Header'.
You will see the 'Objective-C Bridging Header' box.

Type the relative path of your bridging header in the box. For this project/target, the path provided is:
`StackTest-C/StackTest-C-Bridging-Header.h`.

### C and Objective-C work natively from within Swift, C++ does not
In order to use a C++ class, it must be wrapped inside an Objective-C class.
See the provided examples in this project on how this works.


## Usage of bridged code (`main.swift` samples):

### C:
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

### Objective-C:
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

### Objective-C++:
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
