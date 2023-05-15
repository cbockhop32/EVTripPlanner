#pragma once

using namespace std;

vector<tuple<string,double,double>> getChargersFromFile(string csvPath, string start, string end);
void printShortestPath(vector<int> path, Network chargingNetwork, string startingChargerName, string endingChargerName);

