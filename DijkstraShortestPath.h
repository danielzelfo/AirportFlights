#pragma once
#include <map>
#include <queue>
#include <vector>
#include <utility>

#include "Graph.h"
#include "AdjacencyListGraph.h"


using namespace std;




template <typename V, typename E>
map<Vertex<V>*, pair<E, vector<Vertex<V>*>>> shortestPathLengths(AdjacencyListGraph<V, E> g, Vertex<V>* src, bool weighted=true) {

    // d.get(v) is upper bound on distance from src to v
    map<Vertex<V>*, pair<E, vector<Vertex<V>*>>> d;
    // map reachable v to its d value
    map<Vertex<V>*, pair<E, vector<Vertex<V>*>>> cloud;
    // pq will have vertices as elements, with d.get(v) as key

    struct CompareVertex {
        bool operator()(pair< E, Vertex<V>*> const& v1, pair< E, Vertex<V>*> const& v2) {
            return v1.first > v2.first;
        }
    };

    priority_queue <pair< E, Vertex<V>*>, vector<pair< E, Vertex<V>*>>, CompareVertex> pq;
    // maps from vertex to its pq locator
    map<Vertex<V>*, pair<E, Vertex<V>*>> pqTokens;

    // for each vertex v of the graph, add an entry to the priority queue, with
    // the source having distance 0 and all others having infinite distance
    for (Vertex<V>* v : g.getVertices()) {
        if (v == src)
            d[v] = make_pair(0, vector<Vertex<V>*>());

        else
            d[v] = make_pair(INT8_MAX, vector<Vertex<V>*>()); ;

        pq.push(pair< E, Vertex<V>*>(d[v].first, v));       // save entry for future updates
        pqTokens[v] = pair<E, Vertex<V>*>(d[pq.top().second].first, pq.top().second);
    }
    // now begin adding reachable vertices to the cloud
    while (!pq.empty()) {
        pair<pair<E, vector<Vertex<V>*>>, Vertex<V>*> entry(d[pq.top().second], pq.top().second);
        pq.pop();
        pair<E, vector<Vertex<V>*>> key = entry.first;
        Vertex<V>* u = entry.second;
        cloud[u] = key;                             // this is actual distance to u
        pqTokens.erase(u);                            // u is no longer in pq

        for (Edge<E>* e : g.outgoingEdges(u)) {
            Vertex<V>* v = g.opposite(u, e);
            if (cloud.find(v) == cloud.end()) {
                // perform relaxation step on edge (u,v)
                E wgt = (weighted ? e->getElement() : 1);
                if (d[u].first + wgt < d[v].first) {              // better path to v?
                    // update the distance
                    d[v].first = d[u].first + wgt;

                    //updating the direction vector for the current vertex
                    d[v].second = d[u].second;
                    d[v].second.push_back(u);

                    //updating the key for vertex v
                    vector< pair<E, Vertex<V>*>> dq;
                    while (!pq.empty() && pq.top().second != v) {
                        dq.push_back(pq.top()); pq.pop();
                    }
                    pair<E, Vertex<V>*> nV = pq.top(); pq.pop();
                    nV.first = d[v].first; pq.push(nV);
                    for (int i = 0; i < dq.size(); i++)
                        pq.push(dq[i]);
                }
            }
        }
    }

    //adding the last vertex in the each direction vector in the cloud map
    for (const auto& p : cloud) {
        cloud[p.first].second.push_back(p.first);

        if (!weighted) {
            cloud[p.first].first = 0;
            for (int i = 0; i < p.second.second.size() - 1; i++)
                cloud[p.first].first += g.getEdge(p.second.second[i], p.second.second[i + 1])->getElement();
        }

    }

    return cloud;
}