//
// Created by Silver on 01.11.2024.
//

#ifndef TSP_2_STRUCTURES_H
#define TSP_2_STRUCTURES_H


#include <vector>
#include <algorithm>
#include "TimeCounter.h"

using namespace std;

struct listElement
{
    listElement *next;
    int target = 0;
    int weight = 0;
};



struct resultHelper
{
    int * path;
    int cost;
};

struct Node
{
    int nodeNumber = 0;
    int cost = 0;
    vector<int> currentPath;
    int level=0;
    int costToStart=0;

    vector<Node*> children;
    Node * parent = nullptr;
};

struct Comparator
{
    bool operator()(const Node* x, const Node* y)
    {
        return x->cost > y->cost;
    }
};
#endif //TSP_2_STRUCTURES_H


