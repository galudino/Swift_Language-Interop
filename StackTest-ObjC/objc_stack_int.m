//
//  objc_stack_int.m
//  StackTest-ObjC
//
//  Created by Gemuele Aludino on 5/12/21.
//

#include <stdint.h>

#import "objc_stack_int.h"
#import <Foundation/Foundation.h>

#define StackInt_DEFAULT_CAPACITY 2

@interface StackInt (PrivateFunctionality)

@property (readonly) size_t capacity;
@property (readonly) size_t size;

- (void)resizeFromOldCapacity:(size_t)oldCapacity toNewCapacity:(size_t)newCapacity;

@end

@implementation StackInt {
    int *m_start;
    int *m_finish;
    int *m_end_of_storage;
}

- (instancetype)init {
    if (self == [super init]) {
        int *start = calloc(StackInt_DEFAULT_CAPACITY, sizeof *start);
        assert(start);
        
        m_start = m_finish = start;
        m_end_of_storage = start + StackInt_DEFAULT_CAPACITY;
    }
    
    return self;
}

- (instancetype)init:(size_t)capacity {
    if (self == [super init]) {
        int *start = calloc(capacity, sizeof *start);
        assert(start);
        
        m_start = m_finish = start;
        m_end_of_storage = start + capacity;
    }
    
    return self;
}

- (instancetype)initCopy:(const StackInt *const)s {
    if (self == [super init]) {
        int *start = calloc(s.capacity, sizeof *s->m_start);
        assert(start);
        
        memcpy(start, s->m_start, sizeof *s->m_start * s.size);
        
        m_start = start;
        m_finish = start + s.size;
        m_end_of_storage = start + s.capacity;
    }
    
    return self;
}

- (instancetype)initMove:(StackInt *const)s {
    if (self == [super init]) {
        self->m_start = s->m_start;
        self->m_finish = s->m_finish;
        self->m_end_of_storage = s->m_end_of_storage;
        
        s->m_start = s->m_finish = s->m_end_of_storage = (int *)(0);
    }
    
    return self;
}

- (instancetype)deinit {
    free(m_start);
    m_start = m_finish = m_end_of_storage = (int *)(0);
    
    return self;
}

- (instancetype)assignCopy:(const StackInt *const)s {
    if (s != nil) {
        int *start = calloc(s.capacity, sizeof *s->m_start);
        assert(start);
        
        memcpy(start, s->m_start, sizeof *s->m_start * s.size);
        
        m_start = start;
        m_finish = start + s.size;
        m_end_of_storage = start + s.capacity;
    }
    
    return self;
}

- (instancetype)assignMove:(StackInt *const)s {
    if (s != nil) {
        m_start = s->m_start;
        m_finish = s->m_finish;
        m_end_of_storage = s->m_end_of_storage;
        
        s->m_start = s->m_finish = s->m_end_of_storage = (int *)(0);
    }
    return self;
}

- (int)top {
    return *(m_finish - 1);
}

- (BOOL)empty {
    return m_finish == m_start;
}

@end

@implementation StackInt (StackOperations)

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

- (void)clear {
    memset(m_start, 0, self.capacity);
    m_finish = m_start;
}

@end

@implementation StackInt (PrivateFunctionality)

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
    m_end_of_storage = new_start + newCapacity;
}

@end
