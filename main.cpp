#include <iostream>
#include "Graph.h"

using namespace std;


int main() {

    Graph<int> graph;


    graph.add_vertex(1);

    cout << graph.has_vertex(1);
    cout << endl << endl;
}