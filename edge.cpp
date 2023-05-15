#include "edge.hpp"

Edge::Edge(int destID, int dist) : destChargerID(destID), distance(dist){};

int Edge::getDistance()
{
    return distance;
}

int Edge::getDestChargerID()
{
    return destChargerID;
}