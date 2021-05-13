//
//  objcpp_stack_int.mm
//  StackTest-ObjCPP
//
//  Created by Gemuele Aludino on 5/12/21.
//

#import "objcpp_stack_int.h"
#import <Foundation/Foundation.h>

#include "cpp_stack_int.hpp"

@interface StackInt() {
    cpp::stack _impl;
}
@end

@implementation StackInt

- (instancetype)init:(size_t)capacity {
    if (self == [super init]) {
        auto s = cpp::stack(capacity);
        _impl = std::move(s);
    }
    
    return self;
}

- (instancetype)deinit {
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
