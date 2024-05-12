#include <bits/stdc++.h>
using namespace std;

// Assumptions:
// Please refer readme file

//Sample Cases
// Location R1 = {"R1", 12.9352, 77.6245}; // Restaurant for C1
// Location R2 = {"R2", 12.9226, 77.6559}; // Restaurant for C2
// vector<Order> orders = {
//     {"C1", R1, 15}, // Order from C1 at R1 with prep time 15 mins
//     {"C2", R2, 20}  // Order from C2 at R2 with prep time 20 mins
// };


struct Location {
    string name;
    double lat;
    double lon;
};

struct Order {
    string consumer;
    Location restaurant;
    int prep_time;
};

struct DeliveryExecutive {
    Location location;
};

double haversine_distance(Location loc1, Location loc2) {
    double R = 6371; // Radius of the Earth in km
    double lat1 = loc1.lat;
    double lon1 = loc1.lon;
    double lat2 = loc2.lat;
    double lon2 = loc2.lon;
    double dlat = (lat2 - lat1) * M_PI / 180.0;
    double dlon = (lon2 - lon1) * M_PI / 180.0;
    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R * c;
    return distance;
}

double calculate_time(double distance, double speed) {
    double time = distance / speed;
    return time;
}

pair<vector<Order>, double> find_shortest_path(DeliveryExecutive de, vector<Order>& orders) {
    Location current_location = de.location;
    double total_time = 0;
    vector<Order> path;

    while (!orders.empty()) {
        double min_time = DBL_MAX;
        Order next_order;

        for (Order& order : orders) {
            Location restaurant = order.restaurant;
            int prep_time = order.prep_time;
            double distance_to_restaurant = haversine_distance(current_location, restaurant);
            double travel_time_to_restaurant = calculate_time(distance_to_restaurant, 20);
            double total_order_time = prep_time + travel_time_to_restaurant;

            if (total_order_time < min_time) {
                min_time = total_order_time;
                next_order = order;
            }
        }

        // Update current location and time
        total_time += min_time;
        current_location = next_order.restaurant;
        path.push_back(next_order);

        // Remove processed order
        orders.erase(std::remove_if(orders.begin(), orders.end(), [&](const Order& o) {
        return o.consumer == next_order.consumer && o.restaurant.name == next_order.restaurant.name;
    }), orders.end());

    }

    return make_pair(path, total_time);
}

int main() {
    
    int n;
    cout<<"Input the number of restaurants: ";
    cin>>n;
    
    vector<Location> resto;
    vector<Order> orders;
    
    cout<<"Enter restaurants details: ";
    string name;
    double lat, lan;
    for(int i=0;i<n;i++)
    {
        cin>>name;
        cin>>lat;
        cin>>lan;
        Location restaurant = {name, lat, lan}; // Restaurant distance
        resto.push_back(restaurant);
    }
    
    int prep_time;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter preparation time for restaurant: ";
        cin>>prep_time;
        orders.push_back({"C" + to_string(i+1), resto[i], prep_time});
    }
    
    cout<<endl;
    DeliveryExecutive aman = {"Aman", 12.9242, 77.6227}; // Aman's initial location

    // Find shortest path for Aman to deliver orders
    auto result = find_shortest_path(aman, orders);
    vector<Order> path = result.first;
    double total_time = result.second;

    // Output
    cout << "Shortest Path for Aman:" << endl;
    for (const Order& order : path) {
        cout << "Deliver to " << order.consumer << " from " << order.restaurant.name << " (Prep time: " << order.prep_time << " mins)" << endl;
    }
    cout << "Total time taken: " << total_time << " minutes" << endl;

    return 0;
}
