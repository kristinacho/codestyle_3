#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

/**
 * @brief Класс для работы с ориентированными графами
 */
class Graph {
public:
    /**
     * @brief Загружает граф из файла
     * @param filename Имя файла с матрицей смежности
     * @param error [out] Сообщение об ошибке
     * @return true если загрузка успешна, false иначе
     */
    bool loadFromFile(const std::string& filename, std::string& error);

    /**
     * @brief Выполняет топологическую сортировку
     * @param result [out] Вектор с отсортированными вершинами
     * @param error [out] Сообщение об ошибке
     * @return true если сортировка выполнена, false если граф содержит циклы
     */
    bool topologicalSort(std::vector<int>& result, std::string& error) const;

private:
    std::vector<std::vector<int>> adjacencyMatrix; ///< Матрица смежности
    int vertexCount = 0;                           ///< Количество вершин

    /**
     * @brief Рекурсивная функция для DFS
     * @param vertex Текущая вершина
     * @param visited Вектор посещенных вершин
     * @param stack Стек для сохранения порядка
     * @param recursionStack Стек для обнаружения циклов
     * @param error [out] Сообщение об ошибке
     * @return true если циклов не обнаружено, false иначе
     */
    bool dfsTopologicalSort(int vertex, std::vector<bool>& visited,
        std::stack<int>& stack, std::vector<bool>& recursionStack,
        std::string& error) const;
};

#endif // GRAPH_H
