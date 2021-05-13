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
