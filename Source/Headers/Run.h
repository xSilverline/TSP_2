//
// Created by Silver on 01.11.2024.
//

#ifndef TSP_2_RUN_H
#define TSP_2_RUN_H



#include "DFS.h"
#include "BFS.h"
#include "NearestNeighbour.h"
#include "BestFirst.h"
#include "Structures.h"

class Run
{

private:
    int ** graphMatrix;
    int graphSize;
    int repeats;
    int startingNode;



//    void buildTree(int **matrix, int size, int start);


public:
    void run(int ** graphMatrix, int graphSize, int repeats,int start,int killSwitch,const string& method,string output,string input,int opt,bool print);


//    void addToTree(int **matrix, int size, Node* parent, int *visited);

//    int caluculateBound(int **matrix, int siz,int visited[]);
};


#endif //TSP_2_RUN_H
