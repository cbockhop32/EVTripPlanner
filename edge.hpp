#pragma once

// Edge class that connects Chargers to one another
class Edge {
    public:
        Edge(){};
        Edge(int destID, int dist);
        int getDistance();
        int getDestChargerID();
      
    public:
        int destChargerID;
        int distance;
};