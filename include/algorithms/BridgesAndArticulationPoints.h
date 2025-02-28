#ifndef BRIDGES_AND_ARTICULATION_POINTS_H
#define BRIDGES_AND_ARTICULATION_POINTS_H

#include "Graph.h"
#include <vector>
#include <unordered_map>

namespace graph {

template <typename VertexType, typename EdgeType>
class BridgesAndArticulationPoints {
public:
    BridgesAndArticulationPoints(const Graph<VertexType, EdgeType>& graph)
        : graph(graph), time(0) {}

    // Поиск мостов
    std::vector<EdgeType> findBridges() {
        std::vector<EdgeType> bridges;
        std::unordered_map<int, int> discoveryTime;
        std::unordered_map<int, int> low;
        std::unordered_map<int, int> parent;

        for (const auto& vertex : graph.getVertices()) {
            if (discoveryTime.find(vertex.id) == discoveryTime.end()) {
                dfsBridges(vertex.id, discoveryTime, low, parent, bridges);
            }
        }

        return bridges;
    }

    // Поиск точек сочленения
    std::vector<int> findArticulationPoints() {
        std::vector<int> articulationPoints;
        std::unordered_map<int, int> discoveryTime;
        std::unordered_map<int, int> low;
        std::unordered_map<int, int> parent;

        for (const auto& vertex : graph.getVertices()) {
            if (discoveryTime.find(vertex.id) == discoveryTime.end()) {
                dfsArticulationPoints(vertex.id, discoveryTime, low, parent, articulationPoints);
            }
        }

        return articulationPoints;
    }

private:
    const Graph<VertexType, EdgeType>& graph;
    int time;

    void dfsBridges(int u, std::unordered_map<int, int>& discoveryTime, std::unordered_map<int, int>& low,
                    std::unordered_map<int, int>& parent, std::vector<EdgeType>& bridges) {
        discoveryTime[u] = low[u] = ++time;

        for (int v : graph.getNeighbors(u)) {
            if (discoveryTime.find(v) == discoveryTime.end()) {
                parent[v] = u;
                dfsBridges(v, discoveryTime, low, parent, bridges);

                low[u] = std::min(low[u], low[v]);

                if (low[v] > discoveryTime[u]) {
                    bridges.push_back(EdgeType(u, v));нет
                }
            } else if (v != parent[u]) {
                low[u] = std::min(low[u], discoveryTime[v]);
            }
        }
    }

    void dfsArticulationPoints(int u, std::unordered_map<int, int>& discoveryTime, std::unordered_map<int, int>& low,
                               std::unordered_map<int, int>& parent, std::vector<int>& articulationPoints) {
        discoveryTime[u] = low[u] = ++time;
        int children = 0;

        for (int v : graph.getNeighbors(u)) {
            if (discoveryTime.find(v) == discoveryTime.end()) {
                children++;
                parent[v] = u;
                dfsArticulationPoints(v, discoveryTime, low, parent, articulationPoints);

                low[u] = std::min(low[u], low[v]);

                if (parent.find(u) == parent.end() && children > 1) {
                    articulationPoints.push_back(u);
                }

                if (parent.find(u) != parent.end() && low[v] >= discoveryTime[u]) {
                    articulationPoints.push_back(u);
                }
            } else if (v != parent[u]) {
                low[u] = std::min(low[u], discoveryTime[v]);
            }
        }
    }
};

}  // namespace graph

#endif  // BRIDGES_AND_ARTICULATION_POINTS_H