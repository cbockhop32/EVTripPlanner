#pragma once

#include <iostream>
#include <list>

#include "edge.hpp"

using namespace std;

//Charger class represents the vertices in the graph
class Charger {
    public:
        // Constructor w/o paramters
        Charger(){
            id = 0;
            name = "";
        };

        // Constructor w/ parameters
        Charger(int chargID,double chargLat, double chargLon, string chargName);
        void setChargerID(int chargID);
        int getChargerID();
        void setChargerName(string chargName);
        string getChargerName();
        double getChargerLatitude();
        double getChargerLongitude();
        list<Edge> getEdgeList();
        void printEdges();
       
    public:
        int id;
        string name;
        double lat;
        double lon;
        list<Edge> edges; // list of edges, each Edge contains the destination Charger ID and the distance (weight)

};