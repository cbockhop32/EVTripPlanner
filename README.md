# EVTripPlanner


## Background

This program will take a CSV file that has names and locations (by GPS coordinates: latitude and longitude) and parse the CSV file to create a network of chargers.
Then the user the input two names of chargers within the network/CSV file and the program will return the shortest route between those two points, giving you
the necessary charger stops and charging times at each charger on your way to the destination.

The program assumes that your hypothetical electric car has a fixed range and the path route will be depended on the vehichle's range

## Compiling Program

Run the provided bash script to compile the program: ./build.sh

## Running the program 


./solution [name of csv file].csv [Charger Name 1] [Charger Name 2]

Example:  
./solution network.csv Hawthorne_CA Bozeman_MT

Output:
Hawthorne_CA
Barstow_CA - 11.53 Minutes Charging Time
Las_Vegas_NV - 17.16 Minutes Charging Time
St._George_UT - 13.02 Minutes Charging Time
Beaver_UT - 11.25 Minutes Charging Time
Tooele_UT - 20.43 Minutes Charging Time
Tremonton_UT - 8.56 Minutes Charging Time
Idaho_Falls_ID - 14.81 Minutes Charging Time
Bozeman_MT
