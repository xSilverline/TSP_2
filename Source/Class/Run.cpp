//
// Created by Silver on 01.11.2024.
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include "../Headers/Run.h"

string outFileName;
string inFileName;
int optimal;


class WithComma: public numpunct<char> // class for decimal numbers with comma
{
    protected: char do_decimal_point() const override { return ','; } // override the function that gives the decimal separator
};

void Run::run(int **matrix,int size, int reps,int start,int killSwitch,const string& method,string output,string input,int opt,bool print)
{
    optimal = opt;
    inFileName = input;
    outFileName = output;

    this->graphMatrix = matrix;
    this->graphSize = size;
    this->repeats = reps;

    this->startingNode = start;

    int initialBestCost = INT_MAX;
    if(size > 10)
    {
        NearestNeighbour nn;
        nn.runNN(matrix,size,start,false,killSwitch,false);
        initialBestCost = nn.getCost()+1;
        cout<<initialBestCost<<endl;
    }


    DFS dfs;
    locale myloc(  locale(),    // C++ default locale
                   new WithComma);
    ofstream outputFile;
    outputFile.imbue(myloc);
    outputFile.open (outFileName);
    outputFile<<"Input file\t"<<inFileName<<endl;
    outputFile<<"Optimal cost\t"<<optimal<<endl;
    double timedfs=0;
    double timebfs=0;
    double timebest=0;

    double oneTimeDfs=0;
    double oneTimeBfs=0;
    double oneTimeBest=0;



    for(int i = 0; i< reps;i++)
    {
        cout<<" ------- RUN "<<i+1<<" -------"<<endl<<endl;
        if (method == "dfs")
        {
            Node *root = new Node;
            oneTimeDfs= dfs.runDFS(root, matrix, size, initialBestCost, start, killSwitch,print);
            timedfs+=oneTimeDfs;
            outputFile<<"Time DFS Rep "<<i+1<<"\t"<<fixed<<setprecision(4)<<oneTimeDfs<<endl;
            dfs.clean(root);
            cout<<endl<<endl;
        } else if (method == "bfs") {
            Node *root = new Node;
            BFS bfs;
            oneTimeBfs=bfs.runBFS(root, matrix, size, initialBestCost, start, killSwitch,print);
            timebfs+=oneTimeBfs;
            outputFile<<"Time BFS Rep "<<i+1<<"\t"<<fixed<<setprecision(4)<<oneTimeBfs<<endl;
            dfs.clean(root);
            cout<<endl<<endl;

        } else if (method == "best") {
            Node *root = new Node;
            BestFirst bf;
            oneTimeBest= bf.runBestFirst(root, matrix, size, initialBestCost, start, killSwitch,print);
            timebest += oneTimeBest;
            outputFile<<"Time Best Rep "<<i+1<<"\t"<<fixed<<setprecision(4)<<oneTimeBest<<endl;
            dfs.clean(root);
            cout<<endl<<endl;
        } else if (method == "all") {
            Node *root = new Node;
            oneTimeDfs = dfs.runDFS(root, matrix, size, initialBestCost, start, killSwitch,print);
            timedfs+=oneTimeDfs;
            outputFile<<"Time DFS Rep "<<i+1<<"\t"<<fixed<<setprecision(4)<<oneTimeDfs<<endl;
            dfs.clean(root);
            cout<<endl<<endl;

            root = new Node;
            BFS bfs;
            oneTimeBfs = bfs.runBFS(root, matrix, size, initialBestCost, start, killSwitch,print);
            timebfs+=oneTimeBfs;
            outputFile<<"Time BFS Rep "<<i+1<<"\t"<<fixed<<setprecision(4)<<oneTimeBfs<<endl;
            dfs.clean(root);
            cout << endl << endl;

            root = new Node;
            BestFirst bf;
            oneTimeBest= bf.runBestFirst(root, matrix, size, initialBestCost, start, killSwitch,print);
            timebest+=oneTimeBest;
            outputFile<<"Time Best Rep "<<i+1<<"\t"<<fixed<<setprecision(4)<<oneTimeBest<<endl;
            dfs.clean(root);
            cout << endl << endl;

        } else
            cout << "Wrong method! Check config file ! " << endl;
    }
    timedfs/=reps;
    timebfs/=reps;
    timebest/=reps;

    if(timedfs!=0)
        outputFile<<"Avg Time DFS \t"<<fixed<<setprecision(4)<<timedfs<<endl;
    if(timebfs !=0)
        outputFile<<"Avg Time BFS \t"<<fixed<<setprecision(4)<<timebfs<<endl;
    if(timebest !=0)
        outputFile<<"Avg Time Best \t"<<fixed<<setprecision(4)<<timebest<<endl;


}

//int caluculateBound(int **matrix, int size,int visited[])
//{
//    int bound = 0;
//    for(int i = 0; i<size; i++)
//    {
//        if(!visited[i])
//        {
//            int minimal = INT_MAX;
//            for(int j = 0;j<size;j++)
//            {
//                if(!visited[j] && matrix[i][j] !=-1 && matrix[i][j] < minimal)
//                    minimal = matrix[i][j];
//
//            }
//            if(minimal != INT_MAX)
//                bound += minimal;
//        }
//    }
//
//    return bound;
//}
// Wersja relaksacji co Hindus wyjaśniał

//int lowest_bound(int** matrix, int size, const vector<int>& path) {
//
//    vector<bool> visitedRows(size, false), visitedCols(size, false);
//    int bound = 0;
//
//    // Oznacz odwiedzone wiersze i kolumny na podstawie ścieżki
//    for (size_t i = 0; i < path.size() - 1; ++i) {
//        int from = path[i];
//        int to = path[i + 1];
//        visitedRows[from] = true;
//        visitedCols[to] = true;
//    }
//
//    for (size_t i = 0; i < path.size() - 1; ++i) {
//        int from = path[i];
//        int to = path[i + 1];
//        if (matrix[from][to] != -1) {
//            bound += matrix[from][to];
//        }
//    }
//
////    cout << "sciezka: ";
////    for (int node : path) cout << node << " ";
////    cout << endl;
//
//    // Redukcja wierszy
//    for (int i = 0; i < size; ++i) {
//        if (!visitedRows[i]) {
//            int minVal = INT_MAX;
//            for (int j = 0; j < size; ++j) {
//                if (!visitedCols[j] && matrix[i][j] != -1) {
//                    minVal = min(minVal, matrix[i][j]);
//                }
//            }
//            if (minVal != INT_MAX) {
//
////                    cout << "Dodanie do bound w wierszu " << i << ": " << minVal << endl;
//                    bound += minVal;
////                cout << "Minimalny koszt w wierszu " << i << ": " << minVal << endl;
//
//            }
//        }
//    }
//
//    // Redukcja kolumn
//    for (int j = 0; j < size; ++j) {
//        if (!visitedCols[j]) {
//            int minVal = INT_MAX;
//            for (int i = 0; i < size; ++i) {
//                if (!visitedRows[i] && matrix[i][j] != -1) {
//                    minVal = min(minVal, matrix[i][j]);
//                }
//            }
//            if (minVal != INT_MAX) {
////                cout << "Dodanie do bound w kolumnie " << j << ": " << minVal << endl;
//                bound += minVal;
////                cout << "Minimalny koszt w kolumnie " << j << ": " << minVal << endl;
//            }
//        }
//    }
//
////    cout << "Dolne ograniczenie (bound): " << bound << endl;
//    return bound;
//}
//
//void Run::buildTree(int **matrix,int size, int start)
//{
//    Node* root = new Node;
//    int visited[size];
//
//
//
//    for(int i = 0; i<size; i++)
//    {
//
//        visited[i] = 0;
//
//    }
//
//    visited[start] = 1;
//    root->nodeNumber = start;
//    root->currentPath.push_back(root->nodeNumber);
////    root->bound= caluculateBound(matrix,size,visited);
//
////    root->bound = lowest_bound(matrix,size,root->currentPath);
//
//    addToTree(matrix,size,root,visited);
//}
//
//
//void Run::addToTree(int **matrix,int size,Node* parent,int visited[])
//{
//
//    int visitedCopy[size];
//
//    for(int i = 0; i<size;i++)
//    {
//        if(visited[i] != 1 && matrix[parent->nodeNumber][i] != -1)
//        {
//            Node* currentNode = new Node;
//
//
//            for (int x = 0; x < size; x++) {
//                visitedCopy[x] = visited[x];
//            }
//
//
//
//            currentNode->nodeNumber = i;
//            currentNode->parent = parent;
//            visitedCopy[i] = 1;
//
//            if(currentNode->parent != nullptr)
//                currentNode->currentPath = currentNode->parent->currentPath;
//
//
//            currentNode->cost = parent->cost+matrix[currentNode->currentPath.back()][i];
//
////            currentNode->bound = currentNode->cost + caluculateBound(matrix,size,visitedCopy);
//
//            currentNode->currentPath.push_back(currentNode->nodeNumber);
////            currentNode->bound = currentNode->cost + lowest_bound(matrix,size,currentNode->currentPath);
//
//
//            parent->children.push_back(currentNode);
//            addToTree(matrix, size, currentNode, visitedCopy);
//            if(currentNode->children.empty())
//                currentNode->costToStart = matrix[i][currentNode->currentPath[0]];
//
//        }
//    }
//}

