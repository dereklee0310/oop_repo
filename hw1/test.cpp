#include <iostream>
#include <map>
#include <vector>
#include <climits>
#include <utility>

#define MAX 4096

using namespace std;

// signle node in the routing table
class Node {
    public:
        vector<unsigned int> old_neighbor_list, new_neighbor_list;
        map<unsigned int, unsigned int> old_table, new_table;
};

// record of destinations and their corresponding tables
class Dest {
    public:
        unsigned int dest_point;
};

// info of the routing table
class Info {
    public:
        vector<Node> node_list;
        vector<Dest> dest_list;
        unsigned int node_num, dest_num, link_num;
        bool is_old;
        
        Info() : is_old(true) {};
        void Initialize();
};

// operation on routing table
class Ctrl {
    public:
        void findPath(Info &info, vector<Node> &node_list);
        void Dijkstra(Info &info, vector<Node> &node_list, unsigned int dest_idx);
        unsigned int getMin(Info &info, vector<unsigned long> distance_arr, vector<bool> is_found);
        void PrintOldTable(Info info);
        void PrintNewTable(Info info);
};

int main() {
    Info info;
    Ctrl controller;

    // freopen("1.in","r",stdin);
    // freopen("output.txt","w",stdout);

    info.Initialize(); // read the data

    controller.findPath(info, info.node_list);
    info.is_old = false; // change the state to find the new table instead
    controller.findPath(info, info.node_list);

    controller.PrintOldTable(info);
    controller.PrintNewTable(info);

    return 0;
}

void Ctrl::findPath(Info &info, vector<Node> &node_list)
{
    for(unsigned int i = 0; i < info.dest_num; i++)
        Dijkstra(info, node_list, i); // use the destinations as the root of shortest path tree 
}

void Ctrl::Dijkstra(Info &info, vector<Node> &node_list, unsigned int dest_idx)
{   
    unsigned int root;
    unsigned int min_point;
    vector<unsigned long> distance_arr; // store the distance between the start point and other nodes
    vector<bool> is_found; // record the state of each node

    // initialize
    distance_arr.resize(info.node_num, MAX);
    root = info.dest_list.at(dest_idx).dest_point;
    distance_arr.at(root) = 0;
    is_found.resize(info.node_num, false);

    // if(info.is_old)
    //     info.dest_list.at(dest_idx).old_table[root] = root; // the next node of the destination is the destination itself
    // else
    //     info.dest_list.at(dest_idx).new_table[root] = root;

    if(info.is_old)
        node_list.at(root).old_table[dest_idx] = root; // the next node of the destination is the destination itself
    else
        node_list.at(root).new_table[dest_idx] = root;

    
    
    for(unsigned int i = 0; i < info.node_num - 1; i++) {
        min_point = getMin(info, distance_arr, is_found); // get the smallest node that have the shortest distance between root node
        is_found.at(min_point) = true;

        // update all distance between neighbor nodes and current point
        for(unsigned int j = 0; j < info.node_num; j++) {
            if(is_found.at(j))
                continue;
            if(info.is_old) {
                if(distance_arr.at(min_point) + node_list.at(min_point).old_neighbor_list.at(j) == distance_arr.at(j)) {
                    if(min_point < node_list.at(j).old_table[dest_idx]) {
                        node_list.at(j).old_table[dest_idx] = min_point;
                    }
                }
                if(distance_arr.at(min_point) + node_list.at(min_point).old_neighbor_list.at(j) < distance_arr.at(j)) {
                    distance_arr.at(j) = distance_arr.at(min_point) + node_list.at(min_point).old_neighbor_list.at(j);
                    node_list.at(j).old_table[dest_idx] = min_point; // use [] operator to overwrite the old data
                }
            } else {
                if(distance_arr.at(min_point) + node_list.at(min_point).new_neighbor_list.at(j) == distance_arr.at(j)) {
                    if(min_point < node_list.at(j).new_table[dest_idx]) {
                        node_list.at(j).new_table[dest_idx] = min_point;
                    }
                }
                if(distance_arr.at(min_point) + node_list.at(min_point).new_neighbor_list.at(j) < distance_arr.at(j)) {
                    distance_arr.at(j) = distance_arr.at(min_point) + node_list.at(min_point).new_neighbor_list.at(j);
                    node_list.at(j).new_table[dest_idx] = min_point; // use [] operator to overwrite the old data
                }
            }
        }
    }
}

unsigned int Ctrl::getMin(Info &info, vector<unsigned long> distance_arr, vector<bool> is_found)
{
    unsigned int minPos = 0;
    unsigned long min = MAX;

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
    for(auto &itr : dest_list)
        cin >> itr.dest_point;

    // allocate memory and initialize all entries to MAX
    node_list.resize(node_num);
    for(auto &itr : node_list) {
        itr.old_neighbor_list.resize(node_num, MAX);
        itr.new_neighbor_list.resize(node_num, MAX);
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

void Ctrl::PrintOldTable(Info info)
{
    for(unsigned int i = 0; i < info.node_num; i++) {
        cout << i << endl; // simply print the node Id
        for(unsigned int j = 0; j < info.dest_num; j++) {
            unsigned int dest = info.dest_list.at(j).dest_point;
            if(i != dest) // if the node Id equals the destination, don't print it.
                cout << dest << " " << info.node_list.at(i).old_table[j] << endl;
        }
    }
}
void Ctrl::PrintNewTable(Info info)
{    

    for(unsigned int i = 0; i < info.node_num; i++) {
        for(unsigned int j = 0; j < info.dest_num; j++) {
            if(info.node_list.at(i).old_table[j] != info.node_list.at(i).new_table[j]) {
                cout << i << endl; // print the node Id if any path is changed
                break;
            }
        } 
        for(unsigned int j = 0; j < info.dest_num; j++) {
            unsigned int dest = info.dest_list.at(j).dest_point;
            if(i != info.dest_list.at(j).dest_point && info.node_list.at(i).old_table[j] != info.node_list.at(i).new_table[j]) // print the nodes that has been changed
                cout << dest << " " << info.node_list.at(i).new_table[j] << endl;
        }
    }
}