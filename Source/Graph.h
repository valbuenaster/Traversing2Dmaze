/*
 * Graph.h
 *
 *  Created on: Oct 10, 2020
 *      Author: luis
 */

#ifndef SOURCE_GRAPH_H_
#define SOURCE_GRAPH_H_

#include <vector>
#include <map>
#include <list>
#include <limits.h>
#include <float.h>
#include <memory>

#include "Map.h"

#define N_CONN 8

const long long int DeltaXG[] = {0, 1, 1, 1, 0, -1, -1, -1};
const long long int DeltaYG[] = {1, 1, 0, -1, -1, -1, 0, 1};
const double DistanceGain[] = {1.00, 1.41, 1.00, 1.41, 1.00, 1.41, 1.00, 1.41};
const char levelChar[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		                  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
						  'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
						  'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
						  'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
						  'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
						  'Y', 'Z'};


struct NdG{
	long long int px=0;
	long long int py=0;

	int NodeType = 0;
	//Vector pointing to start point;
	double vx = 0.0;
	double vy = 0.0;

	bool visited = false;

	bool flagA = false;
	bool flagB = false;
	bool flagC = false;

	double cummulativeDistance = DBL_MAX;

	long long int Level = LLONG_MAX;
	std::shared_ptr<struct NdG> Parent = nullptr;
	std::vector< std::shared_ptr<struct NdG> >Connections;
}typedef NodeG;

class Graph
{
	long long int initPosx = 0;
	long long int initPosy = 0;

	std::shared_ptr<NodeG> StartPoint;

	std::shared_ptr<NodeG> HeadList;
	std::shared_ptr<NodeG> DestinationNode;

	std::map<long long int,std::vector<long long int>> mapNodesGraph;
	std::map<long long int,std::vector<long long int>> mapPositionsGraph;
	std::map<long long int,std::vector<long long int>> mapWhattoDiscoverGraph;
	std::map<long long int,std::vector<long long int>> map_NodeCanProvideTo;
	std::map<long long int,std::vector<long long int>> mapWhattoShareGraphLeft;
	std::map<long long int,std::vector<long long int>> mapWhattoShareGraphRight;
	std::map<long long int,std::vector<long long int>> mapArrivaltoShareGraphLeft;
	std::map<long long int,std::vector<long long int>> mapArrivaltoShareGraphRight;

public:
	Graph(long long int Ipx,
		  long long int Ipy);
	std::shared_ptr<NodeG> returnStartPoint();
	std::shared_ptr<NodeG> createNode(std::shared_ptr<NodeG> Pointer,
			                          long long int Ipx,
									  long long int Ipy,
									  int type);
	std::shared_ptr<NodeG> growGraphStepOne(std::shared_ptr<Map> M,
			                                std::shared_ptr<NodeG> ptr);
	void growGraphStepTwo(std::shared_ptr<Map> M);
	std::shared_ptr<NodeG> growGraph(std::shared_ptr<Map> M);
	void growGraphStepThree(std::shared_ptr<Map> M);
	void cleanAllFlags();
	char computeConnections(std::shared_ptr<Map> M,
			                std::shared_ptr<NodeG> Tile);
	void assignLevel(std::shared_ptr<Map> M);
	double findPath(std::list< std::shared_ptr<NodeG> > &Path,
			        std::shared_ptr<NodeG> Pointer);

	~Graph();
};

#endif /* SOURCE_GRAPH_H_ */
