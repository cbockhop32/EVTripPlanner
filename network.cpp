#include "network.hpp"

void Network::addCharger(Charger charger)
{
    // checking if charger already exists
    if(checkIfChargerExists(charger.getChargerID())) {
        cout << "Charger already exists" << '\n';
    } else {
        chargers.push_back(charger);
    }

};

bool Network::checkIfChargerExists(int id)
{
    bool exists = false;

    for(auto& c: chargers)
    {
        if(c.getChargerID() == id){
            exists = true;
            break;
        }
    }
    return exists;
};

bool Network::checkIfEdgeExists(int id1, int id2)
{   
    // Get the first charger and its edge list
    Charger c = getChargerByID(id1);
    list<Edge> chargerEdges; 
    chargerEdges = c.getEdgeList(); // This is the edges within that specific charger

    //Loop through all the edges in the charger and check if there is an edge with id2 as the destination
    for(auto& edge : chargerEdges)
    {
        if(edge.getDestChargerID() == id2){
            return true;
        }
    }

    return false;
};


  Charger Network::getChargerByID(int chargerID)
{
    Charger res;
    for(auto& c : chargers)
    {
        if(c.getChargerID() == chargerID)
        {
            res = c;
            break;
        }
    }
    return res;
};


Charger Network::getChargerByName(string chargerName)
{
    Charger res;
    for(auto& c : chargers)
    {
        if(c.getChargerName() == chargerName)
        {
            res = c;
            break;
        }
    }
    return res;
};

void Network::addEdge(int startID, int destinationID, int weight)
{
    bool chargerOneExists = checkIfChargerExists(startID);
    bool chargerTwoExists = checkIfChargerExists(destinationID);

    if(chargerOneExists && chargerTwoExists) 
    {
        // Both chargers exist, check if the passed in edge exists or not
        bool edgeExists = checkIfEdgeExists(startID,destinationID);

        if(!edgeExists) {
            for(int i =0; i < chargers.size(); i++) 
            {
                if(chargers.at(i).getChargerID() == startID){
                    Edge e(destinationID,weight);
                    chargers.at(i).edges.push_back(e);
                } else if(chargers.at(i).getChargerID() == destinationID){
                    Edge e(startID,weight);
                    chargers.at(i).edges.push_back(e);
                }
            }
        } 
        
    } else {
        if(chargerOneExists == false) {
            cerr << "Error: Charger With The ID " << startID << " Does Not Exist\n";
        }
        if(chargerTwoExists == false){
            cerr << "Error: Charger With The ID " << destinationID << " Does Not Exist\n";
        }
    }
};


// Method that creates the graph data structure by looping through the vector that was created from the CSV file and creates a Charger instance for each of them
void Network::buildChargerNetwork(vector<tuple<string,double,double>> chargersFromCSV)
{
    int id = 1;
    for(auto& c : chargersFromCSV )
    {
        string chargerName = get<0>(c);
        double lat = get<1>(c);
        double lon = get<2>(c);
        
        Charger newCharger {id, lat, lon, chargerName};

        addCharger(newCharger);
        id++;
    }
}


// Helper method to add all the edges between the necessary Chargers, uses the cars max range to decide if an Edge will exist between two Chargers
void Network::addEdgesToChargerNetwork(int maxCarRange)
{
    // Loop thread evey charger
    for(auto& c1 : chargers)
    {
        int id1 = c1.getChargerID();

        for(auto& c2 : chargers)
        {
            int id2 = c2.getChargerID();

            // If we are looking at the same charger then skip it
            if(id2 == id1) continue;

            double lat1 = c1.getChargerLatitude();
            double lat2 = c2.getChargerLatitude();
            double lon1 = c1.getChargerLongitude();
            double lon2 = c2.getChargerLongitude();


            int distBetween = CalcGPSDistance(lat1,lon1,lat2,lon2);

            // If the distance between the two chargers is less than the cars max range
            // Then create an edge between those two chargers (vertices)
            if(distBetween < maxCarRange)
            {
                addEdge(id1,id2, distBetween);
            }
        }
    }

    //Then inner loop loop through all the others ones and calculating distance
    // If distance is less than car total range, then add edge
};


float Network::calculateChargingTime(Charger startLocation, Charger endLocation, float distanceDriven)
{

    // Calculate distance betweent the two chargers
    int lat1 = startLocation.getChargerLatitude();
    int lon1 = startLocation.getChargerLongitude();
    int lat2 = endLocation.getChargerLatitude();
    int lon2 = endLocation.getChargerLongitude();

    int distance = CalcGPSDistance(lat1,lon1,lat2,lon2);

    float chargingTimeMin = (distanceDriven / 498) * 60; // charging at 800km /hr or 498mi/hr

    return chargingTimeMin;
};
        
 // Function to calculate the shortest distance and path between two chargers using Dijkstra's Algorithm
// CITATION: Adapted GeekForGeeks implementaion of Dijkstra's Algorithm to work with my graph structure
vector<int> Network::calculateShortestDistance(string startName, string endName)
{
    Charger startCharger = getChargerByName(startName);
    Charger endCharger = getChargerByName(endName);

    // Initalize vector to repsresent distances to all the chargers, set all it infinity at first
    vector<int> distances(chargers.size(),INT_MAX);

    // Vector that represents the previous nodes that lead to the shortest distance for each respective node
    vector<int> previous(chargers.size(), INT_MAX);

    // Creating a prioerity queue that will hold the distance and the Charger ID
    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> queue;

    // Adding the distance and the charger ID of the source Charger
    queue.push(make_pair(0,startCharger.getChargerID()));
    // Set the distance of that starting charger to 0
    distances[startCharger.getChargerID()-1] = 0;
    
    vector<int> stack;

    while(!queue.empty()){
        // Pop the next charger ID off the priotiy queue (with the lowest distance)
        int currChargerID = queue.top().second;
        queue.pop();
        
        // Getting the Charger for the ID that we just popped off the queue
        Charger curr = getChargerByID(currChargerID);

        // Checking to see if we reached out destination charger
        if(currChargerID == endCharger.getChargerID())
        {

            // cout << "Destination found" << endl;

            stack.push_back(endCharger.getChargerID());

            int currPathID = endCharger.getChargerID();


            while(previous[currPathID-1] != INT_MAX) {

                stack.push_back(previous[currPathID-1]);
                currPathID = previous[currPathID-1];

            }

            return stack;
        }


        // Loop thhrough all adjacent chargers to the current one
        for(Edge& c : curr.getEdgeList())
        {
            // Get the the ID of the destination charger (zero-index first) and then update the distance
            int adjChargerID = c.getDestChargerID();
            int dist = c.getDistance();

            if(distances[adjChargerID-1] > (distances[currChargerID-1] + dist))
            {
                distances[adjChargerID-1] = (distances[currChargerID-1] + dist);
                previous[adjChargerID-1] = currChargerID;
                queue.push(make_pair(distances[adjChargerID-1],adjChargerID));
                
            }
        }
    }

    return stack;
    
};

//Helper function that calculates the distance between two points 
// CITATION: StackOverflow
double Network::CalcGPSDistance(double latitud1, double longitud1, double latitud2, double longitud2)
{
    double haversine;
    double temp;
    double distance;

    latitud1  = latitud1  * DEGREES_RADIANS;
    longitud1 = longitud1 * DEGREES_RADIANS;
    latitud2  = latitud2  * DEGREES_RADIANS;
    longitud2 = longitud2 * DEGREES_RADIANS;

    haversine = (pow(sin((1.0 / 2) * (latitud2 - latitud1)), 2)) + ((cos(latitud1)) * (cos(latitud2)) * (pow(sin((1.0 / 2) * (longitud2 - longitud1)), 2)));
    temp = 2 * asin(min(1.0, sqrt(haversine)));
    distance = EARTH_RADIUS  * temp;

    return distance;
};

// Helper function that was used during testing
void Network::printNetwork()
{
    for(auto& c : chargers) 
    {
        cout << c.getChargerName() << " (" << c.getChargerID() << ") " << "(" << c.getChargerLatitude() << ' ' << c.getChargerLongitude() << "):" ;
        c.printEdges();
    }
}


