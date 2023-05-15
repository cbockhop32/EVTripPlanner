#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>


#include "network.hpp"
#include "helper_functions.hpp"

// This will grab all the data from the CSV file and then return a vector of tuples containing the name, lat, and long
// CITATION: Adapted from Java2Blog.com "How to read CSV file in C++"
vector<tuple<string,double,double>> getChargersFromFile(string csvPath, string start, string end){
    vector<tuple<string,double,double>> chargerList;
    tuple<string,double,double> row;
    string line;
    string word;
    fstream file(csvPath, ios::in);
    if(file.is_open())
    {   
        //  Getting the beginnig charger and the final charger
        // Outer loop loops through each line int he file
        while(getline(file,line)) {
            int i =0;
            stringstream str(line);
            string chargerName;
            double lat;
            double lon;

            while(getline(str,word,','))
            {
                // CITATION: from stackoverflow "Converting a string to a double c++"
                istringstream iss(word);
                // If index is 1 or 2, we are getting the lat and lon from the CSV file
                switch(i){
                    case 0:
                        chargerName = word;
                    case 1:
                        iss >> lat;
                    case 2:
                        iss >> lon;
                }
                i++;
            }
            row = {chargerName,lat,lon};
            chargerList.push_back(row);
        }

    } else {
        cerr << "Could not open CSV file" << '\n';
    }
    return chargerList;
}

void printShortestPath(vector<int> path, Network chargingNetwork, string startingChargerName, string endingChargerName)
{
   Charger prev = chargingNetwork.getChargerByName(startingChargerName);

    while(!path.empty())
    {
        int curr = path.back();
        path.pop_back();
        Charger charger = chargingNetwork.getChargerByID(curr);

        // Calculating the distance between the two chargers
        float distanceDriven = chargingNetwork.CalcGPSDistance(prev.getChargerLatitude(), prev.getChargerLongitude(),charger.getChargerLatitude(), charger.getChargerLongitude());

        if(charger.getChargerName() == startingChargerName || charger.getChargerName() == endingChargerName)
        {
            cout << charger.getChargerName() << '\n';
        } else {
            // Charging time to full
            float chargingTime = chargingNetwork.calculateChargingTime(prev, charger, distanceDriven);

            cout << charger.getChargerName() << " - " << ceilf(chargingTime*100)/100 << " Minutes Charging Time"<<'\n';
            // Update previous charger so we can calculate the next distance
            prev = charger;
        }
    }

}