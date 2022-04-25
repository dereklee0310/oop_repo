#include <iostream>
#include <map>
#include <vector>
#include <climits>
#include <utility>

using namespace std;

class Node {
    public:
        vector<unsigned int> old_neighbor_list;
        vector<unsigned int> new_neighbor_list;
};

class Dest {
    public:
        unsigned int dest_point;
        map<unsigned int, unsigned int> old_table;
        map<unsigned int, unsigned int> new_table;
};

class Info {
    public:
        vector<Node> node_list;
        vector<Dest> dest_list;
        unsigned int node_num;
        unsigned int dest_num;
        unsigned int link_num;
        bool is_old;
        
        Info() : is_old(true) {};
        void Initialize();
        void PrintOldTable();
        void PrintNewTable();
};

void findPath(Info &info, vector<Node> node_list);

void Dijkstra(Info &info, vector<Node> node_list, unsigned int dest_idx);

unsigned int getMin(Info &info, vector<unsigned long> distance_arr, vector<bool> is_found);

int main() {
    //freopen("1.in","r",stdin);
    //freopen("output.txt","w",stdout);
    Info info;

    info.Initialize(); // read the data

    findPath(info, info.node_list);
    info.is_old = false; // change the state to find the new table instead
    findPath(info, info.node_list);

    info.PrintOldTable();
    info.PrintNewTable();

    return 0;
}

void findPath(Info &info, vector<Node> node_list)
{
    for(unsigned int i = 0; i < info.dest_num; i++)
        Dijkstra(info, node_list, i); // use the destinations as the root of shortest path tree 
}

void Dijkstra(Info &info, vector<Node> node_list, unsigned int dest_idx)
{   
    unsigned int root;
    unsigned int min_point;
    vector<unsigned long> distance_arr; // store the distance between the start point and other nodes
    vector<bool> is_found; // record the state of each node


    // initialize
    distance_arr.resize(info.node_num, UINT_MAX / 2);
    root = info.dest_list.at(dest_idx).dest_point;
    distance_arr.at(root) = 0;
    is_found.resize(info.node_num, false);

    if(info.is_old)
        info.dest_list.at(dest_idx).old_table[root] = root; // the next node of the destination is the destination itself
    else
        info.dest_list.at(dest_idx).new_table[root] = root;
    
    for(unsigned int i = 0; i < info.node_num - 1; i++) {
        min_point = getMin(info, distance_arr, is_found); // get the smallest node that have the shortest distance between root node

        is_found.at(min_point) = true;

        // update all distance between neighbor nodes and current point
        for(unsigned int j = 0; j < info.node_num; j++) {
            if(is_found.at(j))
                continue;
            if(info.is_old) {
                if(distance_arr.at(min_point) + node_list.at(min_point).old_neighbor_list.at(j) == distance_arr.at(j)) {
                    if(min_point < info.dest_list.at(dest_idx).old_table[j]) {
                        info.dest_list.at(dest_idx).old_table[j] = min_point;
                    }
                }
                if(distance_arr.at(min_point) + node_list.at(min_point).old_neighbor_list.at(j) < distance_arr.at(j)) {
                    distance_arr.at(j) = distance_arr.at(min_point) + node_list.at(min_point).old_neighbor_list.at(j);
                    info.dest_list.at(dest_idx).old_table[j] = min_point; // use [] operator to overwrite the old data
                }
            } else {
                if(distance_arr.at(min_point) + node_list.at(min_point).new_neighbor_list.at(j) == distance_arr.at(j)) {
                    if(min_point < info.dest_list.at(dest_idx).new_table[j]) {
                        info.dest_list.at(dest_idx).new_table[j] = min_point;
                    }
                }
                if(distance_arr.at(min_point) + node_list.at(min_point).new_neighbor_list.at(j) < distance_arr.at(j)) {
                    distance_arr.at(j) = distance_arr.at(min_point) + node_list.at(min_point).new_neighbor_list.at(j);
                    info.dest_list.at(dest_idx).new_table[j] = min_point; // use [] operator to overwrite the old data
                }
            }
                
        }
    }
}

unsigned int getMin(Info &info, vector<unsigned long> distance_arr, vector<bool> is_found)
{
    unsigned int minPos = 0;
    unsigned long min = LONG_MAX;

    for(unsigned int i = 0; i < info.node_num; i++) {
        if(distance_arr.at(i) < min && !is_found.at(i)) {
            min = distance_arr.at(i);
            minPos = i;
        }
    }
    return minPos;
}

void Info::Initialize()
{   
    unsigned int link_id;
    unsigned int node_1;
    unsigned int node_2;
    unsigned int weight;

    cin >> node_num >> dest_num >> link_num;
    dest_list.resize(dest_num);
    for(vector<Dest>::iterator itr = dest_list.begin(); itr != dest_list.end(); itr++)
        cin >> (*itr).dest_point;

    // allocate memory and initialize all entries to UINT_MAX / 2
    node_list.resize(node_num);
    for(vector<Node>::iterator itr = node_list.begin(); itr != node_list.end(); itr++) {
        (*itr).old_neighbor_list.resize(node_num, UINT_MAX / 2);
        (*itr).new_neighbor_list.resize(node_num, UINT_MAX / 2);
    }
    
    // read the relations between nodes
    for(unsigned int i = 0; i < link_num; i++) {
        cin >> link_id >> node_1 >> node_2;
        cin >> weight;
        node_list.at(node_1).old_neighbor_list.at(node_2) = weight;
        node_list.at(node_2).old_neighbor_list.at(node_1) = weight;
        cin >> weight;
        node_list.at(node_1).new_neighbor_list.at(node_2) = weight;
        node_list.at(node_2).new_neighbor_list.at(node_1) = weight;
    }
}

void Info::PrintOldTable()
{
    for(unsigned int i = 0; i < node_num; i++) {
        cout << i << endl; // simply print the node Id
        for(unsigned int j = 0; j < dest_num; j++)
            if(i != dest_list.at(j).dest_point) // if the node Id equals the destination, don't print it.
                cout << dest_list.at(j).dest_point << " " << dest_list.at(j).old_table[i] << endl;
    }
}
void Info::PrintNewTable()
{
    for(unsigned int i = 0; i < node_num; i++) {
        for(vector<Dest>::iterator itr = dest_list.begin(); itr != dest_list.end(); itr++) {
            if((*itr).old_table[i] != (*itr).new_table[i]) {
                cout << i << endl; // print the node Id if any path is changed
                break;
            }
        } 
        for(unsigned int k = 0; k < dest_num; k++) {
            if(dest_list.at(k).old_table[i] != dest_list.at(k).new_table[i]) // print the nodes that has been changed
                cout << dest_list.at(k).dest_point << " " << dest_list.at(k).new_table[i] << endl;
        }
    }
}