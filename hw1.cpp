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

class Info {
    public:
        vector<unsigned int> dstList;
        unsigned int nodeNum;
        unsigned int dstNum;
        unsigned int linkNum;
        map<unsigned int, unsigned int> oldTable;
        map<unsigned int, unsigned int> newTable;
        bool isOld;
        
        Info() : isOld(true) {};
        void initialize();
};

void Dijkstra(Info info, vector<node> nodeList, unsigned int root);

unsigned int getMin(Info info, vector<unsigned int> distanceArr, vector<bool> isFound);

vector<unsigned int> findPath(Info info, vector<node> nodeList);

int main() {
    unsigned int linkId;
    unsigned int nodeId1;
    unsigned int nodeId2;
    vector<node> nodeList; // nodes in the graph
    Info info;

    info.initialize(); // read the data

    // read the information of links
    for(int i = 0; i < info.linkNum; i++) {
        cin >> linkId >> nodeId1 >> nodeId2; // what is the usage?
        cin >> nodeList[nodeId1].oldNeighborList[nodeId2];
        cin >> nodeList[nodeId1].newNeighborList[nodeId2];
    }


    // !test
    // cout << info.nodeNum << endl;
    // cout << info.dstNum << endl;
    // cout << info.linkNum << endl;
    // cout << "------------" << endl;
    // for(int i = 0; i < info.dstNum; i++)
    //     cout << info.dstList[i] << endl;


    findPath(info, nodeList);
    info.isOld = false;
    findPath(info, nodeList);


    for(int i = 0; i < info.nodeNum; i++) {
        cout << i << endl; // the Id of each start point
        for(int j = 0; j < info.dstNum; j++);
            // TODO: print out the old table and new table(changed entries)
    }

    return 0;
}

void Dijkstra(Info info, vector<node> nodeList, unsigned int root)
{   
    // int *distanceArr;
    // bool *isFound;
    // distanceArr = (int *)malloc(sizeof(int) * vertexNum);
    // isFound = (bool *)malloc(sizeof(bool) * vertexNum);

    unsigned int curPoint; // TODO: change type

    vector<unsigned int> childList; // store the next node of the current node (to record the path of shortest path)
    vector<unsigned int> distanceArr; // store the distance between the start point and other nodes
    vector<bool> isFound;

    map<unsigned int, unsigned int> table; // return a table of path

    // allocate memory
    distanceArr.reserve(info.nodeNum);
    isFound.reserve(info.nodeNum);

    // for(int i = 0; i < vertexNum; i++) {
    //     distanceArr[i] = adjMatrix[0][i];
    //     isFound[i] = false;
    // }

    for(unsigned int i = 0; i < info.nodeNum; i++) {
        unsigned int tmp = info.isOld ? nodeList[root].oldNeighborList[i] : nodeList[root].newNeighborList[i];
        distanceArr.push_back(tmp);
        isFound[i] = false;
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
    distanceArr[root] = 0;
    for(unsigned int i = 0; i < info.nodeNum - 2; i++) {
        curPoint = getMin(distanceArr, vertexNum, isFound);
        isFound[curPoint] = true;
        for(int j = 0; j < info.nodeNum; j++)
            if(!isFound[j])
                if(distanceArr[curPoint] + adjMatrix[curPoint][j] < distanceArr[j])
                    distanceArr[j] = distanceArr[curPoint] + adjMatrix[curPoint][j];
    }

    return;
}

// TODO: change int to unsigned int
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

    unsigned minPos;
    unsigned int min = UINT_MAX;

    for(int i = 0; i < info.nodeNum; i++) {
        if(distanceArr.at(i) < min && !isFound.at(i)) {
            min = distanceArr[i];
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
        cin >> dstList[i];
}

vector<unsigned int> findPath(Info info, vector<node> nodeList)
{
    for(int i = 0; i < info.nodeNum; i++) {
        Dijkstra(info, nodeList, i); // TODO: change the definition of dijkstra function
    }
}