//
//  blaseddStarbucks.h
//  Starbucks
//
//  Created by Doug Blase on 10/25/13.
//  Copyright (c) 2013 Doug Blase. All rights reserved.
//

#include "BST.h"
#include "Starbucks.h"

//template <class Key, class T>
class blaseddStarbucks: public Starbucks{
public:
    blaseddStarbucks();
    ~blaseddStarbucks();
    BST<double, Entry> tree;
    
       virtual void build(Entry* c, int n);
	
       virtual Entry* getNearest(double x, double y);

    
};




#include "blaseddStarbucks.ipp"