#ifndef NETWORK_H
#define NETWORK_H

#include <istream>
#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>


#include "switch.h"


/**
 * A network of switches with lossy connections.
 */
class Network {
	typedef boost::adjacency_list<boost::listS,       // store edges in lists
                                  boost::vecS,        // store vertices in a vector
                                  boost::directedS, // an undirected graph
                                  Switch,                // vertex data (Switch)
                                  double                // edge data (loss)
                                  >
        Graph;
    typedef boost::graph_traits<Graph> GraphTraits;
    typedef GraphTraits::edge_descriptor Edge;

	Graph network; // each vertex in this graph represents one switch.

public:
	/**
	 * Read a network description from an input stream.
	 */
	void read (std::istream& in);


	/**
	 * Compute the signal strength at the output of the final
	 * switch in the network if a signal of strength 1.0 is presented
	 * at all inputs of the first switch in the network.
	 */
	double findSignalStrength() const;

};



#endif
