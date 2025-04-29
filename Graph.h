#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <limits>
#include <memory>


using namespace std;

template<typename Vertex, typename Distance = double>
class Graph {
    
public:

    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;

        Edge(const Vertex f, const Vertex t, const Distance d) : from(f), to(t), distance(d) {}
    };

private:

    unordered_map<Vertex, vector<shared_ptr<Edge>>> adjacency_list;

public:

    bool has_vertex(const Vertex& v) const {
        return adjacency_list.contains(v);
    }


    bool add_vertex(const Vertex& v) {
        if (has_vertex(v)) return false;

        adjacency_list[v] = {};
        return true;
    }


    bool remove_vertex(const Vertex& v) {
        if (!has_vertex(v)) return false;

        adjacency_list.erase(v);

        for (auto& vertex_edges : adjacency_list) {

            auto& edges_from_vertex = vertex_edges.second;

            vector<shared_ptr<Edge>> updated_edges;

            for (const auto& edge : edges_from_vertex) {

                if (edge->to != v) {

                    updated_edges.push_back(edge);

                }

            }

            edges_from_vertex = updated_edges;

        }

        return true;

    }


    std::vector<Vertex> vertices() const {

        vector<Vertex> vertices;

        for (const auto& pair : adjacency_list) {
            vertices.push_back(pair.first);
        }

        return vertices;

    }


    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {

        if (!has_vertex(from)) {
            add_vertex(from);
        }

        if (!has_vertex(to)) {
            add_vertex(to);
        }

        auto edge = make_shared<Edge>(from, to, d);

        adjacency_list[from].push_back(edge);

    }


    bool remove_edge(const Vertex& from, const Vertex& to) {

        if (!has_vertex(from)) return false;

        if (!has_vertex(to)) return false;

        auto& edges = adjacency_list[from];

        vector<shared_ptr<Edge>> updated_edges;

        for (const auto& edge : edges) {

            if (edge->to != to) updated_edges.push_back(edge);

        }

        if (edges.size() == updated_edges.size()) return false;

        edges = updated_edges;

        return true;
    }


    bool remove_edge(const Edge& e) {

        if (!has_vertex(e.from) || !has_vertex(e.to)) return false;

        auto& edges = adjacency_list[e.from];

        vector<shared_ptr<Edge>> updated_edges;

        for (const auto& edge : edges) {

            if (!(edge->to == e.to && edge->distance == e.distance)) {

                updated_edges.push_back(edge);

            }

        }

        if(edges.size() == updated_edges.size()) return false;

        edges = updated_edges;

        return true;

    }
    
    
    bool has_edge(const Vertex& from, const Vertex& to) const {

        if (!has_vertex(from)) return false;

        auto& edges = adjacency_list[from];

        for (const auto& edge : edges) {

            if (edge->to == to) return true;

        }

        return false;

    }


    bool has_edge (const Edge& e) const {

        if (!has_vertex(e.from)) return false;

        auto& edges = adjacency_list[e.from];

        for (const auto& edge : edges) {

            if (edge->to == e.to && edge->distance == e.distance) return true;

        }

        return false;


    }


    std::vector<Edge> edges(const Vertex& vertex) {

        if (!has_vertex(vertex)) return {};

        const auto& ptrs_edges = adjacency_list[vertex];

        vector<Edge> result;

        for (auto& edge_ptr : ptrs_edges) {

            result.push_back(*edge_ptr);

        }

        return result;
    }


    size_t order() const {
        return adjacency_list.size();
    }


    size_t degree(const Vertex& v) const {

        if (!has_vertex(v)) return 0;

        return adjacency_list[v].size();

    }
    
    bool is_connected() const {

        if(adjacency_list.empty()) return true;

        Vertex start = adjacency_list.begin()->first;

        vector<Vertex> reached_vertices = walk(start);

        if (reached_vertices.size() != adjacency_list.size()) return false;

        unordered_map<Vertex, vector<shared_ptr<Edge>>> r_adjacency_list;

        for (auto& vertices_edges : adjacency_list) {

            for (auto& edge : vertices_edges.second) {

                r_adjacency_list[edge->to].push_back(
                    make_shared<Edge>(edge->to, edge->from, edge->distance)
                );

            }

        }

        vector<Vertex> r_reached_vertices = reverse_walk(start, r_adjacency_list);

        if (r_reached_vertices.size() != adjacency_list.size()) return false;

        return true;

    }

    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {

        unordered_map<Vertex, int> distance;
        unordered_map<Vertex, Vertex> previous;
        unordered_set<Vertex> visited;

        for (auto& [v, _] : adjacency_list) {

            distance[v] = INT_MAX;
            
        }

        if (!has_vertex(from) || !has_vertex(to)) return {};
        
        distance[from] = 0;

        vector<Vertex> to_process = { from };

        while (!to_process.empty()) {

            auto min_it = min_element(to_process.begin(), to_process.end(),
                [&distance](const Vertex& a, const Vertex& b) {

                    return distance[a] < distance[b];

                });

            Vertex current = *min_it;

            to_process.erase(min_it);

            if (visited.contains(current)) continue;
            visited.insert(current);

            if (current ==  to) break;

            for (auto& edge : adjacency_list[current]) {

                Vertex neighbor = edge->to;

                int w = edge->distance;

                int new_dist = distance[current] + w;

                if (new_dist < distance[neighbor]) {

                    distance[neighbor] = new_dist;
                    previous[neighbor] = current;

                    to_process.push_back(neighbor);                    

                }

            }

        }

        vector<Vertex> path;

        if (distance[to] == INT_MAX) return path;

        for (Vertex v = to; v != from; v = previous[v]) {

            path.push_back(v);

        }

        path.push_back(from);

        reverse(path.begin(), path.end());

        Vector<Edge> path_edges;

        for (size_t i = 0; i + 1 < path.size(); ++i) {

            Vertex u = path[i];
            Vertex v = path[i + 1];

            for (auto& edge : adjacency_list[u]) {

                if (edge->to == v) {

                    path_edges.push_back(*edge);
                    break;

                }

            }

        }

        return path_edges;

    }


    std::vector<Vertex> walk(const Vertex& start_vertex) const {

        vector<Vertex> result;

        if (!has_vertex(start_vertex)) return result;

        queue<Vertex> q;
        unordered_set<Vertex> visited;

        q.push(start_vertex);
        visited.insert(start_vertex);

        while(!q.empty()) {

            Vertex current = q.front();

            q.pop();

            result.push_back(current);

            auto& edges = adjacency_list[current];

            for (const auto& edge : edges) {

                Vertex neighbor = edge->to;

                if (!visited.contains(neighbor)) {

                    q.push(neighbor);
                    visited.insert(neighbor);

                }

            }

        }

        return result;

    }

    
    std::vector<Vertex> reverse_walk(
        const Vertex& start_vertex,
        const unordered_map<Vertex, vector<shared_ptr<Edge>>>& r_adjacency_list
    ) const {

        vector<Vertex> result;

        if (!r_adjacency_list.contains(start_vertex)) return result;

        queue<Vertex> q;
        unordered_set<Vertex> visited;

        q.push(start_vertex);
        visited.insert(start_vertex);

        while(!q.empty()) {

            Vertex current = q.front();

            q.pop();
            
            result.push_back(current);

            auto& edges = r_adjacency_list[current];

            for (const auto& edge : edges) {

                Vertex neighbor = edge->to;

                if (!visited.contains(neighbor)) {

                    q.push(neighbor);
                    visited.insert(neighbor);

                }

            }

        }

        return result;

    }
};