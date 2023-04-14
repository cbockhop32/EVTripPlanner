#pragma once

using namespace std;

vector<tuple<string,double,double>> getChargersFromFile(string csvPath, string start, string end);
void printShortestPath(stack<int> path, Network chargingNetwork, string startingChargerName, string endingChargerName);

