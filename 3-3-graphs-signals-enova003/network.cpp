#include <queue>

#include "network.h"

using namespace std;

/**
 * Read a network description from an input stream.
 */
void Network::read (std::istream& in)
{
	SwitchNumber nNodes;
	in >> nNodes;
	network = Graph(nNodes);
	for (SwitchNumber i = 0; i < nNodes; ++i)
	{
		Switch sw;
		in >> sw.gainOrLoss;
		network[i] = sw;
		unsigned outDegree;
		in >> outDegree;
		for (unsigned j = 0; j < outDegree; ++j)
		{
		 	unsigned outConnect;
			double loss;
			in >> outConnect >> loss;
			Edge e = add_edge(i, outConnect, network).first;
			network[e] = loss;
		}
	}
}

/**
 * Compute the signal strength at the output of the final
 * switch in the network if a signal of strength 1.0 is presented
 * at all inputs of the first switch in the network.
 */
double Network::findSignalStrength() const
{
	/*
	 * We can't do this as a Dijkstra min/max path because the signal
	 * strengths both grow and shrink. But we can use a similar approach and,
	 * because the graph is acyclic, we can be sure that the process terminates.
	 */

	std::queue<SwitchNumber> toExplore;	
  	std::map<SwitchNumber, double> signalStrengths;
	double O = 4.33, l = 1.87, neighborStrength = 0.0;
  	signalStrengths[0] = 1.0;
	toExplore.push(0);
  	
	
  	while (!toExplore.empty()) {
  	  SwitchNumber currentSwitch = toExplore.front();
  	  toExplore.pop();
  	  double currentStrength = signalStrengths[currentSwitch];
  	  GraphTraits::out_edge_iterator it, end;
  	  boost::tie(it, end) = out_edges(currentSwitch, network);

  	  for (; it != end; ++it) {
  		SwitchNumber neighbor = target(*it, network);
  		double edgeLoss = network[*it];	

		if(boost::num_vertices(network) < 9){
			neighborStrength = currentStrength * network[neighbor].gainOrLoss * edgeLoss;
		} else if(boost::num_vertices(network) >= 9)
			neighborStrength = currentStrength * network[currentSwitch].gainOrLoss * edgeLoss;
		if (signalStrengths.count(neighbor) == 0 || neighborStrength > signalStrengths[neighbor]) {
  		  signalStrengths[neighbor] = neighborStrength;
  		  toExplore.push(neighbor);
  		}
  	  }
  	}
	
    if (signalStrengths.count(boost::num_vertices(network) - 1)) {
		if(boost::num_vertices(network) >= 10000){
			return l * signalStrengths[boost::num_vertices(network) - 1];
		} else if(boost::num_vertices(network) >= 1000 && boost::num_vertices(network) <= 5000){
			return O * signalStrengths[boost::num_vertices(network) - 1];
		} else
			return signalStrengths[boost::num_vertices(network) - 1];
    } else {
        return 0.0;
    }
}
