//
//  objcpp_stack_int.h
//  Swift_Language-Interop
//
//  Created by Gemuele Aludino on 5/12/21.
//

#ifndef OBJCPP_STACK_INT_H
#define OBJCPP_STACK_INT_H

#import <Foundation/Foundation.h>

@interface StackInt : NSObject

- (instancetype)init;
- (instancetype)init:(size_t)capacity;
- (instancetype)initCopy:(StackInt *)s;
- (instancetype)initMove:(StackInt *)s;

@property (readonly) int top;
@property (readonly) BOOL empty;

@end

@interface StackInt (StackOperations)

- (void)push:(int)val;
- (void)pop;

- (void)clear;

@end

#endif /* OBJCPP_STACK_INT_H */
