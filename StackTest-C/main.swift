//
//  main.swift
//  StackTest-C
//
//  Created by Gemuele Aludino on 5/12/21.
//

func useCStack() {
    // Declare a StackInt
    var s = StackInt();
    
    // Initialize the stack to a capacity of 1
    StackInt_init(&s, 1)
    
    // Push integers 10, 9, 8 ... 1 to the stack
    for i: Int32 in (1...10).reversed() {
        StackInt_push(&s, i)
    }
    
    // For all stack members,
    // peek the stack top, print the element, then pop it off
    while !StackInt_empty(&s) {
        let n = StackInt_top(&s)
        print("[useCStack] stack_int just popped: \(n)")
        
        StackInt_pop(&s)
    }
}

useCStack()
