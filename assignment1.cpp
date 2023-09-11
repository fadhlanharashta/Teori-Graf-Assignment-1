#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits>
#include <algorithm> 

using namespace std;

struct Edge {
    char destination;
    int weight;
};

struct Vertex {
    char name;
    int distance;
    
    bool operator>(const Vertex& other) const {
        return distance > other.distance;
    }
};

vector<char> dijkstra(map<char, vector<Edge>>& graph, char start, char end) {
    priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

    map<char, int> distance;
    
    map<char, char> previous;

    for (const auto& pair : graph) {
        char vertex = pair.first;
        distance[vertex] = (vertex == start) ? 0 : numeric_limits<int>::max();
        pq.push({vertex, distance[vertex]});
    }

    while (!pq.empty()) {
        Vertex current = pq.top();
        pq.pop();

        if (current.name == end) {
            break;
        }

        for (const Edge& edge : graph[current.name]) {
            int alt = distance[current.name] + edge.weight;
            if (alt < distance[edge.destination]) {
                distance[edge.destination] = alt;
                previous[edge.destination] = current.name;
                pq.push({edge.destination, alt});
            }
        }
    }

    vector<char> shortestPath;
    char current = end;
    while (current != start) {
        shortestPath.push_back(current);
        current = previous[current];
    }
    shortestPath.push_back(start);

    reverse(shortestPath.begin(), shortestPath.end());

    return shortestPath;
}

int getTotalWeight(const vector<char>& path, const map<char, vector<Edge>>& graph) {
    int totalWeight = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        char current = path[i];
        char next = path[i + 1];
        for (const Edge& edge : graph.at(current)) {
            if (edge.destination == next) {
                totalWeight += edge.weight;
                break;
            }
        }
    }
    return totalWeight;
}


int main() {
    map<char, vector<Edge>> graph;
    
    graph['a'] = {{'b', 1}, {'c', 3},{'d',5}};
    graph['b'] = {{'a', 1}, {'f', 4},{'e',7}};
    graph['c'] = {{'a', 3},{'f',1}};
    graph['d'] = {{'a', 5},{'g',2}};
    graph['e'] = {{'b', 7},{'g',1},{'i',6}};
    graph['f'] = {{'b', 4},{'c',1},{'g',2},{'h',6}};
    graph['g'] = {{'d', 2},{'f',2},{'h',4},{'c',1},{'e',1},{'l',1}};
    graph['h'] = {{'f', 6},{'j',1},{'g',4}};
    graph['i'] = {{'e', 6},{'j',2},{'m',4}};
    graph['j'] = {{'h', 1},{'i',2},{'m',7},{'k',1}};
    graph['k'] = {{'j', 1},{'l',4}};
    graph['l'] = {{'g', 1},{'k',4},{'m',3}};
    graph['m'] = {{'i', 4},{'j',7},{'l',3}};
    
    char start = 'a';
    char end = 'm';
    
    vector<char> shortestPath = dijkstra(graph, start, end);
    
    cout << "Shortest path from Vs to Vm: ";
    for (size_t i = 0; i < shortestPath.size(); ++i) {
        cout << shortestPath[i];
        if (i < shortestPath.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
    int totalWeight = getTotalWeight(shortestPath, graph);
    cout << "Total weight of the path: " << totalWeight << endl;


    return 0;
}
