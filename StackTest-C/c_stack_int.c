//
//  c_stack_int.c
//  StackTest-C
//
//  Created by Gemuele Aludino on 5/12/21.
//

#include "c_stack_int.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define StackInt_DEFAULT_CAPACITY 16

static inline size_t StackInt_capacity(const StackInt *const self) {
    return self->m_end_of_storage - self->m_start;
}

static inline size_t StackInt_size(const StackInt *const self) {
    return self->m_finish - self->m_start;
}

static void StackInt_resize(StackInt *const self, size_t old_capacity, size_t new_capacity);

void StackInt_init(StackInt *const self, size_t capacity) {
    int *start = calloc(capacity, sizeof *start);
    assert(start);
    
    self->m_start = self->m_finish = start;
    self->m_end_of_storage = start + capacity;
}

void StackInt_initCopy(StackInt *const self, const StackInt *const s) {
    int *start = calloc(StackInt_capacity(s), sizeof *start);
    
    assert(start);
    
    memcpy(start, s->m_start, sizeof *s->m_start * StackInt_size(s));
    
    self->m_start = start;
    self->m_finish = start + StackInt_size(s);
    self->m_end_of_storage = start + StackInt_capacity(s);
}

void StackInt_initMove(StackInt *const self, StackInt *const s) {
    self->m_start = s->m_start;
    self->m_finish = s->m_finish;
    self->m_end_of_storage = s->m_end_of_storage;
    
    s->m_start = s->m_finish = s->m_end_of_storage = (int *)(0);
}

void StackInt_deinit(StackInt *const self) {
    free(self->m_start);
    self->m_start = self->m_finish = self->m_end_of_storage = (int *)(0);
}

void StackInt_push(StackInt *const self, int val) {
    if (!self->m_start) {
        int *start = calloc(StackInt_DEFAULT_CAPACITY, sizeof *start);
        
        self->m_start = self->m_finish = start;
        self->m_end_of_storage = start + StackInt_DEFAULT_CAPACITY;
    }
    
    if (StackInt_size(self) == StackInt_capacity(self)) {
        StackInt_resize(self, StackInt_capacity(self), StackInt_capacity(self) * 2);
    }
    
    *(self->m_finish++) = val;
}

void StackInt_clear(StackInt *const self) {
    memset(self->m_start, 0, StackInt_capacity(self));
    self->m_finish = self->m_start;
}

StackInt *StackInt_assignCopy(StackInt *const self, const StackInt *const s) {
    int *new_start = calloc(StackInt_capacity(s), sizeof *new_start);
    assert(new_start);
    
    free(s->m_start);
    
    memcpy(new_start, s->m_start, sizeof *s->m_start * StackInt_size(s));
    
    self->m_start = new_start;
    self->m_finish = new_start + StackInt_size(s);
    self->m_end_of_storage = self->m_start + StackInt_capacity(s);
    
    return self;
}

StackInt *StackInt_assignMove(StackInt *const self, StackInt *const s) {
    self->m_start = s->m_start;
    self->m_finish = s->m_finish;
    self->m_end_of_storage = s->m_end_of_storage;
    
    s->m_start = s->m_finish = s->m_end_of_storage = (int *)(0);
    
    return self;
}

static void StackInt_resize(StackInt *const self, size_t old_capacity, size_t new_capacity) {
    if (old_capacity == new_capacity) { return; }
    
    int *new_start = realloc(self->m_start, sizeof *self->m_start * new_capacity);
        
    assert(new_start);
        
    self->m_start = new_start;
    self->m_finish = old_capacity < new_capacity ? new_start + old_capacity : new_start + new_capacity;
    self->m_end_of_storage = new_start + new_capacity;
}

