/*
 * A_Star.h
 *
 *  Created on: Nov 4, 2020
 *      Author: luis
 */

#ifndef SOURCE_A_STAR_H_
#define SOURCE_A_STAR_H_

#include <vector>
#include <map>
#include <list>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <bits/stdc++.h>
#include <memory>

#include "Map.h"

using namespace std;

#define N_CONN_S 8
#define N_CONN_S_2 4

const long long int DeltaXS[] = {0, 1, 1, 1, 0, -1, -1, -1};
const long long int DeltaYS[] = {1, 1, 0, -1, -1, -1, 0, 1};

const double DifferentialCost[] = {1.00, 1.41, 1.00, 1.41, 1.00, 1.41, 1.00, 1.41};

struct NdS{
	long long int px=0;
	long long int py=0;

	bool visited = false;

	bool flagA = false;
	bool flagB = false;
	bool flagC = false;

	double cummulativeDistance = DBL_MAX;

	long long int Level = LLONG_MAX;
	std::shared_ptr<struct NdS> Parent = nullptr;

	vector<char> stateNeighbors;
	vector< std::shared_ptr<struct NdS> >Connections;
}typedef NodeS;

class A_Star
{
	std::shared_ptr<NodeS> StartNode;
	std::shared_ptr<NodeS> EndNode;

	map<long long int,vector<long long int>> mapWHERE2MOVE;
	map<long long int,vector<long long int>> mapWHAT2MOVE;
	map<long long int,vector<long long int>> mapConnInsOrder;

public:
	A_Star(long long int Sx,
	       long long int Sy,
		   long long int Ex,
		   long long int Ey);
	bool evolve(std::shared_ptr<Map> M);
	int exploreNeighbors(std::shared_ptr<Map> M,
			             std::shared_ptr<NodeS> ptr,
						 long long int Vx,
						 long long int Vy);
	std::shared_ptr<NodeS> createNode(std::shared_ptr<NodeS> ptrParent,
			                          int index);
	void createConnections(std::shared_ptr<NodeS> ptr,
			               int index);
	std::shared_ptr<NodeS> returnEndNode();

	~A_Star();
};


#endif /* SOURCE_A_STAR_H_ */
