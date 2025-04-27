#include <unordered_map>
#include <unordered_set>
#include <queue>


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

        return adjacency_list[vertex];

    }


    size_t order() const;

    size_t degree(const Vertex& v) const;
    
    bool is_connected() const;

    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const;

    std::vector<Vertex> walk(const Vertex& start_vertex) const {

        vector<Vertex> result;

        if (!has_vertex(start_vertex)) return result;

        queue<Vertex> q;
        unordered_set<Vertex> visited;

        q.push(start_vertex);
        visited.insert(start_vertex);

        while(!q.empty()) {

            Vertex current = q.front();

            auto& edges = adjacency_list[current];

            for (const auto& edge : edges) {

                Vertex& neighbor = edge->to;

                if (!visited.contains(neighbor)) {

                    q.push(neighbor);
                    visited.insert(neighbor);

                }

            }

        }

        return result;

    }
};