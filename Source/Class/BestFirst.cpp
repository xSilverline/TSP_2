//
// Created by Silver on 01.11.2024.
//

#include <queue>

#include "../Headers/BestFirst.h"

double BestFirst::runBestFirst(Node* root, int **matrix,int size, int initialBestCost,int start,int killSwitch,bool print)
{

    startCounter();

    root->currentPath.push_back(start);
    root->nodeNumber = start;
    root->level = 0;
    vector<int> bestPath;
    int bestCost = initialBestCost;

//    if(root == nullptr)
//        return -999;

    priority_queue<Node* , vector<Node*>, Comparator> q;

    q.push(root);

    while (!q.empty())
    {

        if(killSwitch<getCounter())
            return -999;
        Node* currentNode = q.top();
        q.pop();

        if(currentNode->level == size-1)
        {
            int currentCost = currentNode->cost + currentNode->costToStart;
            if(currentCost < bestCost)
            {
                bestCost = currentCost;
                bestPath = currentNode->currentPath;
                bestPath.push_back(currentNode->currentPath[0]);
            }
//            delete currentNode;
            continue;
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

                    q.push(newChild);
                }
            }

        }

//        for(Node* children: currentNode->children)
//        {
//            if(children->cost < bestCost)
//                q.push(children);
//        }
    }

    double time = getCounter();
    if(print) {
        cout << " --- Best First ---" << endl;
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
