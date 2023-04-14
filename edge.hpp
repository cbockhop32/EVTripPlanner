#pragma once

// Edge class that connects Chargers to one another
class Edge {
    public:
        Edge(){};
        Edge(int destID, int dist) 
        {
            destChargerID = destID;
            distance = dist;
        }

        int getDistance()
        {
            return distance;
        }

        int getDestChargerID()
        {
            return destChargerID;
        }

    public:
        int destChargerID;
        int distance;
};