//
//  objc_stack_int.m
//  StackTest-ObjC
//
//  Created by Gemuele Aludino on 5/12/21.
//

#include <stdint.h>

#import "objc_stack_int.h"

#import <Foundation/Foundation.h>

@interface StackInt()

@property (readonly) size_t capacity;
@property (readonly) size_t size;

- (void)resizeFromOldCapacity:(size_t)oldCapacity toNewCapacity:(size_t)newCapacity;

@end

@implementation StackInt

- (id)init:(size_t)capacity {
    if (self == [super init]) {
        int *start = calloc(capacity, sizeof *start);
        assert(start);
        
        m_start = m_finish = start;
        m_end_of_storage = start + capacity;
    }
    
    return self;
}

- (id)deinit {
    free(m_start);
    m_start = m_finish = m_end_of_storage = (int *)(0);
    
    return self;
}

- (void)push:(int)val {
    if (self.size == self.capacity) {
        [self resizeFromOldCapacity:self.capacity toNewCapacity:self.capacity * 2];
    }
    
    *(m_finish++) = val;
}

- (void)pop {
    if (m_finish > m_start) {
        --m_finish;
    }
}

- (int)top {
    return *(m_finish - 1);
}

- (BOOL)empty {
    return m_finish == m_start;
}

- (void)clear {
    memset(m_start, 0, self.capacity);
    m_finish = m_start;
}

- (size_t)capacity {
    return m_end_of_storage - m_start;
}

- (size_t)size {
    return m_finish - m_start;
}

- (void)resizeFromOldCapacity:(size_t)oldCapacity toNewCapacity:(size_t)newCapacity {
    if (oldCapacity == newCapacity) { return; }
    
    int *new_start = realloc(m_start, sizeof *m_start * newCapacity);
    
    assert(new_start);
    
    m_start = new_start;
    m_finish = oldCapacity < newCapacity ? new_start + oldCapacity : new_start + newCapacity;
    m_finish = new_start + newCapacity;
}

@end
