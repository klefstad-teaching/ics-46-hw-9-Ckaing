#include "../src/dijkstras.h"




vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    if (G.empty() || source < 0 || source >= static_cast<int>(G.size())) {
        return vector<int>();  
    }
    
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous.assign(numVertices, -1);
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;
    minHeap.push({0, source});
    
    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        int dist_u = minHeap.top().first;
        minHeap.pop();
        
        if (visited[u]) continue;
        visited[u] = true;
        
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            
            if (!visited[v] && distances[u] != INF && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> path;
    if (distances.empty() || destination < 0 || destination >= static_cast<int>(distances.size())) {
            return path;
        }

    int current = destination;
    while (current != -1){
        path.push_back(current);
        current = previous[current];
    }
    reverse(path.begin(), path.end());
    return path;
}
void print_path(const vector<int>& v, int total){
    if (v.empty()) {
        cout << "\nTotal cost is " << total << "\n";
        return;
    }
    for(size_t i = 0; i < v.size() ; i++){
        cout << v[i];

        cout << " ";
    }
    cout << "\nTotal cost is " << total << "\n";
}