#include "charger.hpp"

 // Constructor w/ parameters
Charger::Charger(int chargID,double chargLat, double chargLon, string chargName) : id(chargID), name(chargName), lat(chargLat), lon(chargLon){};

void Charger::setChargerID(int chargID)
{
    id = chargID;
}

int Charger::getChargerID()
{
    return id;
}

void Charger::setChargerName(string chargName)
{
    name = chargName;
}

string Charger::getChargerName()
{
    return name;
}

double Charger::getChargerLatitude()
{
    return lat;
}

 double Charger::getChargerLongitude()
{
    return lon;
}


list<Edge> Charger::getEdgeList()
{
    return edges;
}

// Helper function that was used during testing
void Charger::printEdges()
{
    for(auto it = edges.begin(); it != edges.end(); it++)
    {   
        cout << "[" << it->getDestChargerID() << "," << it->getDistance() << "] ";
    }
    cout << '\n';
}