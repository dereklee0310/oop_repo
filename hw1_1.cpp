#include <iostream>
#include <map>
#include <vector>
#include <climits>
#include <utility>

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
        vector<Node> nodeList;
        vector<Dst> dstList;
        unsigned int nodeNum;
        unsigned int dstNum;
        unsigned int linkNum;
        bool isOld;
        
        Info() : isOld(true) {};
        void initialize();
        void printOldTable();
        void printNewTable();
};

void Dijkstra(Info &info, vector<Node> nodeList, unsigned int dstIdx);

unsigned int getMin(Info info, vector<unsigned long> distanceArr, vector<bool> isFound);

void findPath(Info &info, vector<Node> nodeList);

int main() {
    Info info;

    info.initialize(); // read the data

    findPath(info, info.nodeList);
    info.isOld = false; // change the state to find the new table instead
    findPath(info, info.nodeList);

    info.printOldTable();
    info.printNewTable();

    return 0;
}

void Dijkstra(Info &info, vector<Node> nodeList, unsigned int dstIdx)
{   
    unsigned int root;
    unsigned int curPoint;
    vector<unsigned long> distanceArr; // store the distance between the start point and other nodes
    vector<bool> isFound; // record the state of each node


    // initialize
    distanceArr.resize(info.nodeNum, UINT_MAX / 2);
    root = info.dstList.at(dstIdx).dstPoint;
    distanceArr.at(root) = 0;
    isFound.resize(info.nodeNum, false);

    if(info.isOld)
        info.dstList.at(dstIdx).oldTable[root] = root; // the next node of the destination is the destination itself
    else
        info.dstList.at(dstIdx).newTable[root] = root;
    
    for(unsigned int i = 0; i < info.nodeNum - 1; i++) {
        curPoint = getMin(info, distanceArr, isFound); // get the smallest node that have the shortest distance between root node
        isFound.at(curPoint) = true;

        // update all distance between neighbor nodes and current point
        for(unsigned int j = 0; j < info.nodeNum; j++) {
            if(isFound.at(j))
                continue;
            if(info.isOld) {
                if(nodeList.at(curPoint).oldNeighborList.at(j) && distanceArr.at(curPoint) != UINT_MAX && distanceArr.at(curPoint) + nodeList.at(curPoint).oldNeighborList.at(j) < distanceArr.at(j)) {
                    distanceArr.at(j) = distanceArr.at(curPoint) + nodeList.at(curPoint).oldNeighborList.at(j);
                    info.dstList.at(dstIdx).oldTable[j] = curPoint; // use [] operator to overwrite the old data
                }
            } else {
                if(nodeList.at(curPoint).newNeighborList.at(j) && distanceArr.at(curPoint) != UINT_MAX && distanceArr.at(curPoint) + nodeList.at(curPoint).newNeighborList.at(j) < distanceArr.at(j)) {
                    distanceArr.at(j) = distanceArr.at(curPoint) + nodeList.at(curPoint).newNeighborList.at(j);
                    info.dstList.at(dstIdx).newTable[j] = curPoint; // use [] operator to overwrite the old data
                }
            }
                
        }
    }
}

unsigned int getMin(Info info, vector<unsigned long> distanceArr, vector<bool> isFound)
{
    unsigned int minPos = 0;
    unsigned long min = LONG_MAX;

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
    unsigned int linkId;
    unsigned int nodeId1;
    unsigned int nodeId2;
    unsigned int weight;

    cin >> nodeNum >> dstNum >> linkNum;
    dstList.resize(dstNum);
    for(vector<Dst>::iterator itr = dstList.begin(); itr != dstList.end(); itr++)
        cin >> (*itr).dstPoint;

    // allocate memory and initialize all entries to UINT_MAX
    nodeList.resize(nodeNum);
    for(vector<Node>::iterator itr = nodeList.begin(); itr != nodeList.end(); itr++) {
        (*itr).oldNeighborList.resize(nodeNum, UINT_MAX / 2);
        (*itr).newNeighborList.resize(nodeNum, UINT_MAX / 2);
    }
    
    // read the relations between nodes
    for(unsigned int i = 0; i < linkNum; i++) {
        cin >> linkId >> nodeId1 >> nodeId2;
        cin >> weight;
        nodeList.at(nodeId1).oldNeighborList.at(nodeId2) = weight;
        nodeList.at(nodeId2).oldNeighborList.at(nodeId1) = weight;
        cin >> weight;
        nodeList.at(nodeId1).newNeighborList.at(nodeId2) = weight;
        nodeList.at(nodeId2).newNeighborList.at(nodeId1) = weight;
    }
}

void findPath(Info &info, vector<Node> nodeList)
{
    for(unsigned int i = 0; i < info.dstNum; i++)
        Dijkstra(info, nodeList, i); // use the destinations as the root of shortest path tree 
}

void Info::printOldTable()
{
    for(unsigned int i = 0; i < nodeNum; i++) {
        cout << i << endl; // simply print the node Id
        for(unsigned int j = 0; j < dstNum; j++)
            if(i != dstList.at(j).dstPoint) // if the node Id equals the destination, don't print it.
                cout << dstList.at(j).dstPoint << " " << dstList.at(j).oldTable[i] << endl;
    }
}
void Info::printNewTable()
{
    for(unsigned int i = 0; i < nodeNum; i++) {
        for(vector<Dst>::iterator itr = dstList.begin(); itr != dstList.end(); itr++) {
            if((*itr).oldTable[i] != (*itr).newTable[i]) {
                cout << i << endl; // print the node Id if any path is changed
                break;
            }
        } 
        for(unsigned int k = 0; k < dstNum; k++) {
            if(dstList.at(k).oldTable[i] != dstList.at(k).newTable[i]) // print the nodes that has been changed
                cout << dstList.at(k).dstPoint << " " << dstList.at(k).newTable[i] << endl;
        }
    }
}