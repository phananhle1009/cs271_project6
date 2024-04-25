//=================================
// Eleanor Murphy, Phan Anh Le, Khoa Ho
// graph.cpp
// April 2024
// This file contains the class template implementation for the Graph class
//=================================

#include "graph.h"
#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

//==============================================================
// default constructor
// Pre-condition: None
// Post-condition: An empty Graph is created
// Parameters: None
// Return Value: None
//==============================================================
template <typename D, typename K>
Graph<D,K>::Graph()
{ 
    // Initialize all variables to default
    keys;
    edges;
    data;
    pointers;
    vertices;
}

//==============================================================
// copy constructor
// Pre-condition: Properly initiallized graph
// Post-condition: Deep-copied new graph, the original graph is not affected
// Parameters: const Graph<D, K>& myGraph, graph to be copied
// Return Value: None
//==============================================================
template<typename D, typename K>
Graph<D, K>::Graph(const Graph<D, K>& myGraph) 
{
    // Copying data
    this->keys = myGraph.keys;
    this->data = myGraph.data;
    this->edges = myGraph.edges;

    // Initialize the pointers vector of vectors
    this->pointers.resize(myGraph.pointers.size());         // Ensure the new adjacency list has the same number of elements.
    // Copy each vector of Node pointers
    for (size_t i = 0; i < myGraph.pointers.size(); ++i)    
    {
        this->pointers[i].resize(myGraph.pointers[i].size());
        for (size_t j = 0; j < myGraph.pointers[i].size(); ++j) // Iterate over each node pointer in the adjacency list.
        {
            // Deep copy of nodes
            Node<D, K>* newNode = new Node<D, K>; // Create a new node on the heap to ensure a deep copy.
            *newNode = *myGraph.pointers[i][j];  
            this->pointers[i][j] = newNode;
        }
    }
}


//==============================================================
// parameterized constructor
// 	
// Pre-condition: None
// Post-condition: A graph is created with the specified keys and edges
//
// Parameters: vector<K> keys, vector<vector<K>> edges
// Return Value: None
//==============================================================

template <typename D, typename K>
Graph<D,K>::Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges) : keys(keys), data(data), edges(edges)
{
    for(int i = 0; i < keys.size(); i++) // Go through every key in the graph
    {
        // Create a Node object with data and key values
        Node<D,K> temp;
        temp.data = data[i];
        temp.key = keys[i];
        vertices.insert(vertices.begin() + i, temp); // Insert the Node object into vector of vertices in correct position

    }
}



//==============================================================
// destructor
// Pre-condition: Properly iniallized graph with dynamically allocated memory
// Post-condition: All dynamically allocated memory associated with the graph is freed
// Parameters: None
// Return Value: None
//============================================================== 
template <class D, class K>
Graph<D, K>::~Graph(void) 
{
    vertices.clear(); // Clear the vertices vector of created nodes
}


// ================================================================================
// get
// Pre-condition: Properly initiallized graph with valid pointers to nodes. 
// Post-condition: Returns a pointer to the graph node with the specified key k if found; otherwise, returns nullptr.
// Parameters: K k, the key to be found
// Return Value: pointer to Node object with key k
// ================================================================================
template <typename D, typename K>
Node<D, K>* Graph<D,K>::get(K k)
{
    int index = find(keys.begin(), keys.end(), k) - keys.begin(); // Find index of key k in keys vector
    if(find(keys.begin(), keys.end(), k) != keys.end()) // Check to see if key was found in graph
    {
        Node<D, K> *ptr = &vertices[index]; // Create a pointer pointed to the Node object in vertices vector at that index
        return ptr;
    }
    else
    {
        return nullptr; // Return a nullptr if key was not found
    }
}
    


//==============================================================
// reachable
// Pre-condition: Properly innitiallized graph, and vertices u and v must exist in the graph
// Post-condition: Returns true if there exists a path from vertex with key u to the vertex with key v, 
// and false otherwise. Empty graph or invalid u v keys returns false.
// Parameters: K u, K v
// Return Value: true is vertex with key v is reachable from vertex with key u, false otherwise
//==============================================================
template<typename D, typename K>
bool Graph<D, K>::reachable(K u, K v) 
{
    queue<K> queue;        // Initialize a queue to hold the vertices to be explored next.
    unordered_map<K, bool> visited;    // Track which vertices have been visited.
    queue.push(u);
    visited[u] = true;  // Mark the starting vertex as visited.

    while (!queue.empty())
    {
        K current = queue.front();  // Retrieve and remove the front vertex from the queue.
        queue.pop();

        // Find the index of the current vertex in the list of keys.
        int index = find(keys.begin(), keys.end(), current) - keys.begin();
        if (index >= keys.size())
        {
            continue;
        }
        for (auto neighbor : edges[index]) 
        {
            // If the neighbor is the target vertex v, return true that v is reachable from u.
            if (neighbor == v) 
            {
                return true;
            }
            if (!visited[neighbor]) // If this neighbor has not been visited, mark it as visited and add it to the queue.
            {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }
    // Return false if no path was found from u to v.
    return false;
}

//==============================================================
// bfs
// Pre-condition: Properly innitiallized graph, and source node must exist in the graph
// Post-condition: The breadth-first search algorithm is executed from the source node
// Parameters: K s, source for bfs
// Return Value: None
//==============================================================
template <class D, class K>
void Graph<D, K>::bfs(K k) {
    Node<D, K>* s = get(k);
    if(s == nullptr) { 
      return; 
    }

    // iterate through list of vector of node pointers
    for (int i = 0; i < pointers.size(); i++) {
        // iterate through each node pointer within the vector at pointers[i]
        for (int j = 0; j < pointers[i].size(); j++) {
            pointers[i][j]->color = "WHITE"; // not visited
            pointers[i][j]->distance = -1; // distance initialized to -1
            pointers[i][j]->predecessor = nullptr; // starting node does not have a predecessor
        }
    }
    
    s->color = "GRAY"; // discovered but not fully explored
    s->distance = 0; // distance initialized to 0
    s->predecessor = nullptr; // starting node does not have a predecessor

    // use queue to manage the order of visiting nodes
    queue<K> Q;
    Q.push(s->key); // enqueue the key of the starting node
    
    while(!Q.empty()) {
        K current_key = Q.front(); // get the key of the current front node
        Node<D, K>* u = get(current_key); // node associated with the current key
        Q.pop(); // dequeue the current node's key

        // get the index of the current node in the list of keys
        int u_index = distance(keys.begin(), find(keys.begin(), keys.end(), u->key));
        // iterate through the neighbors of the current node
        for(K neighbor_key : edges[u_index]) {
            Node<D, K>* v = get(neighbor_key);
            if(v != nullptr && v->color == "WHITE"){ // if the neighbor node exists and is not visited
                v->color = "GRAY"; // discovered but not fully explored
                v->distance = u->distance + 1; // set distance from starting node
                v->predecessor = u; // set predecessor to the current node
                Q.push(v->key); // enqueue neighbor's key
            }
        }
        u->color = "BLACK"; // fully explored
    }
}

//==============================================================
// print_path
// Pre-condition: Properly innitiallized graph, and valid vertices u and v must exist in the graph
// Post-condition: If a path exists from vertex u to v, the function prints the path in the correct order, else do nothing
// Parameters: K u, K v
// Return Value: None
//==============================================================
template <typename D, typename K>
void Graph<D,K>::print_path(K u, K v)
{
    bfs(u); // Call bfs to create the tree structure
    print_path_helper(u, v); // Call helper function
}

//==============================================================
// print_path_helper
// Pre-condition: Properly innitiallized graph, and valid vertices u and v must exist in the graph
// Post-condition: Prints the path in the correct order if a path exists from vertex u to v, else do nothing
// Parameters: K u, K v
// Return Value: None
//==============================================================
template <typename D, typename K>
void Graph<D,K>::print_path_helper(K u, K v)
{
    Node<D,K> temp = *get(v); // Create a pointer to the key of v
    if(v == u) // Base case for only one vertex in path
    {
        cout << u;
    }
    else if (temp.predecessor == NULL) // If the vertex has no predecessor, there exists no path
    {
        cout << "no path" << endl;
    }
    else{
        print_path_helper(u, temp.predecessor->key); // Recurse with the predecessor of temp variable
        cout << " -> "; // Print the arrows
        cout << v; // Print the current key
    }
}

//==============================================================
// edge class
// Pre-condition: Properly innitiallized graph, and valid vertices u and v must exist and bereachable in the graph
// Post-condition: Returns a string indicating the type of edge between vertices u and v in the graph 
// Parameters: K u, K v
// Return Value: string
//==============================================================
template <typename D, typename K>
string Graph<D,K>::edge_class(K u, K v)
{
    auto& vertex_u = this->vertices[u]; // Assuming vertices is a map from K to vertex struct
    auto& vertex_v = this->vertices[v]; // Assuming vertices is a map from K to vertex struct

    if (vertex_u.discovery < vertex_v.discovery) {
        if (vertex_v.predecessor == u) {
            return "tree edge"; // v was discovered from u
        } else {
            return "forward edge"; // v is a descendant but not directly via u
        }
    } else if (vertex_u.discovery > vertex_v.discovery) {
        if (vertex_v.color == "GRAY") {
            return "back edge"; // v is an ancestor of u
        } else {
            return "cross edge"; // v is neither an ancestor nor a descendant
        }
    }
    return "no edge"; // Catch-all for any missed conditions
}

//==============================================================
// bfs_tree
// Pre-condition: Properly innitiallized graph and valid inputs
// Post-condition: The BFS tree with valid level order, starting from source vertex s
// Parameters: K s, source for bfs
// Return Value: None
//==============================================================
template <typename D, typename K>
void Graph<D,K>::bfs_tree(K s)
{
    bfs(s); // Call bfs to create implicit structure
    
    for(int dist = 0; dist < keys.size(); dist++) // Go through each distance level
    {
        for (int i = 0; i < vertices.size(); i++) // Go through each vertex
        {
            if(get(keys[i])->distance == dist) // Check to see if each vertex is at that distance level
            {
                cout << keys[i] << " "; // Print that key and a space
            }
        }
        cout << endl; // Create a new line after each distance level
    }
    

}

//==============================================================
// dfs
// Pre-condition: Properly innitiallized graph and valid inputs
// Post-condition: The depth-first search algorithm is executed from the source node
// Parameters: K s, source for dfs
// Return Value: None
//==============================================================
template <typename D, typename K>
void Graph<D,K>::dfs(K s)
{
    // Clearing previous state before starting new DFS.
    color.clear();
    discovery.clear();
    finish.clear();
    time = 0;  // Resetting time to zero for the new DFS run.

    // Initialize each vertex's state and map each vertex to its corresponding Node object.
    for (K key : keys) {
        color[key] = "WHITE";  // All vertices are unvisited.
        vertex_map[key] = pointers[find(keys.begin(), keys.end(), key) - keys.begin()][0];
    }

    // Start DFS from vertex s if it is unvisited.
    if (color[s] == "WHITE") {
        dfs_helper(s);  // Call the recursive helper function to perform DFS.
    }
}

//==============================================================
// dfs_helper
// Pre-condition: Properly innitiallized graph and valid inputs
// Post-condition: The recursive helper function for the DFS algorithm
// Parameters: K u
// Return Value: None
//==============================================================
template <typename D, typename K> 
void Graph<D,K>::dfs_helper (K u)
{
    color[u] = "GRAY";  // Mark vertex u as discovered
    discovery[u] = time++;  // Set discovery time and increment the global timd

    // Explore all neighbors of vertex u.
    for (Node<D, K>* neighbor : pointers[find(keys.begin(), keys.end(), u) - keys.begin()]) 
    {
        K neighborKey = neighbor->key;
        // If the neighbor has not been visited, proceed to explore it
        if (color[neighborKey] == "WHITE") 
        {
            neighbor->predecessor = vertex_map[u];  // Set the predecessor for path reconstruction.
            dfs_helper(neighborKey);  // Recursively explore the neighbor
        }
    }
    color[u] = "BLACK";  // Mark vertex u as explored.
    finish[u] = time++;  // Set the finish time and increment the global time.
}
