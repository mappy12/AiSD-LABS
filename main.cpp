#include <iostream>
#include "Graph.h"


int main() {

    Graph<string, double> g;


    g.add_vertex("A");
    g.add_vertex("B");
    g.add_vertex("C");
    g.add_vertex("D");
    g.add_vertex("E");

    cout << "Вершины: ";
    g.print_vertices(); 

    g.add_edge("A", "B", 13.0);
    g.add_edge("A", "C", 4.0);
    g.add_edge("B", "C", 10.0);
    g.add_edge("C", "D", 4.0);
    g.add_edge("E", "A" , 5.0);
    g.add_edge("E", "E", 8.0);

    cout << "Граф после добавления ребер: " << endl << endl;

    g.print();

    cout << "Проверка наличия вершин: " << endl << endl;

    cout << "Есть ли вершина 'A' ?   " << g.has_vertex("A") << endl;
    cout << "Есть ли вершина 'E' ?   " << g.has_vertex("E") << endl;
    cout << "Есть ли вершина 'F' ?   " << g.has_vertex("F") << endl << endl;

    cout << "Проверка наличия ребер: " << endl << endl;

    cout << "Есть ли ребро A -> E ?   " << g.has_edge("A", "E") << endl;
    cout << "Есть ли ребро B -> C ?   " << g.has_edge("B", "C") << endl;
    cout << "Есть ли ребро E -> A ?   " << g.has_edge("E", "A") << endl << endl;

    cout << "Удаление вершины: " << endl << endl;

    cout << "Удалена вершина D. Так ли это?   " << g.remove_vertex("D") << endl << endl;
    cout << "Граф после удаления вершины D: " << endl << endl;
    g.print();

    cout << "Удаление ребра: " << endl << endl;

    cout << "Удалено ребро C -> D. Так ли это?   " << g.remove_edge("C", "D") << endl << endl;
    cout << "Граф после удаления ребра C -> D: " << endl << endl;
    g.print();

    cout << "Порядок графа: " << g.order() << endl << endl;

    cout << "Проверка степени вершины: " << endl << endl;

    cout << "Вершина B: " << g.degree("B") << endl;
    cout << "Вершина C: " << g.degree("C") << endl;
    cout << "Вершина A: " << g.degree("A") << endl << endl;


    cout << "Проверка связности графа: " << endl << endl;

    cout << "Является ли граф 'g' сильно-связным ?   " << g.is_connected() << endl;
    Graph<string, int> g1;

    g1.add_vertex("A");
    g1.add_vertex("B");

    g1.add_edge("A", "B", 3.0);
    g1.add_edge("B", "A", 10.0);

    cout << "Является ли граф 'g1' сильно-связным ?   " << g1.is_connected() << endl << endl;

    cout << "Нахождение кратчайшего пути A -> E: " << endl << endl;

    g.add_vertex("F");
    g.add_vertex("G");

    g.add_edge("F", "B", 14.0);
    g.add_edge("C", "D", 7.0);
    g.add_edge("D", "F", 15.0);
    g.add_edge("F", "G", 3.0);


    std::vector<typename Graph<std::string, double>::Edge> path = g.shortest_path("A", "G");


    cout << "Путь: "; 
    g.print_path(path);

    cout << endl << "Вес: " << g.get_path_weight(path);


    cout << endl << endl << endl << "Задача: " << endl << endl;

    Graph<std::string, double> city_graph;

    city_graph.add_vertex("Травмпункт 1");
    city_graph.add_vertex("Травмпункт 2");
    city_graph.add_vertex("Травмпункт 3");
    city_graph.add_vertex("Травмпункт 4");
    city_graph.add_vertex("Травмпункт 5");

    city_graph.add_edge("Травмпункт 1", "Травмпункт 2", 5.0);
    city_graph.add_edge("Травмпункт 1", "Травмпункт 3", 10.0);
    city_graph.add_edge("Травмпункт 2", "Травмпункт 4", 3.0);
    city_graph.add_edge("Травмпункт 3", "Травмпункт 4", 7.0);
    city_graph.add_edge("Травмпункт 4", "Травмпункт 5", 4.0);
    city_graph.add_edge("Травмпункт 1", "Травмпункт 5", 15.0);

    std::cout << "Граф травмпунктов: " << std::endl;
    city_graph.print();
    cout << endl;

    cout << "Травмпункт, который находится дальше всего от своих прямых соседей: " << g.most_isolated_clinic();


    cout << endl << endl;
}