#include <iostream>
#include <map>
#include <vector>
#include <limits>

using namespace std;

class node {
    public:
        vector<unsigned int> oldNeighborList;
        vector<unsigned int> newNeighborList;
        // TODO: initialize the vectors
};

class Dst {
    public:
        unsigned int dstPoint;
        map<unsigned int, unsigned int> oldTable;
        map<unsigned int, unsigned int> newTable;
};

class Info {
    public:
        // vector<unsigned int> dstList;
        vector<Dst> dstList;
        unsigned int nodeNum;
        unsigned int dstNum;
        unsigned int linkNum;
        bool isOld;
        
        Info() : isOld(true) {};
        void initialize();
};

void Dijkstra(Info info, vector<node> nodeList, unsigned int root);

unsigned int getMin(Info info, vector<unsigned int> distanceArr, vector<bool> isFound);

void findPath(Info info, vector<node> nodeList);

int main() {
    unsigned int linkId;
    unsigned int nodeId1;
    unsigned int nodeId2;
    vector<node> nodeList; // nodes in the graph
    Info info;
    vector<Dst> dstList;

    info.initialize(); // read the data

    nodeList.resize(info.nodeNum);

    for(int i = 0; i < info.nodeNum; i++) {
        nodeList.at(i).oldNeighborList.resize(info.nodeNum);
        nodeList.at(i).newNeighborList.resize(info.nodeNum);
    }

    // read the information of links
    for(int i = 0; i < info.linkNum; i++) {
        cin >> linkId >> nodeId1 >> nodeId2; // what is the usage?
        cin >> nodeList.at(nodeId1).oldNeighborList.at(nodeId2);
        cin >> nodeList.at(nodeId1).newNeighborList.at(nodeId2);
    }

    findPath(info, nodeList);
    info.isOld = false;
    // findPath(info, nodeList);

    // cout << "test" << endl;

    for(int i = 0; i < info.nodeNum; i++) {
        cout << i << endl; // the Id of each start point
        for(unsigned int j = 0; j < info.dstNum; j++) {
            // TODO: print out the old table and new table(changed entries)
            cout << info.dstList.at(j).dstPoint << " " << info.dstList.at(j).oldTable.at(i);
        }
    }

    return 0;
}

void Dijkstra(Info info, vector<node> nodeList, unsigned int root)
{   
    // int *distanceArr;
    // bool *isFound;
    // distanceArr = (int *)malloc(sizeof(int) * vertexNum);
    // isFound = (bool *)malloc(sizeof(bool) * vertexNum);

    unsigned int curPoint;

    vector<unsigned int> distanceArr; // store the distance between the start point and other nodes
    vector<bool> isFound;

    map<unsigned int, unsigned int> table; // return a table of path

    // allocate memory
    distanceArr.resize(info.nodeNum);
    isFound.resize(info.nodeNum, false);

    // for(int i = 0; i < vertexNum; i++) {
    //     distanceArr[i] = adjMatrix[0][i];
    //     isFound[i] = false;
    // }

    for(unsigned int i = 0; i < info.nodeNum; i++) {
        unsigned int tmp = info.isOld ? nodeList.at(root).oldNeighborList.at(i) : nodeList.at(root).newNeighborList.at(i);
        distanceArr.at(i) = tmp;
        info.dstList.at(root).oldTable.at(i) = root; // root is the next node of node i (after the graph being reversed)
    }

    // isFound[0] = true;
    // distanceArr[0] = 0;
    // for(int i = 0; i < vertexNum - 2; i++) {
    //     curPoint = getMin(distanceArr, vertexNum, isFound);
    //     isFound[curPoint] = true;
    //     for(int j = 0; j < vertexNum; j++)
    //         if(!isFound[j])
    //             if(distanceArr[curPoint] + adjMatrix[curPoint][j] < distanceArr[j])
    //                 distanceArr[j] = distanceArr[curPoint] + adjMatrix[curPoint][j];
    // }

    isFound.at(root) = true;
    distanceArr.at(root) = 0;
    for(unsigned int i = 0; i < info.nodeNum - 2; i++) {
        curPoint = getMin(info, distanceArr, isFound);
        isFound.at(curPoint) = true;
        for(unsigned int j = 0; j < info.nodeNum; j++) {
            cout << "test" << endl;
            if(!isFound.at(j)) {
                if(distanceArr.at(curPoint) + nodeList.at(curPoint).oldNeighborList.at(j) < distanceArr.at(j)) {
                    distanceArr.at(j) = distanceArr.at(curPoint) + nodeList.at(curPoint).oldNeighborList.at(j);
                    // TODO: save the child of each node to the table
                    info.dstList.at(root).oldTable.at(j) = curPoint; // !use [] operator to overwrite the old data?
                }
            }
        }
    }
    
    return;
}

unsigned int getMin(Info info, vector<unsigned int> distanceArr, vector<bool> isFound)
{
    // int minPos = -1;
    // int min = INT_MAX;

    // for(int i = 0; i < vertexNum; i++) {
    //     if(distanceArr[i] < min && !isFound[i]) {
    //         min = distanceArr[i];
    //         minPos = i;
    //     }
    // }

    unsigned int minPos;
    unsigned int min = UINT_MAX;

    for(unsigned int i = 0; i < info.nodeNum; i++) {
        if(distanceArr.at(i) < min && !isFound.at(i)) {
            min = distanceArr.at(i);
            minPos = i;
        }
    }

    return minPos;
}

void Info::initialize()
{
    cin >> nodeNum >> dstNum >> linkNum;

    // read the destinations
    dstList.resize(dstNum);
    for(int i = 0; i < dstNum; i++)
        cin >> dstList.at(i).dstPoint;
}

void findPath(Info info, vector<node> nodeList)
{
    for(int i = 0; i < info.dstNum; i++)
        Dijkstra(info, nodeList, info.dstList.at(i).dstPoint); // use the destinations as the root of shortest path tree
    
    return;
}