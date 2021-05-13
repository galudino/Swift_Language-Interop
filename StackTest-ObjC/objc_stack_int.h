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

@interface StackInt : NSObject {
    int *m_start;
    int *m_finish;
    int *m_end_of_storage;
}

- (instancetype)init:(size_t)capacity;
- (instancetype)deinit;

- (void)push:(int)val;
- (void)pop;

- (int)top;
- (BOOL)empty;

- (void)clear;

@end

#endif /* OBJC_STACK_INT_H */
