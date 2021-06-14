//
//  objc_stack_int.h
//  Swift_Language-Interop
//
//  Created by Gemuele Aludino on 5/12/21.
//

#ifndef OBJC_STACK_INT_H
#define OBJC_STACK_INT_H

#include <stdint.h>
#import <Foundation/Foundation.h>

@interface StackInt : NSObject

- (instancetype)init;
- (instancetype)init:(size_t)capacity;
- (instancetype)initCopy:(const StackInt *const)s;
- (instancetype)initMove:(StackInt *const)s;
- (instancetype)deinit;

- (instancetype)assignCopy:(const StackInt *const)s;
- (instancetype)assignMove:(StackInt *const)s;

@property (readonly) int top;
@property (readonly) BOOL empty;

@end

@interface StackInt (StackOperations)

- (void)push:(int)val;
- (void)pop;

- (void)clear;

@end

#endif /* OBJC_STACK_INT_H */
