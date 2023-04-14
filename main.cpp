#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

#include "network.hpp"
#include "helper_functions.hpp"

// The cars total range with a full charger
// Will be used to determine if chargers will have an edge between another charger when building out the
#define VEHICLE_RANGE 198

using namespace std;


int main(int argc, char** argv)
{
    if (argc != 4)
    {
        cout << "Error: requires csv path, initial supercharger names, and final supercharger names" << endl;        
        return -1;
    }

    stack<int> shortestPath;
    
    string charger_csv_path = argv[1];
    string initial_charger_name = argv[2];
    string goal_charger_name = argv[3];


    vector<tuple<string,double,double >> listOfChargers = getChargersFromFile(charger_csv_path, initial_charger_name, goal_charger_name);

    // Creates new network of Chargers and then uses the buildChargerNetwork to add all the Charger instances and then uses addEdgesToChargerNetwork
    // to connect all the necessary Chargers within one another using the Edge class
    Network newNetwork;
    newNetwork.buildChargerNetwork(listOfChargers);
    newNetwork.addEdgesToChargerNetwork(VEHICLE_RANGE);
    // newNetwork.printNetwork();
    
    shortestPath = newNetwork.calculateShortestDistance(initial_charger_name, goal_charger_name);
    printShortestPath(shortestPath, newNetwork, initial_charger_name, goal_charger_name);

    return 0;
}