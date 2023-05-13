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

Example:  ./solution network.csv Redondo_Beach_CA Bozeman_MT
