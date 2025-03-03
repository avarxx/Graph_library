#ifndef FLOW_NETWORK_H
#define FLOW_NETWORK_H

#include "Graph.h"
#include <unordered_map>
#include <memory>

namespace graph {

/**
 * @class FlowNetwork
 * @brief Шаблонный класс для представления сети потоков с остаточными ребрами
 * @tparam GraphType Тип базового графа для построения сети потоков
 * 
 * @details Реализует представление графа с помощью списков смежности,
 *          автоматически создавая обратные ребра для работы алгоритмов поиска потока
 */
template <typename GraphType>
class FlowNetwork {
public:
    /**
     * @struct FlowEdge
     * @brief Ребро потока с метаданными для алгоритмов поиска максимального потока
     */
    struct FlowEdge {
        Vertex target;       ///< Целевая вершина ребра
        int capacity;        ///< Пропускная способность ребра
        int flow;            ///< Текущий поток через ребро (0 <= flow <= capacity)
        FlowEdge* reverse;   ///< Указатель на обратное ребро в остаточной сети

        /**
         * @brief Конструктор ребра потока
         * @param t Конечная вершина ребра
         * @param cap Пропускная способность ребра
         * @param rev Указатель на обратное ребро (по умолчанию nullptr)
         */
        FlowEdge(Vertex t, int cap, FlowEdge* rev = nullptr)
            : target(t), capacity(cap), flow(0), reverse(rev) {}
    };

    /**
     * @brief Конструктор сети потоков на основе существующего графа
     * @param baseGraph Исходный граф для преобразования в сеть потоков
     * 
     * @note Автоматически добавляет все вершины и ребра из базового графа,
     *       инициализируя поле capacity значением из исходного ребра
     */
    explicit FlowNetwork(const GraphType& baseGraph) {
        for (const auto& v : baseGraph.getVertices()) {
            addVertex(v);
        }
        for (const auto& e : baseGraph.getEdges()) {
            addEdge(e.source, e.target, e.capacity);
        }
    }

    /**
     * @brief Добавляет ориентированное ребро в сеть потоков
     * @param from Исходная вершина ребра
     * @param to Конечная вершина ребра
     * @param capacity Пропускная способность ребра
     * 
     * @note Автоматически создает обратное ребро с нулевой пропускной способностью.
     *       Для неориентированных графов используйте addEdge в обоих направлениях
     */
    void addEdge(const Vertex& from, const Vertex& to, int capacity) {
        auto& adjFrom = adjacency[from];
        auto& adjTo = adjacency[to];
        
        adjFrom.emplace_back(to, capacity);
        adjTo.emplace_back(from, 0);
        
        adjFrom.back().reverse = &adjTo.back();
        adjTo.back().reverse = &adjFrom.back();
    }

    /**
     * @brief Возвращает список смежных ребер для вершины (только для чтения)
     * @param v Вершина для получения смежных ребер
     * @return Константная ссылка на вектор ребер или пустой вектор, если вершина не найдена
     */
    const std::vector<FlowEdge>& getAdjacent(const Vertex& v) const {
        static const std::vector<FlowEdge> empty;
        auto it = adjacency.find(v);
        return it != adjacency.end() ? it->second : empty;
    }

    /**
     * @brief Возвращает список смежных ребер для вершины (для модификации)
     * @param v Вершина для получения смежных ребер
     * @return Ссылка на вектор ребер (создает пустой вектор, если вершины не существует)
     */
    std::vector<FlowEdge>& getAdjacentMut(const Vertex& v) {
        return adjacency[v];
    }

private:
    std::unordered_map<Vertex, std::vector<FlowEdge>> adjacency; ///< Хэш-таблица списков смежности
    
    /**
     * @brief Внутренний метод для добавления вершины в сеть
     * @param v Вершина для добавления
     */
    void addVertex(const Vertex& v) {
        adjacency.emplace(v, std::vector<FlowEdge>{});
    }
};

} // namespace graph

#endif // FLOW_NETWORK_H