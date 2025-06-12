#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

/**
 * @brief ����� ��� ������ � ���������������� �������
 */
class Graph {
public:
    /**
     * @brief ��������� ���� �� �����
     * @param filename ��� ����� � �������� ���������
     * @param error [out] ��������� �� ������
     * @return true ���� �������� �������, false �����
     */
    bool loadFromFile(const std::string& filename, std::string& error);

    /**
     * @brief ��������� �������������� ����������
     * @param result [out] ������ � ���������������� ���������
     * @param error [out] ��������� �� ������
     * @return true ���� ���������� ���������, false ���� ���� �������� �����
     */
    bool topologicalSort(std::vector<int>& result, std::string& error) const;

private:
    std::vector<std::vector<int>> adjacencyMatrix; ///< ������� ���������
    int vertexCount = 0;                           ///< ���������� ������

    /**
     * @brief ����������� ������� ��� DFS
     * @param vertex ������� �������
     * @param visited ������ ���������� ������
     * @param stack ���� ��� ���������� �������
     * @param recursionStack ���� ��� ����������� ������
     * @param error [out] ��������� �� ������
     * @return true ���� ������ �� ����������, false �����
     */
    bool dfsTopologicalSort(int vertex, std::vector<bool>& visited,
        std::stack<int>& stack, std::vector<bool>& recursionStack,
        std::string& error) const;
};

#endif // GRAPH_H
