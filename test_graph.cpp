//
//  test_graph_example.cpp
//  CS 271 Graph Project: Example Test File
//
//  Created by Dr. Stacey Truex, Khoa Ho, Eleanor Murphy, Phan Anh Le
//

#include <fstream>
#include <sstream>
#include "graph.cpp"

Graph<string, string> *generate_graph(string fname)
{
    string line;
    ifstream infile(fname);
    vector<string> keys = {};
    vector<string> data = {};
    vector<vector<string>> adjs = {};
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            size_t delim = line.find(":");
            string key = line.substr(0, delim);
            string adj = line.substr(delim + 1);

            keys.push_back(key);
            data.push_back(key + " data");
            delim = adj.find(",");
            vector<string> adj_lst = {};
            while (delim != string::npos)
            {
                adj_lst.push_back(adj.substr(0, delim));
                adj = adj.substr(delim + 1);
                delim = adj.find(",");
            }
            adj_lst.push_back(adj);
            adjs.push_back(adj_lst);
        }
        infile.close();
    }
    Graph<string, string> *G = new Graph<string, string>(keys, data, adjs);
    return G;
}



void test_get(Graph<string, string> *G)
{
    try
    {
        if (G->get("S") == nullptr || G->get("S")->data != "S data")
        {
            cout << "Incorrect result getting vertex \"s\"" << endl;
        }
        if (G->get("a") != nullptr)
        {
            cout << "Incorrect result getting non-existant vertex \"a\"" << endl;
        }
        if (G->get("T") == nullptr || G->get("T")->key != "T")
        {
            cout << "Incorrect result getting vertex \"T\"" << endl;
        }
        if (G->get("X") == nullptr || G->get("X")->data != "X data")
        {
            cout << "Incorrect result getting vertex \"X\"" << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }
}
void test_get_new()
{
    // int and string
    try {
        vector<int> keys;
        vector<string> data;
        vector<vector<int>> edges(4); 
        Graph<string, int> emptyGraph(keys, data, edges);
        if (emptyGraph.get(1) != nullptr) {
            cout << "Error: Expected nullptr for vertex '1' in empty graph, but found a vertex." << endl;
        }
        keys = {1, 2, 3, 4};
        data = {"apple", "banana", "cat", "dog"};
        Graph<string, int> G(keys, data, edges);
        Node<string, int>* nodeA = G.get(1);
        if (nodeA == nullptr || nodeA->key != 1 || nodeA->data != "apple") {
            cout << "Error: Incorrect result getting vertex '1'. Expected key '1' and data 'apple'." << endl;
        }
        Node<string, int>* nodeB = G.get(2);
        if (nodeB == nullptr || nodeB->key != 2 || nodeB->data != "banana") {
            cout << "Error: Incorrect result getting vertex '2'. Expected key '2' and data 'banana'." <<endl ;
        }
        if (G.get('E') != nullptr) {
            cout << "Error: Expected nullptr for vertex 'E', but found a vertex." << endl;
        }
    }
        catch (exception &e)
    {
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }

    // char and float
        try {
        vector<char> keys;
        vector<float> data;
        vector<vector<char>> edges(4); 
        Graph<float, char> emptyGraph(keys, data, edges);
        if (emptyGraph.get('A') != nullptr) {
            cout << "Error: Expected nullptr for vertex 'A' in empty graph, but found a vertex." << endl;
        }
        keys = {'A', 'B', 'C', 'D'};
        data = {1.1f, 2.1f, 3.1f, 4.1f};
        Graph<float, char> G(keys, data, edges);
        Node<float, char>* nodeA = G.get('A');
        if (nodeA == nullptr || nodeA->key != 'A' || nodeA->data != 1.1f) {
            cout << "Error: Incorrect result getting vertex 'A'. Expected key 'A' and data '1.1'." << endl;
        }
        Node<float, char>* nodeB = G.get('B');
        if (nodeB == nullptr || nodeB->key != 'B' || nodeB->data != 2.1f) {
            cout << "Error: Incorrect result getting vertex 'B'. Expected key 'B' and data '2.1'."<< endl;
        }
        if (G.get('E') != nullptr) {
            cout << "Error: Expected nullptr for vertex 'E', but found a vertex." << endl;
        }
    }
        catch (exception &e)
    {
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }
}



void test_reachable(Graph<string, string> *G)
{
    try
    {
        if (!G->reachable("R", "V"))
        {
            cout << "Incorrectly identified adjacent vertex \"V\" as unreachable from \"R\"" << endl;
        }
        if (!G->reachable("X", "W"))
        {
            cout << "Incorrectly identified \"W\" as unreachable from \"X\"" << endl;
        }
        if (G->reachable("S", "A"))
        {
            cout << "Incorrectly identified non-existant vetex \"A\" as reachable from \"S\"" << endl;
        }
        if (G->reachable("R", "T"))
        {
            cout << "Incorrectly identified vertex T as reachable from vertex R" << endl;
        }
        if (!G->reachable("X", "X"))
        {
            cout << "Inccorectly identified X as not reachable from X, when there exists a path" << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing reachable : " << e.what() << endl;
    }
}
void test_reachable_new()
{
    // string and float
        try {
        vector<string> keys{"apple", "banana", "cat", "dog"};
        vector<float> data{3.1, 2.1, 1.1, -0.1};
        vector<vector<string>> edges{{"banana", "dog"}, {"cat"}, {"dog"}, {}}; // Adjacency list for each vertex.

        Graph<float, string> G_new(keys, data, edges);

        if(!G_new.reachable("apple", "banana")) {
            cerr << "Incorrectly identified adjacent vertex \"apple\" as unreachable from \"banana\"" << endl;
        }
        if(!G_new.reachable("banana", "cat")) {
            cerr << "Incorrectly identified adjacent vertex \"banana\" as unreachable from \"cat\"" << endl;
        }
        if(G_new.reachable("cat", "banana")) {
            cerr << "Incorrectly identified non-existant vetex \"cat\" as reachable from \"banana\"" << endl;
        }
        if(G_new.reachable("dog", "banana")) {
            cerr << "Incorrectly identified non-existant vetex \"dog\" as reachable from \"banana\"" << endl;
        }
        if(G_new.reachable("egg", "banana")) {
            cerr << "Incorrectly identified non-existant vetex \"egg\" as reachable from \"banana\"" << endl;
        }
        if(!G_new.reachable("banana","banana")) {
            cerr << "Incorrectly identified adjacent vertex \"banana\" as unreachable from \"banana\"" << endl;
        }
    } catch (exception &e) {
        cerr << "Error testing reachable: " << e.what() << endl;
    }

        // char and int
        try {
        vector<char> keys{'A', 'B', 'C', 'D'};
        vector<int> data{3, 2, 1, 4};
        vector<vector<char>> edges{{'B', 'D'}, {'C'}, {'D'}, {}}; // Adjacency list for each vertex.

        Graph<int, char> G_new1(keys, data, edges);

        if(!G_new1.reachable('A', 'B')) {
            cerr << "Incorrectly identified adjacent vertex \"A\" as unreachable from \"B\"" << endl;
        }
        if(!G_new1.reachable('B', 'C')) {
            cerr << "Incorrectly identified adjacent vertex \"B\" as unreachable from \"C\"" << endl;
        }
        if(G_new1.reachable('C', 'B')) {
            cerr << "Incorrectly identified non-existant vetex \"C\" as reachable from \"B\"" << endl;
        }
        if(G_new1.reachable('D', 'B')) {
            cerr << "Incorrectly identified non-existant vetex \"D\" as reachable from \"B\"" << endl;
        }
        if(G_new1.reachable('E', 'B')) {
            cerr << "Incorrectly identified non-existant vetex \"E\" as reachable from \"B\"" << endl;
        }
        if(!G_new1.reachable('B','B')) {
            cerr << "Incorrectly identified adjacent vertex \"B\" as unreachable from \"B\"" << endl;
        }
    } catch (exception &e) {
        cerr << "Error testing reachable: " << e.what() << endl;
    }
}


void test_bfs(Graph<string, string> *G)
{
    //string and int 
    try
    {
        G->bfs("T");
        string vertices[8] = {"V", "R", "S", "W", "T", "X", "U", "Y"};
        int distances[8] = {3, 2, 1, 1, 0, 2, 1, 2};
        for (int i = 0; i < 8; i++)
        {
            if (G->get(vertices[i]) == nullptr || G->get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"t\"" << endl;
            }
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs : " << e.what() << endl;
    }
}

void test_bfs_new()
{
    // char and float
    try {
        vector<char> keys{'V', 'R', 'S', 'W', 'T', 'X', 'U', 'Y'};
        vector<float> data{3.0f, 2.0f, 1.0f, 1.0f, 0.0f, 2.0f, 1.0f, 2.0f};
        vector<vector<char>> edges{{'R', 'S'}, {'V', 'W'}, {'W', 'X'}, {'T', 'U'}, {'U', 'Y'}, {}, {'X'}, {'X', 'V'}};

        Graph<float, char> G(keys, data, edges);
        G.bfs('T');
        int expected_distances[8] = {3, 2, 1, 1, 0, 2, 1, 2};
        for (int i = 0; i < 8; i++) {
            Node<float, char>* node = G.get(keys[i]);
            if (node == nullptr || node->distance != expected_distances[i]) {
                cout << "Incorrect bfs result. Vertex " << keys[i] << " should have distance " << expected_distances[i] << " from source vertex 'T'" << endl;
            }
        }
    }   catch (exception &e) {
        cerr << "Error testing bfs: " << e.what() << endl;
    }

    //int and char
    try {
        vector<int> keys{1, 2, 3, 4, 5, 6, 7, 8};  
        vector<char> data{'V', 'R', 'S', 'W', 'T', 'X', 'U', 'Y'};  
        vector<vector<int>> edges{{2, 3}, {1, 4}, {4, 6}, {5, 7}, {7, 8}, {}, {6}, {6, 1}};
        Graph<char, int> G(keys, data, edges);
        G.bfs(5);  
        int expected_distances[8] = {3, 2, 1, 1, 0, 2, 1, 2};
        for (int i = 0; i < 8; i++) {
            Node<char, int>* node = G.get(keys[i]);
            if (node == nullptr || node->distance != expected_distances[i]) {
                cout << "Incorrect bfs result. Vertex " << keys[i] << " should have distance " << expected_distances[i] << " from source vertex 'T'" << endl;
            }
        }
    } catch (exception &e) {
        cerr << "Error testing bfs: " << e.what() << endl;
    }

    //float and string
    try {
        vector<float> keys{1.1f, 2.1f, 3.1f, 4.1f, 5.1f, 6.1f, 7.1f, 8.1f};  
        vector<string> data{"V", "R", "S", "W", "T", "X", "U", "Y"};  
        vector<vector<float>> edges{{2.1f, 3.1f}, {1.1f, 4.1f}, {4.1f, 6.1f}, {5.1f, 7.1f}, {7.1f, 8.1f}, {}, {6.1f}, {6.1f, 1.1f}};
        Graph<string, float> G(keys, data, edges);
        G.bfs(5.1);  
        int expected_distances[8] = {3, 2, 1, 1, 0, 2, 1, 2};
        for (int i = 0; i < 8; i++) {
            Node<string, float>* node = G.get(keys[i]);
            if (node == nullptr || node->distance != expected_distances[i]) {
                cout << "Incorrect bfs result. Vertex " << keys[i] << " should have distance " << expected_distances[i] << " from source vertex 'T'" << endl;
            }
        }
    } catch (exception &e) {
        cerr << "Error testing bfs: " << e.what() << endl;
    }
}


void test_print_path(Graph<string, string> *G)
{
    //string
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path("T", "V");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T -> S -> R -> V")
        {
            cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: T -> S -> R -> V but got : " << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}
void test_print_path_new(Graph<char, char> *G)
{
    //char
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path('T', 'V');
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T -> S -> R -> V")
        {
            cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: T -> S -> R -> V but got : " << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }
    
}

void test_edge_class(Graph<string, string> *G)
{
    try
    {
        string e_class = G->edge_class("R", "V"); // tree edge
        if (e_class != "tree edge")
        {
            cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
        }
        e_class = G->edge_class("X", "U"); // back edge
        if (e_class != "back edge")
        {
            cout << "Misidentified back edge (\"X\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("R", "U"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "W"); // forward edge
        if (e_class != "forward edge")
        {
            cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "S"); // cross edge
        if (e_class != "cross edge")
        {
            cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
}

void test_edge_class_new(Graph<char, char> *G)
{
    //char 
    try
    {
        string e_class = G->edge_class('R', 'V'); // tree edge
        if (e_class != "tree edge")
        {
            cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
        }
        e_class = G->edge_class('X', 'U'); // back edge
        if (e_class != "back edge")
        {
            cout << "Misidentified back edge (\"X\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class('R', 'U'); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class('T', 'W'); // forward edge
        if (e_class != "forward edge")
        {
            cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
        }
        e_class = G->edge_class('T', 'S'); // cross edge
        if (e_class != "cross edge")
        {
            cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
}

void test_bfs_tree(Graph<string, string> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("T");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T\nS U W\nR Y X\nV")
        {
            cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n"
                 << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
}
void test_bfs_tree_new()
{
    //int
    try {
    vector<int> keys{1, 2, 3, 4};
    vector<string> data{"A", "B", "C", "D"};
    vector<vector<int>> edges{{2, 4}, {3}, {4}, {}};

    Graph<string, int> G(keys, data, edges);

    stringstream buffer;
    streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
    G.bfs_tree(2);
    cout.rdbuf(prevbuf);

    string expectedOutput = "2\n3\n4\n";
    if (buffer.str() != expectedOutput) {
        cout << "Incorrect bfs tree. Expected:\n" << expectedOutput << "but got:\n" << buffer.str() << endl;
    }
} catch (exception &e) {
    cerr << "Error testing bfs tree: " << e.what() << endl;
}
    // char
    try {
    vector<char> keys{'A', 'B', 'C', 'D'};
    vector<string> data{"A", "B", "C", "D"};
    vector<vector<char>> edges{{'B'}, {'C'}, {'D'}, {}};

    Graph<string, char> G(keys, data, edges);

    stringstream buffer;
    streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
    G.bfs_tree('A');
    cout.rdbuf(prevbuf);

    string expectedOutput = "A\nB\nC\nD\n";
    if (buffer.str() != expectedOutput) {
        cout << "Incorrect bfs tree. Expected:\n" << expectedOutput << "but got:\n" << buffer.str() << endl;
    }
} catch (exception &e) {
    cerr << "Error testing bfs tree: " << e.what() << endl;
}

    //float
    try {
    vector<float> keys{1.1f, 2.1f, 3.1f, 4.1f};
    vector<string> data{"A", "B", "C", "D"};
    vector<vector<float>> edges{{2.1f, 4.1f}, {3.1f}, {4.1f}, {}};

    Graph<string, float> G(keys, data, edges);

    stringstream buffer;
    streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
    G.bfs_tree(2);
    cout.rdbuf(prevbuf);

    string expectedOutput = "2.1\n3.1\n4.1\n";
    if (buffer.str() != expectedOutput) {
        cout << "Incorrect bfs tree. Expected:\n" << expectedOutput << "but got:\n" << buffer.str() << endl;
    }
} catch (exception &e) {
    cerr << "Error testing bfs tree: " << e.what() << endl;
}
}

int main()
{

    Graph<string, string> *G = generate_graph("graph_description.txt");
    test_get(G);
    // test_get_new();
    test_reachable(G);
    // test_reachable_new();
    test_bfs(G);
    // test_bfs_new();
    // test_print_path(G);
    // test_print_path_new(G); 
    test_edge_class(G);
    // test_edge_class_new(G);
    test_bfs_tree(G);
    // test_bfs_new();
    cout << "Testing completed" << endl;

    delete G;

    return 0;
}