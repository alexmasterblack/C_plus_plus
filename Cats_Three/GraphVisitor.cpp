#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <exception>

template <class Graph, class Vertex, class Visitor>
void BreadthFirstSearch(const Graph& graph, const Vertex& origin_vertex, Visitor visitor) {
    std::queue<Vertex> vertices_to_visit;
    std::unordered_set<Vertex> visited_vertices;
    vertices_to_visit.push(origin_vertex);
    visitor.DiscoverVertex(origin_vertex);
    visited_vertices.insert(origin_vertex);
    while (vertices_to_visit.size() > 0) {
        auto from = vertices_to_visit.front();
        vertices_to_visit.pop();
        visitor.ExamineVertex(from);
        for (const auto& target : graph.OutgoingEdges(from)) {
            if (visited_vertices.count(target) == 0) {
                visited_vertices.insert(target);
                vertices_to_visit.push(target);
                visitor.DiscoverVertex(target);
            }
        }
    }
}

template<class Vertex>
class UndirectedGraph {
public:
    std::vector<Vertex> OutgoingEdges(const Vertex& from) const {
        auto it = outgoing_edges_.find(from);
        if (it == outgoing_edges_.end()) {
            return std::vector<Vertex>();
        }
        return it->second;
    }

    void Add(const std::vector<std::pair<Vertex, Vertex>>& edges) {
        for (auto fromto : edges) {
            outgoing_edges_[fromto.first].push_back(fromto.second);
            outgoing_edges_[fromto.second].push_back(fromto.first);
        }
    }
private:
    std::unordered_map<Vertex, std::vector<Vertex>> outgoing_edges_;
};

void fail() {
    std::cout << 0 << std::endl;
    exit(0);
}

template<typename Vertex>
class BfsVisitor {
public:
    BfsVisitor() : info(new Place<Vertex>()) {}
    void ExamineVertex(const Vertex& vertex) {
        info->our_vertex = vertex;
    }
    void DiscoverVertex(const Vertex& vertex) {
        if (info->flag) {
            info->flag = false;
            info->parent[vertex] = vertex;
            info->distance[vertex] = 0;
        }
        else {
            info->parent[vertex] = info->our_vertex;
            info->distance[vertex] = info->distance[info->our_vertex] + 1;
        }
    }

    size_t DistanceTo(const Vertex& target) const {
        return info->distance[target];
    }
    Vertex Parent(const Vertex& vertex) const {
        return info->parent[vertex];
    }

private:
    template<typename T>
    struct Place {
        std::unordered_map<T, size_t> distance;
        std::unordered_map<T, T> parent;
        Vertex our_vertex;
        bool flag = true;
    };
    std::shared_ptr<Place<Vertex>> info;
};

int main() {
    //static_assert(sizeof(BfsVisitor<char>) <= 2 * sizeof(char*));

    {
        UndirectedGraph<int> graph;
        graph.Add({ {0, 1}, {1, 2}, {2, 3} });
        BfsVisitor<int> visitor;
        BreadthFirstSearch(graph, 0, visitor);
        if (visitor.DistanceTo(1) != 1 ||
            visitor.DistanceTo(2) != 2 ||
            visitor.DistanceTo(3) != 3 ||
            visitor.Parent(0) != 0 ||
            visitor.Parent(1) != 0 ||
            visitor.Parent(2) != 1 ||
            visitor.Parent(3) != 2 ||
            false
            ) {
            fail();
        }
    }

    {
        UndirectedGraph<int> graph;
        graph.Add({ {0, 1}, {0, 2}, {1, 2} });
        BfsVisitor<int> visitor;
        BreadthFirstSearch(graph, 0, visitor);
        if (visitor.DistanceTo(1) != 1 ||
            visitor.DistanceTo(2) != 1 ||
            visitor.Parent(1) != 0 ||
            visitor.Parent(2) != 0 ||
            false
            ) {
            fail();
        }
    }

    {
        UndirectedGraph<int> graph;
        graph.Add({ {0, 1},
                   {0, 2},
                   {0, 3},
                   {0, 7},
                   {1, 2},
                   {3, 4},
                   {3, 5},
                   {4, 5},
                   {4, 6},
                   {5, 6},
                   {6, 11},
                   {6, 12},
                   {6, 13},
                   {6, 14},
                   {7, 8},
                   {8, 9},
                   {9, 10}
            });

        BfsVisitor<int> visitor;
        BreadthFirstSearch(graph, 0, visitor);
        if (visitor.DistanceTo(1) != 1 ||
            visitor.DistanceTo(2) != 1 ||
            visitor.DistanceTo(3) != 1 ||
            visitor.DistanceTo(4) != 2 ||
            visitor.DistanceTo(5) != 2 ||
            visitor.DistanceTo(6) != 3 ||
            visitor.DistanceTo(7) != 1 ||
            visitor.DistanceTo(8) != 2 ||
            visitor.DistanceTo(9) != 3 ||
            visitor.DistanceTo(10) != 4 ||
            visitor.DistanceTo(11) != 4 ||
            visitor.DistanceTo(12) != 4 ||
            visitor.DistanceTo(13) != 4 ||
            visitor.DistanceTo(14) != 4 ||
            visitor.Parent(1) != 0 ||
            visitor.Parent(2) != 0 ||
            visitor.Parent(3) != 0 ||
            visitor.Parent(7) != 0 ||
            visitor.Parent(4) != 3 ||
            visitor.Parent(5) != 3 ||
            visitor.Parent(11) != 6 ||
            visitor.Parent(8) != 7 ||
            visitor.Parent(9) != 8 ||
            visitor.Parent(10) != 9 ||
            false
            ) {
            fail();
        }
    }

    std::cout << 1 << std::endl;
}
