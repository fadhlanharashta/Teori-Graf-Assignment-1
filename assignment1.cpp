#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits>
#include <algorithm> // Include this header for the reverse function

using namespace std;

// Define a structure to represent edges in the graph
struct Edge {
    char destination;
    int weight;
};

// Define a structure to represent a vertex and its distance from the source
struct Vertex {
    char name;
    int distance;
    
    bool operator>(const Vertex& other) const {
        return distance > other.distance;
    }
};

// Function to find the shortest path from 'start' to 'end' in the graph
vector<char> dijkstra(map<char, vector<Edge>>& graph, char start, char end) {
    // Create a priority queue to store vertices based on their distance
    priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

    // Create a map to store the distance of each vertex from the start vertex
    map<char, int> distance;
    
    // Create a map to store the previous vertex on the shortest path
    map<char, char> previous;

    // Initialize distances and add the start vertex to the priority queue
    for (const auto& pair : graph) {
        char vertex = pair.first;
        distance[vertex] = (vertex == start) ? 0 : numeric_limits<int>::max();
        pq.push({vertex, distance[vertex]});
    }

    // Dijkstra's algorithm
    while (!pq.empty()) {
        Vertex current = pq.top();
        pq.pop();

        if (current.name == end) {
            // We have found the shortest path to 'end', so we can stop here
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

    // Reconstruct the shortest path from 'start' to 'end'
    vector<char> shortestPath;
    char current = end;
    while (current != start) {
        shortestPath.push_back(current);
        current = previous[current];
    }
    shortestPath.push_back(start);

    // Reverse the path to get it in the correct order
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
    // Create the graph as an adjacency list
    map<char, vector<Edge>> graph;
    
    // Add edges and their weights to the graph
    graph['a'] = {{'b', 1}, {'c', 3},{'d',5}};
    graph['b'] = {{'a', 1}, {'f', 4},{'e',7}};
    graph['c'] = {{'a', 3},{'f',1}};
    graph['d'] = {{'a', 5},{'g',2}};
    graph['e'] = {{'b', 7},{'g',1},{'i',6}};
    graph['f'] = {{'b', 4},{'c',1},{'g',2},{'h',6}};
    graph['g'] = {{'d', 2},{'f',2},{'h',4},{'c',1},{'e',1}};
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
