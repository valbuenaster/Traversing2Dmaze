#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "Map.h"
#include "Tree.h"
#include "Graph.h"
#include "A_Star.h"

using namespace std;


int main()
{
	shared_ptr<Map> Mapa = nullptr;
	shared_ptr<Map> Mapa2 = nullptr;
	shared_ptr<Map> Mapa3 = nullptr;
	shared_ptr<Map> MapaAS = nullptr;
	shared_ptr<Map> MapaDisplay = nullptr;

	long long int N = 0;
	long long int M = 0;
	long long int Ix = 0;
	long long int Iy = 0;
	string Str;

	shared_ptr<Tree> Arbol;
	shared_ptr<Graph> Grafo;
	shared_ptr<A_Star> Algorithm;

	cout <<"Hello, please write the map's dimensions"<<endl;
	cin >> N>>M;

	Mapa = make_shared<Map>(N,M);
	Mapa2 = make_shared<Map>(N,M);
	Mapa3 = make_shared<Map>(N,M);
	MapaAS = make_shared<Map>(N,M);
	MapaDisplay = make_shared<Map>(N,M);

	cout <<"The map is "<< N<<" by "<< M<<endl;
	cout <<"Enter the map"<<endl;

	for(long long int mm = 0;mm<M;mm++)
	{
		cin >> Str;
		Mapa->addLine(Str,mm,N);
		Mapa2->addLine(Str,mm,N);
		Mapa3->addLine(Str,mm,N);
		MapaAS->addLine(Str,mm,N);
		MapaDisplay->addLine(Str,mm,N);
	}

	cout<<"Now set up the initial condition."<<endl;
	cin >> Ix >> Iy;

	Mapa->writeoverMap(Ix,Iy,INITIAL_P);
	Mapa2->writeoverMap(Ix,Iy,INITIAL_P);
	Mapa3->writeoverMap(Ix,Iy,INITIAL_P);
	MapaAS->writeoverMap(Ix,Iy,INITIAL_P);
	MapaDisplay->writeoverMap(Ix,Iy,INITIAL_P);

	cout<<"\nPrinting the map back"<<endl<<endl;
	Mapa->printMap();

	Arbol = make_shared<Tree>(Ix,Iy);
	Grafo = make_shared<Graph>(Ix,Iy);

	cout<<endl<<"Exploring the map with a tree in DEPTH approach..."<<endl;
	shared_ptr<Node> Destination = Arbol->exploreMapbyDepth(Mapa,Arbol->Root);
	cout<<"Done exploring."<<endl;

	cout<<endl<<"Exploring the map with a tree in BREADTH approach..."<<endl;
	shared_ptr<Node> Destination2 = Arbol->exploreMapbyBreadth(Mapa2,Arbol->Root);
	cout<<"Done exploring."<<endl;

	Mapa2->cleanVisits();

	shared_ptr<NodeG> DestinationB = Grafo->growGraph(Mapa3);

	shared_ptr<NodeG> TheRoot = Grafo->returnStartPoint();


	//cout<<"Printing third map"<<endl;
	//Mapa3->printMap();
	//cout<<endl;


	Grafo->assignLevel(MapaDisplay);

	list<shared_ptr<NodeG>> bestPath;
	Grafo->findPath(bestPath,DestinationB);


	for(auto elem:bestPath)
	{
		if(elem==nullptr)
		{
			//cout<<"nulo."<<endl;
		}else
		{
			//cout<<"("<< Ix + elem->px <<","<< Iy +elem->py << "), Level = "<< elem->Level <<", cummDist = "<<elem->cummulativeDistance<<endl;
			Mapa3->writeoverMap(Ix + elem->px, Iy +elem->py,PATH);
		}
	}

	cout<<"\nPrinting Optimal trajectory using a Graph"<<endl;
	Mapa3->printMap();
	cout<<"Position Goal ("<< DestinationB->px<<","<< DestinationB->py<<")"<<endl;
	cout<<"Cumulative value = "<<DestinationB->cummulativeDistance<<endl;


	cout<<"\nPrinting Optimal trajectory using A*"<<endl;

	Algorithm = make_shared<A_Star>(Ix,Iy,Ix + DestinationB->px,Iy + DestinationB->py);
	Algorithm->evolve(MapaAS);

	shared_ptr<NodeS> Ppointer = Algorithm->returnEndNode();
	double CCum = Ppointer->cummulativeDistance;
	if(Ppointer->Parent==nullptr) cout<<"Did not find it"<<endl;
	Ppointer = Ppointer->Parent;
	while(Ppointer->Parent!=nullptr)
	{
		//cout<<"("<< Ppointer->px <<","<< Ppointer->py <<")->";
		MapaAS->writeoverMap(Ppointer->px, Ppointer->py,PATH);
		Ppointer = Ppointer->Parent;
	}
	//cout<<"("<< Ppointer->px <<","<< Ppointer->py <<")"<<endl;
	MapaAS->printMap();
	cout<<"Cumulative value = "<<CCum<<endl;

}
