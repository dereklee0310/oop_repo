#include <iostream>
#include <map>
#include <vector>
#include <climits>

using namespace std;

class Node {
    public:
        vector<unsigned int> oldNeighborList;
        vector<unsigned int> newNeighborList;
};

class Dst {
    public:
        unsigned int dstPoint;
        map<unsigned int, unsigned int> oldTable;
        map<unsigned int, unsigned int> newTable;
};

class Info {
    public:
        vector<Dst> dstList;
        unsigned int nodeNum;
        unsigned int dstNum;
        unsigned int linkNum;
        bool isOld;
        
        Info() : isOld(true) {};
        void initialize();
};

void Dijkstra(Info &info, vector<Node> nodeList, unsigned int dstIdx);

unsigned int getMin(Info info, vector<unsigned int> distanceArr, vector<bool> isFound);

void findPath(Info &info, vector<Node> nodeList);

int main() {
    unsigned int linkId;
    unsigned int nodeId1;
    unsigned int nodeId2;
    unsigned int tmp;
    vector<Node> nodeList; // nodes in the graph with their neighbors
    vector<Dst> dstList; // destinations with their corresponding trees
    Info info;

    info.initialize(); // read the data
    nodeList.resize(info.nodeNum);
    for(unsigned int i = 0; i < info.nodeNum; i++) {
        nodeList.at(i).oldNeighborList.resize(info.nodeNum, UINT_MAX / 2);
        nodeList.at(i).newNeighborList.resize(info.nodeNum, UINT_MAX / 2);
    }

    // read the information of links
    for(unsigned int i = 0; i < info.linkNum; i++) {
        cin >> linkId >> nodeId1 >> nodeId2;
        cin >> tmp;
        nodeList.at(nodeId1).oldNeighborList.at(nodeId2) = tmp;
        nodeList.at(nodeId2).oldNeighborList.at(nodeId1) = tmp;
        cin >> tmp;
        nodeList.at(nodeId1).newNeighborList.at(nodeId2) = tmp;
        nodeList.at(nodeId2).newNeighborList.at(nodeId1) = tmp;
    }

    findPath(info, nodeList);
    info.isOld = false;
    findPath(info, nodeList);


    for(unsigned int i = 0; i < info.nodeNum; i++) {
        cout << i << endl; // simply print the node Id
        for(unsigned int j = 0; j < info.dstNum; j++) {
            if(i == info.dstList.at(j).dstPoint) // if the node Id equals the destination, don't print it.
                continue;
            cout << info.dstList.at(j).dstPoint << " " << info.dstList.at(j).oldTable[i] << endl;
        }
    }

    for(unsigned int i = 0; i < info.nodeNum; i++) {
        for(unsigned int j = 0; j < info.dstNum; j++) {
            if(info.dstList.at(j).oldTable[i] != info.dstList.at(j).newTable[i] && i != info.dstList.at(j).dstPoint) {
                cout << i << endl; // print the node Id if any path is changed
                break;
            }
        }
        for(unsigned int k = 0; k < info.dstNum; k++) {
            if(i == info.dstList.at(k).dstPoint) // if the node Id equals the destination, don't print it.
                continue;
            if(info.dstList.at(k).oldTable[i] != info.dstList.at(k).newTable[i]) // print the nodes which has been changed
                cout << info.dstList.at(k).dstPoint << " " << info.dstList.at(k).newTable[i] << endl;
        }
    }

    return 0;
}

void Dijkstra(Info &info, vector<Node> nodeList, unsigned int dstIdx)
{   
    unsigned int curPoint;
    vector<unsigned int> distanceArr; // store the distance between the start point and other nodes
    vector<bool> isFound; // record the state of each node

    // allocate memory
    distanceArr.resize(info.nodeNum);
    isFound.resize(info.nodeNum, false);

    // for(int i = 0; i < vertexNum; i++) {
    //     distanceArr[i] = adjMatrix[0][i];
    //     isFound[i] = false;
    // }

    int root = info.dstList.at(dstIdx).dstPoint;
    info.dstList.at(dstIdx).oldTable[root] = root; // the next node of destionation is the destination itself

    for(unsigned int i = 0; i < info.nodeNum; i++) {
        unsigned int tmp = info.isOld ? nodeList.at(root).oldNeighborList.at(i) : nodeList.at(root).newNeighborList.at(i);
        distanceArr.at(i) = tmp;
        if(tmp != UINT_MAX / 2) {
            if(info.isOld) {
                info.dstList.at(dstIdx).oldTable[i] = root; // root is the next node of node i (after the graph being reversed)
            } else {
                info.dstList.at(dstIdx).newTable[i] = root;
            }
        }
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
        curPoint = getMin(info, distanceArr, isFound); // get the smallest node that have the shortest distance between root node
        isFound.at(curPoint) = true;

        // update all distance between neighbor nodes and current point
        for(unsigned int j = 0; j < info.nodeNum; j++) {
            if(!isFound.at(j)) {
                if(info.isOld) {
                    if(distanceArr.at(curPoint) + nodeList.at(curPoint).oldNeighborList.at(j) < distanceArr.at(j)) {
                        distanceArr.at(j) = distanceArr.at(curPoint) + nodeList.at(curPoint).oldNeighborList.at(j);
                        info.dstList.at(dstIdx).oldTable[j] = curPoint; // use [] operator to overwrite the old data
                    }
                } else {
                    if(distanceArr.at(curPoint) + nodeList.at(curPoint).newNeighborList.at(j) < distanceArr.at(j)) {
                        distanceArr.at(j) = distanceArr.at(curPoint) + nodeList.at(curPoint).newNeighborList.at(j);
                        info.dstList.at(dstIdx).newTable[j] = curPoint; // use [] operator to overwrite the old data
                    }
                }
            }
        }
    }
}

unsigned int getMin(Info info, vector<unsigned int> distanceArr, vector<bool> isFound)
{
    unsigned int minPos = 0;
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

    dstList.resize(dstNum);
    for(unsigned int i = 0; i < dstNum; i++)
        cin >> dstList.at(i).dstPoint;
}

void findPath(Info &info, vector<Node> nodeList)
{
    for(unsigned int i = 0; i < info.dstNum; i++)
        Dijkstra(info, nodeList, i); // use the destinations as the root of shortest path tree
}