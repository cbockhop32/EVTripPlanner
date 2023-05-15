#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <functional>
#include <cmath>
#include "charger.hpp"

#define PI 3.14159265358979323846
#define EARTH_RADIUS 3959.87433 //  6356.752 in km, 3959.87433 in miles
#define DEGREES_RADIANS PI / 180

using namespace std;

// Network class that represents a graph that contains Chargers (vertices) and connections each of them using the Edge class
class Network {
    public:
        Network(){};
        void addCharger(Charger charger);
        bool checkIfChargerExists(int id);
        bool checkIfEdgeExists(int id1, int id2);
        Charger getChargerByID(int chargerID);
        Charger getChargerByName(string chargerName);
        void addEdge(int startID, int destinationID, int weight);
        void buildChargerNetwork(vector<tuple<string,double,double>> chargersFromCSV);
        void addEdgesToChargerNetwork(int maxCarRange);
        float calculateChargingTime(Charger startLocation, Charger endLocation, float distanceDriven);
        vector<int> calculateShortestDistance(string startName, string endName);
        double CalcGPSDistance(double latitud1, double longitud1, double latitud2, double longitud2);
        void printNetwork();

    public: 
        vector<Charger> chargers;
};