/*  Program: Airline FLights Program (EXTRA CREDIT)
 *	Author: Daniel Zelfo
 *	Class: CSCI 230
 *	Date: 6/1/2020
 *	Description: This program includes a AirlineFlights class, which uses a graph to perform varias operations using airports and flights.
 *               It can be constructed using a file of the airports and a file of the flights. After all the operations, it will write to two new file the final airports and flights.
 *               It can show information about a given airport, show the cheapest flight from one airport to another, show the cheapest round trip from one flight to another, 
 *               add a flight from one given airport to another given airport, delete a flight between two given flights, show the trip from one given airport to another given airport with the least number of stops, and delete a given airport
 *
 * I certify that the code below is my own work.
 *
 *	Exception(s): N/A
 *
 */

#include <iostream>
#include "AirlineFlights.h"


int main()
{
    cout << "Airline Flights Program by Daniel Zelfo\n\n";

    AirlineFlights af("P4Airports.txt", "P4Flights.txt");
    af.menu();
}
