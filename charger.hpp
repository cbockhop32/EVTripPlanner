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
        Charger(int chargID,double chargLat, double chargLon, string chargName)
        {
            id = chargID;
            name = chargName;
            lat = chargLat;
            lon = chargLon;
        };

        void setChargerID(int chargID)
        {
            id = chargID;
        }

        int getChargerID()
        {
            return id;
        }

        void setChargerName(string chargName)
        {
            name = chargName;
        }

        string getChargerName()
        {
            return name;
        }

        double getChargerLatitude()
        {
            return lat;
        }

        double getChargerLongitude()
        {
            return lon;
        }

        list<Edge> getEdgeList()
        {
            return edges;
        }
        // Helper function that was used during testing
        void printEdges(){
            for(auto it = edges.begin(); it != edges.end(); it++)
            {   
                cout << "[" << it->getDestChargerID() << "," << it->getDistance() << "] ";
            }
            cout << '\n';

        }

    public:
        int id;
        string name;
        double lat;
        double lon;
        list<Edge> edges; // list of edges, each Edge contains the destination Charger ID and the distance (weight)

};