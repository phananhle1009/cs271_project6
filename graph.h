//============================================================
// Eleanor Murphy, Phan Anh Le, Khoa Ho
// April 2024
// graph.h
// This file contains the Graph class declaration.  
//============================================================

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector> 
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

template <typename D, typename K>
struct Node 
{
    D data;
    K key;
    Node* predecessor;
    int distance;
    string color;
};

template <typename D, typename K>
class Graph
{
    private:
            vector<K> keys;
            vector<D> data;
            vector<vector<K>> edges;
            vector<vector<Node<D, K>*>> pointers; 
            unordered_map<K, Node<D, K>*> vertex_map;
            unordered_map<K, char> color;
            unordered_map<K, int> discovery, finish;
            vector<Node<D,K>> vertices;
            int time;
    public:
                Graph     (void);
                Graph     (const Graph<D,K> &myGraph);
                Graph     (vector<K> keys, vector<D> data, vector<vector<K>> edges);
                ~Graph    (void); 
    Node<D, K>* get       (K k); 
    bool        reachable (K u, K v); 
    void        bfs       (K s); 
    void        print_path(K u, K v); 
    void        print_path_helper(K u, K v);
    string      edge_class(K u, K v); 
    void        bfs_tree  (K s); 
    void        dfs       (K s);
    void        dfs_helper(K u);


};

#endif
