
using namespace std;

template<typename Vertex, typename Distance = double>
class Graph {

    unordered_map<Vertex, vector<shared_ptr<Edge>>> adjacency_list;
    
public:

    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;

        Edge(const Vertex f, const Vertex t, const Distance d) : from(f), to(t), distance(d) {}
    };


    bool has_vertex(const Vertex& v) const {
        return adjacency_list.contains();
    }

    bool add_vertex(const Vertex& v) {
        if (has_vertex(v)) return false;

        adjacency_list[v] = {};
        return true;
    }

    bool remove_vertex(const Vertex& v) {
        if(!has_vertex(v)) return false;
        
    }
    std::vector<Vertex> vertices() const;

    void add_edge(const Vertex& from, const Vertex& to, const Distacnce& d);
    bool remove_edge(const Vertex& from, const Vertex& to);
    bool remove_edge(const Edge& e); 
    bool has_edge(const Vertex& from, const Vertex& to) const;
    bool has_edge (const Edge& e) const;
    std::vector<Edge> edges(const Vertex& vertex);

    size_t order() const;

    size_t degree(const Vertex& v) const;
    
    bool is_connected() const;

    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const;

    std::vector<Vertex> walk(const Vertex& start_vertex) const;
};