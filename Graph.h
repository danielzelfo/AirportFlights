#pragma once
#pragma once
#include <vector>
#include <list>
#include <string>

using namespace std;

// Created by T. Vo for CSCI 230
// Based on Java version of Goodrich book w/o template
// string for vertex and int for edge

template <typename V>
class Vertex		// behaves like interface in Java
{
public:
	virtual V getElement() = 0;
};

template <typename E>
class Edge			// behaves like interface in Java
{
public:
	virtual E getElement() = 0;
};

template <typename V, typename E>
class Graph
{
public:
	/* Returns the number of vertices of the graph */
	virtual int numVertices() = 0;

	/* Returns the number of edges of the graph */
	virtual int numEdges() = 0;

	/* Returns the vertices of the graph as an iterable collection */
	virtual list<Vertex<V>*> getVertices() = 0;

	/* Returns the edges of the graph as an iterable collection */
	virtual list<Edge<E>*> getEdges() = 0;

	/*
	* Returns the number of edges leaving vertex v.
	* returned by inDegree
	* throws IllegalArgumentException if v is not a valid vertex?
	*/
	virtual int inDegree(Vertex<V>* v) = 0; // throws IllegalArgumentException;


	virtual int outDegree(Vertex<V>* v) = 0; // throws IllegalArgumentException;

	/*
	* Returns an iterable collection of edges for which vertex v is the origin.
	* returned by incomingEdges.
	* throws IllegalArgumentException if v is not a valid vertex
	*/
	virtual vector<Edge<E>*> outgoingEdges(Vertex<V>* v) = 0; // throws IllegalArgumentException;

	virtual vector<Edge<E>*> incomingEdges(Vertex<V>* v) = 0; // throws IllegalArgumentException;



	/** Returns the edge from u to v, or null if they are not adjacent. */
	virtual Edge<E>* getEdge(Vertex<V>* u, Vertex<V>* v) = 0; // throws IllegalArgumentException;

	/*
	* Returns the vertices of edge e as an array of length two.
	* the order is arbitrary.
	*/
	virtual vector<Vertex<V>*> endVertices(Edge<E>* e) = 0; // throws IllegalArgumentException;

	/* Returns the vertex that is opposite vertex v on edge e. */
	virtual Vertex<V>* opposite(Vertex<V>* v, Edge<E>* e) = 0; // throws IllegalArgumentException;

	/* Inserts and returns a new vertex with the given element. */
	virtual Vertex<V>* insertVertex(V element) = 0;

	/*
	* Inserts and returns a new edge between vertices u and v, storing given element.
	*
	* throws IllegalArgumentException if u or v are invalid vertices, or if an edge already exists between u and v.
	*/
	virtual Edge<E>* insertEdge(Vertex<V>* u, Vertex<V>* v, E element) = 0; // throws IllegalArgumentException;

	/* Removes a vertex and all its incident edges from the graph. */
	virtual void removeVertex(Vertex<V>* v) = 0; // throws IllegalArgumentException;

	/* Removes an edge from the graph. */
	virtual void removeEdge(Edge<E>* e) = 0; // throws IllegalArgumentException;

};

