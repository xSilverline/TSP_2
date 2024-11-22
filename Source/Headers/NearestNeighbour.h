//
// Created by Silver on 05.10.2024.
//

#ifndef TSP_2_NEARESTNEIGHBOUR_H
#define TSP_2_NEARESTNEIGHBOUR_H

#include "TimeCounter.h"
#include "Structures.h"


class NearestNeighbour
        {
private:
public:
            int getCost();
            double runNN(int ** graphMatrix, int v,int startingNode,bool print,int killSwitch,bool enchancedNN);

};


#endif //TSP_2_NEARESTNEIGHBOUR_H
