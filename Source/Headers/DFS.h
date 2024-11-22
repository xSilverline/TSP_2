//
// Created by Silver on 01.11.2024.
//

#ifndef TSP_2_DFS_H
#define TSP_2_DFS_H


#include "Structures.h"


class DFS {
private:
public:
    double runDFS(Node* root,int **matrix,int size,int bestCost,int start,int killSwitch,bool print);

    void clean(Node *node);
};


#endif //TSP_2_DFS_H
