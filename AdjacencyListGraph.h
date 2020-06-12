#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "Graph.h"

using namespace std;


// Based on T. Vo AdjacencyMapGraph for CSCI 230


//Adjacency List Graph class
template <typename V, typename E>
class AdjacencyListGraph : public Graph<V, E>
{
private:
	list<Vertex<V>*> vertices;
	list<Edge<E>*> edges;
	bool directed;

	/* A vertex of an adjacency map graph representation. */
	class InnerVertex : public Vertex<V> {
	private:
		V element;
		//Position<Vertex<V>> pos;
		Vertex<V>* pos;
		list<pair<Vertex<V>*, Edge<E>*>>* outgoing;
		list<pair<Vertex<V>*, Edge<E>*>>* incoming;

	public:

		/* Constructs a new InnerVertex instance storing the given element. */
		InnerVertex(V elem) {
			element = elem;
			//			adjacent = new vector<pair<Vertex *, Edge *>>();
			outgoing = new list<pair<Vertex<V>*, Edge<E>*>>();
			incoming = new list<pair<Vertex<V>*, Edge<E>*>>();

		}

		/* Returns the element associated with the vertex. */
		V getElement() { return element; }

		/* Stores the position of this vertex within the graph's vertex list. */
		void setPosition(Vertex<V>* p) { pos = p; }

		/* Returns the position of this vertex within the graph's vertex list. */
		Vertex<V>* getPosition() { return pos; }


		list<pair<Vertex<V>*, Edge<E>*>>* getOutgoingEdges() { return outgoing; }

		list<pair<Vertex<V>*, Edge<E>*>>* getIncomingEdges() { return incoming; }


	}; //------------ end of InnerVertex class ------------

	//---------------- nested InnerEdge class ----------------
	/* An edge between two vertices. */
	class InnerEdge : public Edge<E> {
	private:
		E element;
		Edge<E>* pos;
		vector<Vertex<V>*> endpoints;

	public:
		/* Constructs InnerEdge instance from u to v, storing the given element. */
		InnerEdge(Vertex<V>* u, Vertex<V>* v, E elem) {
			element = elem;
			endpoints.push_back(u);
			endpoints.push_back(v);
		}

		/* Returns the element associated with the edge. */
		E getElement() { return element; }

		/* Returns reference to the endpoint array. */
		vector<Vertex<V>*> getEndpoints() { return endpoints; }

		/* Stores the position of this edge within the graph's vertex list. */
		void setPosition(Edge<E>* p) { pos = p; }

		/* Returns the position of this edge within the graph's vertex list. */
		Edge<E>* getPosition() { return pos; }
	}; //------------ end of InnerEdge class ------------

public:
	/*
	* Constructs an empty graph.
	*
	*/
	AdjacencyListGraph(bool d=false) : directed(d){
	}

	~AdjacencyListGraph() {
		// should deallocate memory here
	}

	/* Returns the number of vertices of the graph */
	int numVertices() {
		return static_cast<int>(vertices.size());
	}

	/* Returns the number of edges of the graph */
	int numEdges() {
		return static_cast<int>(edges.size());
	}

	/* Returns the vertices of the graph as an iterable collection */
	list<Vertex<V>*> getVertices() {
		return vertices;
	}

	/* Returns the edges of the graph as an iterable collection */
	list<Edge<E>*> getEdges() {
		return edges;
	}

	/*
	* Returns the number of edges leaving vertex v.
	* returned by inDegree
	* throws IllegalArgumentException if v is not a valid vertex?
	*/
	int outDegree(Vertex<V>* v) { // throws IllegalArgumentException
		InnerVertex* vert = static_cast<InnerVertex*>(v);
		return static_cast<int>(vert->getOutgoingEdges()->size());
	}

	/*
	* Returns the number of edges leaving vertex v.
	* returned by inDegree
	* throws IllegalArgumentException if v is not a valid vertex?
	*/
	int inDegree(Vertex<V>* v) { // throws IllegalArgumentException
		InnerVertex* vert = static_cast<InnerVertex*>(v);
		return static_cast<int>(vert->getIncomingEdges()->size());
	}

	/*
	* Returns an iterable collection of edges for which vertex v is the origin.
	* returned by incomingEdges.
	* throws IllegalArgumentException if v is not a valid vertex
	*/
	vector<Edge<E>*> incomingEdges(Vertex<V>* v) { // throws IllegalArgumentException
		vector<Edge<E>*> temp;
		list<pair<Vertex<V>*, Edge<E>*>>* mapPtr = static_cast<InnerVertex*>(v)->getIncomingEdges();
		for (auto it = mapPtr->begin(); it != mapPtr->end(); ++it) {
			temp.push_back(it->second);
		}
		return temp;
	}



	/*
	* Returns an iterable collection of edges for which vertex v is the origin.
	* returned by incomingEdges.
	* throws IllegalArgumentException if v is not a valid vertex
	*/
	vector<Edge<E>*> outgoingEdges(Vertex<V>* v) { // throws IllegalArgumentException
		vector<Edge<E>*> temp;
		list<pair<Vertex<V>*, Edge<E>*>>* mapPtr = static_cast<InnerVertex*>(v)->getOutgoingEdges();
		for (auto it = mapPtr->begin(); it != mapPtr->end(); ++it) {
			temp.push_back(it->second);
		}
		return temp;
	}

	/*
	* Returns an iterable collection of edges for which vertex v is the destination.
	* returned by adjacencyEdges.
	* throws IllegalArgumentException if v is not a valid vertex
	*/

	/* Returns the edge from u to v, or null if they are not adjacent. */
	Edge<E>* getEdge(Vertex<V>* u, Vertex<V>* v) { // throws IllegalArgumentException;
		Edge<E>* temp = nullptr;
		list<pair<Vertex<V>*, Edge<E>*>>* listPtr = static_cast<InnerVertex*>(u)->getOutgoingEdges();

		for (auto itf = listPtr->begin(); itf != listPtr->end(); itf++) {
			if (itf->first == static_cast<InnerVertex*>(v))
				return itf->second;
		}

		return nullptr;
	}

	/*
	* Returns the vertices of edge e as an array of length two.
	* the order is arbitrary.
	*/
	vector<Vertex<V>*> endVertices(Edge<E>* e) {// throws IllegalArgumentException;
		vector<Vertex<V>*> endpoints = static_cast<InnerEdge*>(e)->getEndpoints();
		return endpoints;
	}

	/* Returns the vertex that is opposite vertex v on edge e. */
	Vertex<V>* opposite(Vertex<V>* v, Edge<E>* e) { // throws IllegalArgumentException;
		vector<Vertex<V>*> endpoints = static_cast<InnerEdge*>(e)->getEndpoints();

		if (endpoints[0] == v)
			return endpoints[1];
		else
			return endpoints[0];
	}

	/* Inserts and returns a new vertex with the given element. */
	Vertex<V>* insertVertex(V element) {
		Vertex<V>* v = new InnerVertex(element);
		vertices.push_back(v);
		static_cast<InnerVertex*>(v)->setPosition(vertices.back());
		return v;
	}

	/*
	* Inserts and returns a new edge between vertices u and v, storing given element.
	*
	* throws IllegalArgumentException if u or v are invalid vertices, or if an edge already exists between u and v.
	*/
	Edge<E>* insertEdge(Vertex<V>* u, Vertex<V>* v, E element) { // throws IllegalArgumentException;
		Edge<E>* e = new InnerEdge(u, v, element);
		edges.push_back(e);
		static_cast<InnerEdge*>(e)->setPosition(edges.back());
		InnerVertex* origin = static_cast<InnerVertex*>(u);
		InnerVertex* dest = static_cast<InnerVertex*>(v);
		(origin->getOutgoingEdges())->push_back(pair<Vertex<V>*, Edge<E>*>(v, e));
		(dest->getIncomingEdges())->push_back(pair<Vertex<V>*, Edge<E>*>(u, e));
		if(!directed){
			(dest->getOutgoingEdges())->push_back(pair<Vertex<V>*, Edge<E>*>(u, e));
			(origin->getIncomingEdges())->push_back(pair<Vertex<V>*, Edge<E>*>(v, e));
		}
		return e;
	}

	/* Removes a vertex and all its incident edges from the graph. */
	void removeVertex(Vertex<V>* v) { // throws IllegalArgumentException;

		list<pair<Vertex<V>*, Edge<E>*>> l1 = *(static_cast<InnerVertex*>(v)->getOutgoingEdges());
		for (typename list<pair<Vertex<V>*, Edge<E>*>>::iterator it = l1.begin(); it != l1.end(); ++it)
			removeEdge((*it).second);

		
		list<pair<Vertex<V>*, Edge<E>*>> l2 = *(static_cast<InnerVertex*>(v)->getIncomingEdges());
		for (typename list<pair<Vertex<V>*, Edge<E>*>>::iterator it = l2.begin(); it != l2.end(); ++it)
			removeEdge((*it).second);
		
		

		// remove this vertex from the list of vertices
		vertices.remove(static_cast<InnerVertex*>(v)->getPosition());
	}

	/* Removes an edge from the graph. */
	void removeEdge(Edge<E>* e) { // throws IllegalArgumentException;
		// remove this edge from vertices' adjacencies
		vector<Vertex<V>*> verts = static_cast<InnerEdge*>(e)->getEndpoints();
		((static_cast<InnerVertex*>(verts[0]))->getOutgoingEdges())->remove(pair<Vertex<V>*, Edge<E>*>(verts[1], e));
		((static_cast<InnerVertex*>(verts[1]))->getIncomingEdges())->remove(pair<Vertex<V>*, Edge<E>*>(verts[0], e));
		if (!directed) {
			((static_cast<InnerVertex*>(verts[0]))->getIncomingEdges())->remove(pair<Vertex<V>*, Edge<E>*>(verts[1], e));
			((static_cast<InnerVertex*>(verts[1]))->getOutgoingEdges())->remove(pair<Vertex<V>*, Edge<E>*>(verts[0], e));
		}

		//// remove this edge from the list of edges
		edges.remove(static_cast<InnerEdge*>(e)->getPosition());

	}

	void print() {
		for (auto itr = vertices.begin(); itr != vertices.end(); itr++)
		{
			cout << "Vertex " << (*itr)->getElement().first << " " << (*itr)->getElement().second << endl;

			cout << " " << outDegree(*itr) << (directed ? " outgoing:" : " adjacencies:");
			for (auto e : outgoingEdges(*itr))
				cout << "(" << opposite(*itr, e)->getElement().first << ", " << e->getElement().first << " " << e->getElement().second << ")" << "  ";
			cout << endl;
			if (directed) {
				cout << " " << inDegree(*itr) << " incoming:";
				for (auto e : incomingEdges(*itr))
					cout << "(" << opposite(*itr, e)->getElement().first << ", " << e->getElement().first << " " << e->getElement().second << ")" << "  ";
				cout << endl;
			}

		}
	}
};

