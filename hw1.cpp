#include <iostream>
#include <map>
#include <vector>

using namespace std;

class node {
    public:
        vector<unsigned int> oldNeighborList;
        vector<unsigned int> newNeighborList;
        // TODO: initialize the vectors
};

class Info {
    public:
        vector<int> dstList;
        int nodeNum;
        int dstNum;
        int linkNum;
        
        void initialize();
};

int *Dijkstra(Info info, vector<node> nodeList, map<unsigned int, unsigned int> table);

int getMin(int *distanceArr, int vertexNum, bool *isfound);

int main() {
    int linkId;
    int nodeId;
    int nodeId2;
    vector<node> nodeList; // nodes in the graph
    map<unsigned int, unsigned int> oldTable;
    map<unsigned int, unsigned int> newTable;
    Info info;

    // read the information of links
    for(int i = 0; i < info.linkNum; i++) {
        cin >> linkId; // what is the usage?
        cin >> nodeId;
        cin >> nodeId2;
        cin >> nodeList[nodeId].oldNeighborList[nodeId2];
        cin >> nodeList[nodeId].newNeighborList[nodeId2];
    }

    Dijkstra(info, nodeList, oldTable);
    Dijkstra(info, nodeList, newTable);


    for(int i = 0; i < info.nodeNum; i++) {
        cout << i << endl; // the Id of each start point
        for(int j = 0; j < info.dstNum; j++);
            // TODO: print out the old table and new table(changed entries)
    }

    return 0;
}

int *Dijkstra(Info info, vector<node> nodeList)
{   
    int *distanceArr;
    bool *isfound;
    int curPoint;

    distanceArr = (int *)malloc(sizeof(int) * vertexNum);
    isfound = (bool *)malloc(sizeof(bool) * vertexNum);
    for(int i = 0; i < vertexNum; i++) {
        distanceArr[i] = adjMatrix[0][i];
        isfound[i] = false;
    }
    
    isfound[0] = true;
    distanceArr[0] = 0;
    for(int i = 0; i < vertexNum - 2; i++) {
        curPoint = getMin(distanceArr, vertexNum, isfound);
        isfound[curPoint] = true;
        for(int j = 0; j < vertexNum; j++)
            if(!isfound[j])
                if(distanceArr[curPoint] + adjMatrix[curPoint][j] < distanceArr[j])
                    distanceArr[j] = distanceArr[curPoint] + adjMatrix[curPoint][j];
    }

    free(isfound);

    return distanceArr;
}

int getMin(int *distanceArr, int vertexNum, bool *isfound)
{
    int minPos = -1;
    int min = INT_MAX;

    for(int i = 0; i < vertexNum; i++) {
        if(distanceArr[i] < min && !isfound[i]) {
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