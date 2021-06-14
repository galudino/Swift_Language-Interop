//
//  c_stack_int.h
//  StackTest-C
//
//  Created by Gemuele Aludino on 5/12/21.
//

#ifndef C_STACK_INT_H
#define C_STACK_INT_H

#include <stdint.h>
#include <stdbool.h>

typedef struct stack StackInt;

struct stack {
    int *m_start;
    int *m_finish;
    int *m_end_of_storage;
};

void StackInt_initDefault(StackInt *const self);
void StackInt_init(StackInt *const self, size_t capacity);
void StackInt_initCopy(StackInt *const self, const StackInt *const s);
void StackInt_initMove(StackInt *const self, StackInt *const s);
void StackInt_deinit(StackInt *const self);

void StackInt_push(StackInt *const self, int val);

static inline void StackInt_pop(StackInt *const self) {
    if (self->m_finish > self->m_start) {
        --self->m_finish;
    }
}

static inline int StackInt_top(const StackInt *const self) {
    return *(self->m_finish - 1);
}

static inline bool StackInt_empty(const StackInt *const self) {
    return self->m_finish == self->m_start;
}

void StackInt_clear(StackInt *const self);

StackInt *StackInt_assignCopy(StackInt *const self, const StackInt *const s);
StackInt *StackInt_assignMove(StackInt *const self, StackInt *const s);

#endif /* C_STACK_INT_H */
