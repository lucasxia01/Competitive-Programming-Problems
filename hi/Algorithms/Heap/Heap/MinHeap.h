//
//  Heap.h
//  Heap
//
//  Created by Lucas Xia on 3/7/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#ifndef Heap_h
#define Heap_h

#include <vector>

class MinHeap {
public:
    MinHeap() {
        
    }
    ~MinHeap();
    int getMin();
    void add(int value);
    
private:
    vector<int> v;
    void heapify();
};

#endif /* Heap_h */
