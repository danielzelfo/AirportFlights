#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <iomanip>
#include <algorithm>

#include "Graph.h"
#include "AdjacencyListGraph.h"
#include "DijkstraShortestPath.h"

using namespace std;

class AirlineFlights {
public:
	
	AirlineFlights() { }

	//constructor using two files
	AirlineFlights(string airportsFilePath, string flightsFilePath) : g(true) {
		ifstream airportsFile(airportsFilePath);
		ifstream flightsFile(flightsFilePath);

		string airportSymbol, airportName, airportSymbol1, airportSymbol2, flightId;
		float cost;

		//inputting all airports information
		while (airportsFile >> airportSymbol) {
			getline(airportsFile, airportName);
			airportName.erase(airportName.begin(), std::find_if(airportName.begin(), airportName.end(), [](int ch) {
				return !std::isspace(ch);
			}));
			//inserting airport into graph
			airports[airportSymbol] = g.insertVertex(make_pair(airportSymbol, airportName));
		}

		//inputting all flights information
		while (flightsFile >> airportSymbol1 >> airportSymbol2 >> cost >> flightId) {
			//inserting flight into graph
			/*flights[flightId] = */g.insertEdge(airports[airportSymbol1], airports[airportSymbol2], cost);
			flightIds[airportSymbol1 + airportSymbol2] = flightId;
			//flightIds[airportSymbol2 + airportSymbol1] = flightId;
		}
	
		airportsFile.close(); flightsFile.close();
	}

	void menu() {
		char option;
		string option1, option2;
		Vertex<V>* v1, * v2;

		string options = "1. Display airport information\n2. Find a cheapest flight from one airport to another airport\n3. Find a cheapest roundtrip from one airport to another airport\n4. Add a flight from one airport to another airport\n5. Delete a flight from one airport to another airport\n6. Find a flight with fewest stops from one airport to another airport\n7. Find all flights from one airport to another airport\n8. Find an order to visit all airports starting from an airport\n9. Delete an existing airport\nQ. Exit\n>";
		//string options = "1. Display airport information\n2. Find a cheapest flight from one airport to another airport\n3. Find a cheapest roundtrip from one airport to another airport\n4. Add a flight from one airport to another airport\n5. Delete a flight from one airport to another airport\n6. Find a flight with fewest stops from one airport to another airport\n9. Delete an existing airport\nQ. Exit\n>";
		cout << options;
		cin >> option;

		while (option != 'Q') {
			

			if (option == '0') {
				list<Vertex<V>*> vertices = g.getVertices();
				//looping through each airport
				for (auto itr = vertices.begin(); itr != vertices.end(); itr++) {
					//outputting airport
					cout << "Airport " << (*itr)->getElement().first << " at " << (*itr)->getElement().second << endl;
					//outputting flights
					outputFlights(*itr);
				}
				cout << endl;

			//Display airport information
			}else if (option == '1'){
				cout << "Enter 3-letter airport code: ";
				cin >> option1;
				if (airports.find(option1) == airports.end()) {
					cout << "Invalid airport.\n\n";
					goto input;
				}

				Vertex<V>* v = airports[option1];
				cout << "at " << v->getElement().second << endl;
				outputFlights(v);
			
			//Find a cheapest flight from one airport to another airport
			}else if (option == '2'){
				//inputting airport 1
				cout << "Enter airport 1 code: ";
				cin >> option1;
				if (airports.find(option1) == airports.end()) {
					cout << "Invalid airport.\n\n";
					goto input;
				}
				v1 = airports[option1];

				//inputting airport 2
				cout << "Enter airport 2 code: ";
				cin >> option1;
				if (airports.find(option1) == airports.end()) {
					cout << "Invalid airport.\n\n";
					goto input;
				}
				v2 = airports[option1];

				//using dijikstra algorithm
				pair<E, vector<Vertex<V>*>> cheapestPath = shortestPathLengths<V, E>(g, v1)[v2];

				//outputting cheapest trip cost
				cout << "Cheapest trip from "<< v1->getElement().first <<" to "<< v2->getElement().first <<": $" << cheapestPath.first << endl;
				//outputting cheapest trip path
				for (int i = 0; i < cheapestPath.second.size(); i++){
					cout << cheapestPath.second[i]->getElement().first << (i < cheapestPath.second.size() - 1 ? " -- " + flightIds[cheapestPath.second[i]->getElement().first + cheapestPath.second[i+1]->getElement().first] + " -> " : "\n\n");
				}
				
			//Find a cheapest roundtrip from one airport to another airport
			}else if (option == '3'){
				
				//inputting the first airport
				cout << "Enter airport 1 Code: ";
				cin >> option1;
				if (airports.find(option1) == airports.end()) {
					cout << "Invalid airport.\n\n";
					goto input;
				}
				v1 = airports[option1];

				//inputting the second airport
				cout << "Enter airport 2 code: ";
				cin >> option1;
				if (airports.find(option1) == airports.end()) {
					cout << "Invalid airport.\n\n";
					goto input;
				}
				v2 = airports[option1];

				//using dijikstra algorithm
				//shortest path from start to end and end to start
				pair<E, vector<Vertex<V>*>> cheapestPathThere = shortestPathLengths<V, E>(g, v1)[v2];
				pair<E, vector<Vertex<V>*>> cheapestPathBack = shortestPathLengths<V, E>(g, v2)[v1];
				
				//outputting the total cost of the cheapest round trip
				cout << "Cheapest round trip from " << v1->getElement().first << " to " << v2->getElement().first << ": $" << cheapestPathThere.first + cheapestPathBack.first << endl;
				//outputting the path of the cheapest round trip
				for (int i = 0; i < cheapestPathThere.second.size(); i++) 
					cout << cheapestPathThere.second[i]->getElement().first << (i < cheapestPathThere.second.size() - 1 ? " -- " + flightIds[cheapestPathThere.second[i]->getElement().first + cheapestPathThere.second[i + 1]->getElement().first] + " -> " : "");
				for (int i = 0; i < cheapestPathBack.second.size(); i++) 
					cout << (i != 0 ? cheapestPathBack.second[i]->getElement().first : "") << (i < cheapestPathBack.second.size() - 1 ? " -- " + flightIds[cheapestPathBack.second[i]->getElement().first + cheapestPathBack.second[i + 1]->getElement().first] + " -> " : "\n\n");
				
			//Add a flight from one airport to another airport
			}else if (option =='4'){
				string a1Symbol, a2Symbol;
				float fCost;

				//inputting first airport code
				cout << "Enter first airport code: ";
				cin >> a1Symbol;

				//adding airport 1 if it doesn't exist
				if (airports.find(a1Symbol) == airports.end()) {
					cout << "Enter first airport name: ";
					cin.ignore();
					getline(cin, option1);
					airports[a1Symbol] = g.insertVertex(make_pair(a1Symbol, option1));
				}
				v1 = airports[a1Symbol];

				//inputting second airport code
				cout << "Enter second airport symbol: ";
				cin >> a2Symbol;
				//adding airport 2 if it doesn't exist
				if (airports.find(a2Symbol) == airports.end()) {
					cout << "Enter second airport name: ";
					cin.ignore();
					getline(cin, option1);
					airports[a2Symbol] = g.insertVertex(make_pair(a2Symbol, option1));
				}
				v2 = airports[a2Symbol];

				//inputting flight id and cost
				cout << "Enter flight ID: ";
				cin >> option1;
				cout << "Enter flight cost: ";
				cin >> fCost;

				//adding flight
				/*flights[fID] = */g.insertEdge(v1, v2, fCost);
				flightIds[a1Symbol + a2Symbol] = option1;
				//flightIds[a2Symbol + a1Symbol] = option1;
				cout << "Flight added.\n\n";
			
			//Delete a flight from one airport to another airport
			}else if (option == '5'){
				Edge<E>* e;

				//inputting airport 1
				cout << "Enter airport 1 code: ";
				cin >> option1;
				if (airports.find(option1) == airports.end()) {
					cout << "Invalid airport.\n\n";
					goto input;
				}

				//inputting airport 2
				cout << "Enter airport 2 code: ";
				cin >> option2;
				if (airports.find(option2) == airports.end()) {
					cout << "Invalid airport.\n\n";
					goto input;
				}

				//deleting flight if it exists
				e = g.getEdge(airports[option1], airports[option2]);
				if (e != nullptr) {
					g.removeEdge(e);
					flightIds.erase(option1 + option2);
					flightIds.erase(option2 + option1);
					cout << "Flight from " << option1 << " to " << option2 << " deleted.\n\n";
				}
				else{
					//trying to find flight going the other way
					e = g.getEdge(airports[option2], airports[option1]);
					if (e != nullptr) {
						g.removeEdge(e);
						flightIds.erase(option1 + option2);
						flightIds.erase(option2 + option1);
						cout << "Flight from " << option2 << " to " << option1 << " deleted.\n\n";
					}else
						cout << "Flight does not exist.\n\n";
				}

			//Find a flight with fewest stops from one airport to another airport
			}else if (option == '6'){

				//inputting first airport
				cout << "Enter airport 1 code: ";
				cin >> option1;
				if (airports.find(option1) == airports.end()) {
					cout << "Invalid airport.\n\n";
					goto input;
				}
				v1 = airports[option1];

				//inputting second airport
				cout << "Enter airport 2 code: ";
				cin >> option1;
				if (airports.find(option1) == airports.end()) {
					cout << "Invalid airport.\n\n";
					goto input;
				}
				v2 = airports[option1];

				//using dijkstrashortedpath (unweighted)
				pair<E, vector<Vertex<V>*>> cheapestPath = shortestPathLengths<V, E>(g, v1, false)[v2];
				//outputting the shortest trip
				cout << "Shortest trip from " << v1->getElement().first << " to " << v2->getElement().first << ": $" << cheapestPath.first << endl;
				for (int i = 0; i < cheapestPath.second.size(); i++)
					cout << cheapestPath.second[i]->getElement().first << (i < cheapestPath.second.size() - 1 ? " -- " + flightIds[cheapestPath.second[i]->getElement().first + cheapestPath.second[i + 1]->getElement().first] + " -> " : "\n\n");

			//Find all flights from one airport to another airport
			}else if (option == '7'){
				cout << "Unavailable.\n\n";

			//Find an order to visit all airports starting from an airport
			}else if (option == '8'){
				cout << "Unavailable.\n\n";

			//Delete an existing airport
			}else if (option == '9') {
				//inputting airport
				cout << "Enter airport code: ";
				cin >> option1;
				if (airports.find(option1) == airports.end()) {
					cout << "Invalid airport.\n\n";
					goto input;
				}

				//deleting airport
				g.removeVertex(airports[option1]);
				cout << "Airport deleted.\n\n";
			
			}else{
				cout << "Invalid Option!\n\n";
			}

		input:
			cout << options;
			cin >> option;
		}

		//writing the airports and flights to file
		ofstream outputFlights("P4FlightsRev1.txt"),
				 outputAirports("P4AirportsRev1.txt");
		list<Vertex<V>*> finalAirports = g.getVertices();
		list<Edge<E>*> finalFlights = g.getEdges();
		for (auto const& i : finalAirports) 
			outputAirports << i->getElement().first << "    " << i->getElement().second << "\n";
		for (auto const& i : finalFlights)
			outputFlights << g.endVertices(i)[0]->getElement().first << "   " << g.endVertices(i)[1]->getElement().first << setw(10) << right << fixed << setprecision(2) << i->getElement() << "  " << flightIds[g.endVertices(i)[0]->getElement().first + g.endVertices(i)[1]->getElement().first] << "\n";
		outputFlights.close(); outputAirports.close();

		cout << "Thank you for using my program.\n";

	}



private:

	typedef pair<string, string> V;
	typedef float E;

	void outputFlights(Vertex<V>* v) {
		cout << " " << g.outDegree(v) << " outgoing flights: ";
		for (auto e : g.outgoingEdges(v))
			cout << "(" << g.opposite(v, e)->getElement().first << ", " << "id=" << flightIds[(v)->getElement().first + g.opposite(v, e)->getElement().first] << " cost=$" << fixed << setprecision(2) << e->getElement() << ")" << "  ";
		cout << endl;

		//outputting incoming flights information
		cout << " " << g.inDegree(v) << " incoming flights: ";
		for (auto e : g.incomingEdges(v))
			cout << "(" << g.opposite(v, e)->getElement().first << ", " << "id=" << flightIds[(v)->getElement().first + g.opposite(v, e)->getElement().first] << " cost=$" << fixed << setprecision(2) << e->getElement() << ")" << "  ";
		cout << "\n\n";
	}

	//the graph
	AdjacencyListGraph<V, E> g;

	//airport symbol to vertex
	map<string, Vertex<V>*> airports;

	//flight id to edge
	//map<string, Edge<E>*> flights;
	//flight id from two airports ex: LAX & SFO: flightId["LAXSFO"] or flightId["SFOLAX"]
	map<string, string> flightIds;

};