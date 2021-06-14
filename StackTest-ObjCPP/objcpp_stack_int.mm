//
//  objcpp_stack_int.mm
//  StackTest-ObjCPP
//
//  Created by Gemuele Aludino on 5/12/21.
//

#import "objcpp_stack_int.h"
#import <Foundation/Foundation.h>

#include "cpp_stack_int.hpp"

@implementation StackInt {
    cpp::stack _impl;
}

- (instancetype)init {
    if (self == [super init]) {

    }

    return self;
}

- (instancetype)init:(size_t)capacity {
    if (self == [super init]) {
        _impl = cpp::stack(capacity);
    }
    
    return self;
}

- (instancetype)initCopy:(StackInt *)s {
    if (self == [super init]) {
        _impl = cpp::stack(s->_impl);
    }
    
    return self;
}

- (instancetype)initMove:(StackInt *)s {
    if (self == [super init]) {
        _impl = cpp::stack(std::move(s->_impl));
    }
    
    return self;
}

- (int)top {
    return _impl.top();
}

- (BOOL)empty {
    return _impl.empty();
}

@end


@implementation StackInt (StackOperations)

- (void)push:(int)val {
    _impl.push(val);
}

- (void)pop {
    _impl.pop();
}

- (void)clear {
    return _impl.clear();
}

@end
