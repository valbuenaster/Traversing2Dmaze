/*
 * Tree.h
 *
 *  Created on: Oct 9, 2020
 *      Author: luis
 */

#ifndef SOURCE_TREE_H_
#define SOURCE_TREE_H_

#include <vector>
#include <list>
#include <math.h>
#include <memory>
#include "Map.h"

//const long long int DeltaX[] = {0, 1, 1, 1, 0, -1, -1, -1};
//const long long int DeltaY[] = {1, 1, 0, -1, -1, -1, 0, 1};

//const long long int DeltaX[] = {1, 1, -1, -1, 0, 1, 0, -1};
//const long long int DeltaY[] = {1, -1, -1, 1, 1, 0, -1, 0};

const long long int DeltaX[] = {-1, 1, 0, 0, 1, -1, 1, -1};
const long long int DeltaY[] = {0, 0, 1, -1, 1, -1, -1, 1,};

const long long int DeltaXBA[] = {0, 1, 1, 1, 0, -1, -1, -1};
const long long int DeltaYBA[] = {1, 1, 0, -1, -1, -1, 0, 1};

struct Nd{
	long long int px=0;
	long long int py=0;
	long long int Level = 0;

	bool visited = false;
	bool flagA = false;
	bool flagB = false;
	bool flagC = false;

	double cummulativeDistance = 0.0;

	std::shared_ptr<struct Nd> Parent = nullptr;
	std::vector<std::shared_ptr<struct Nd>> Connections;
}typedef Node;

class Tree
{
	long long int initPosx=0;
	long long int initPosy=0;

	std::list< std::shared_ptr<Node> > setofRoads;

	const int Nconst = 8;
public:
	std::shared_ptr<Node> Root;
	Tree(long long int Ipx,
	     long long int Ipy);
	std::shared_ptr<Node> createNode(std::shared_ptr<Node> Pointer,
			                         long long int Ipx,
									 long long int Ipy);
	std::shared_ptr<Node> exploreMapbyDepth(std::shared_ptr<Map> M,
			                                std::shared_ptr<Node> Pointer);//Return the node that has the destination;
	std::shared_ptr<Node> exploreMapbyBreadth(std::shared_ptr<Map> M,
			                                  std::shared_ptr<Node> Pointer);
	void printTree();

	~Tree();
};

#endif /* SOURCE_TREE_H_ */
