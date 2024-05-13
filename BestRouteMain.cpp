#include <bits/stdc++.h>
using namespace std;

class Delivery 
{
private:
    vector<vector<int>> graph;
    unordered_set<int> locations{AMANS_LOCATION, RESTAURANT_1, RESTAURANT_2, CUSTOMER_1, CUSTOMER_2};
    vector<int> prepTimes{0, 10, 15, 0, 0}; // prep times for each location
    
public:
    enum Location { AMANS_LOCATION, RESTAURANT_1, RESTAURANT_2, CUSTOMER_1, CUSTOMER_2 };
    static const int NUM_LOCATIONS = 5;

    Delivery() = default;

    void createGraph(const vector<vector<int>>& graph) {
        this->graph = graph;
    }

    int shortestTime() {
        vector<int> dist(NUM_LOCATIONS, numeric_limits<int>::max());
        vector<int> path(NUM_LOCATIONS, -1);
        vector<bool> visited(NUM_LOCATIONS, false);

        dist[AMANS_LOCATION] = 0;
        int current = AMANS_LOCATION;

        unordered_set<int> unvisited;

        while (true) {
            visited[current] = true;
            for (int i = 0; i < NUM_LOCATIONS; ++i) {
                if (graph[current][i] == -1 || visited[i])
                    continue;

                if ((i == CUSTOMER_1 && !visited[RESTAURANT_1]) || (i == CUSTOMER_2 && !visited[RESTAURANT_2]))
                    continue;

                unvisited.insert(i);

                int total = dist[current] + graph[current][i];
                if (i == RESTAURANT_1)
                    total = max(total, prepTimes[RESTAURANT_1]);
                else if (i == RESTAURANT_2)
                    total = max(total, prepTimes[RESTAURANT_2]);

                if (total < dist[i]) {
                    dist[i] = total;
                    path[i] = current;
                }
            }
            unvisited.erase(current);
            if (unvisited.empty())
                break;

            current = *min_element(unvisited.begin(), unvisited.end(),
                                         [&](int a, int b) { return dist[a] < dist[b]; });
        }
        
        cout<<"Time taken to deliver Customer 1: "<<dist[CUSTOMER_1]<<" mins"<<endl;
        cout<<"Time taken to deliver Customer 2: "<<dist[CUSTOMER_2]<<" mins"<<endl;
        return dist[CUSTOMER_1] + dist[CUSTOMER_2];
    }
};

int main() {
    vector<vector<int>> graph = {
        {-1, 5, 10, -1, -1},
        {5, -1, 5, 5, 10},
        {10, 5, -1, 10, 10},
        {-1, 5, 10, -1, 5},
        {-1, 10, 10, 5, -1}
    };

    Delivery delivery;
    delivery.createGraph(graph);

    int totalTime = delivery.shortestTime();
    cout << "Total time taken to deliver both the customers: " << totalTime << " mins\n";

    return 0;
}
