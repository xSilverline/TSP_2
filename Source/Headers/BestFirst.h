//
// Created by Silver on 01.11.2024.
//

#ifndef TSP_2_BESTFIRST_H
#define TSP_2_BESTFIRST_H

#include "Structures.h"

class BestFirst {
private:
public:
    double runBestFirst(Node* root,int **matrix, int size,int initialBestCost,int start,int killSwitch,bool print);

};


#endif //TSP_2_BESTFIRST_H
