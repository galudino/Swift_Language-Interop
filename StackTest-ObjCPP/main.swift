//
//  main.swift
//  StackTest-ObjCPP
//
//  Created by Gemuele Aludino on 5/12/21.
//

func useObjCPPStack() {
    // Declare a StackInt
    // Initialize the stack to a capacity of 1
    let s: StackInt = StackInt(10)
    
    // Push integers 10, 9, 8 ... 1 to the stack
    for i: Int32 in (1...10).reversed() {
        s.push(i)
    }
    
    // For all stack members,
    // peek the stack top, print the element, then pop it off
    while !s.empty() {
        let n = s.top()
        print("[useObjCPPStack] StackInt just popped: \(n)")
        
        s.pop()
    }
    
    s.deinit()
    
    s.push(1123)
    
    print("top after deinit: \(s.top())")
}

useObjCPPStack()
