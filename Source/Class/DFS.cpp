//
// Created by Silver on 01.11.2024.
//

#include <stack>
#include "../Headers/DFS.h"
#include "../Headers/TimeCounter.h"

int killTime;

void dfs(Node* currentNode,int **matrix,int size,int& bestCost,vector<int>& bestPath)
{
    if(killTime < getCounter())
        return;

    if(currentNode == nullptr)
    {
        return;
    }

    if(currentNode->level == size-1)
    {
        int currentCost = currentNode->cost + currentNode->costToStart;
        if(currentCost < bestCost)
        {
            bestCost = currentCost;
            bestPath = currentNode->currentPath;
            bestPath.push_back(currentNode->currentPath[0]);
        }
//        delete currentNode;
    }

    for(int i = 0; i<size; ++i)
    {
        if(find(currentNode->currentPath.begin(),currentNode->currentPath.end(),i) == currentNode->currentPath.end())
        {
            int newCost = currentNode->cost+matrix[currentNode->currentPath.back()][i];
            if(newCost < bestCost)
            {
                Node* newChild = new Node;
                newChild->currentPath = currentNode->currentPath;
                newChild->currentPath.push_back(i);
                newChild->nodeNumber = i;
                newChild->cost = newCost;
                newChild->parent = currentNode;
                newChild->costToStart = matrix[i][newChild->currentPath[0]];
                newChild->level = currentNode->level+1;
                currentNode->costToStart = 0;
                currentNode->children.push_back(newChild);

                dfs(newChild,matrix,size,bestCost,bestPath);
            }


        }

    }


//
//    for(Node* i : currentNode->children)
//    {

//        if(i->cost  < bestCost) {

//            dfs(i, bestCost, bestPath);
//        }



}


double DFS::runDFS(Node* root,int **matrix,int size,int initialBestCost, int start,int killSwitch,bool print)
{
    vector<int> bestPath;
    int bestCost = initialBestCost;
    startCounter();

    killTime = killSwitch;

    root->currentPath.push_back(start);
    root->nodeNumber = start;
    root->level = 0;

    dfs(root,matrix,size,bestCost,bestPath);
    double time = getCounter();

    if(time > killSwitch)
        return -999;
    if(print) {
        cout << " --- DFS ---" << endl;
        cout << "Cost: " << bestCost << endl;
        cout << "Path: ";
        int last = bestPath.back();
        bestPath.pop_back();
        for (int i: bestPath)
            cout << i << " -> ";
        cout << last;
        cout << endl << "Time: " << time << " ms" << endl;
    }
    return time;
}

void DFS::clean(Node* node)
{
    if(node == nullptr)
    {
        return;
    }


    for(Node* i : node->children)
    {
        clean(i);
    }

    delete node;
}
