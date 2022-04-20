/**************************************************************
 * Authors: Ava DeCroix, Grace Bezold, Claire DeMeo, Mia Patel
 * Emails: adecroix@nd.edu, gbezold@nd.edu, cdemeo@nd.edu, rpatel7@nd.edu
 * Date Created: 4/16/22
 * File Name: barcrawl.cpp 
 * File Contents: This file contains the functions for FinalProject.cpp
 * CREDIT: Graph.h, Vertex.h, Edge.h, MSTElem.h are all provided by Dr. Morrision
 * **********************************************************/

#include "../include/barcrawl.h"

void dijkstras_search(VECTOR<std::string> bar_names, Graph<Bar> &bars_graph) {
	
	char name_start[BUFSIZ];
	int to_visit = 0;

	COUT << "Enter name of bar to start at: ";
	CIN >> name_start;

	COUT << "Enter the number of bars to visit: ";
	CIN >> to_visit;
	
	//convert name_start to an int//
	int start = -1;
	
	//set up to convert std::string to char * for strcmp//

	for (unsigned int i = 0; i < bar_names.size(); i++) {
		//set up to convert std::string to char * for strcmp//
		long unsigned int len = bar_names[i].size();

		char* c = new char[len + 1];
		std::copy(bar_names[i].begin(), bar_names[i].end(), c);
	
		if (!strcmp(name_start, c)) start = i;
		
		delete[] c;

	}

	if (start < 0) {
		COUT << "invalid start name" << ENDL;
		return;
	}

	//prune edges to hit user inputted amount of bars
	int end = bars_graph.prune_distance(to_visit, start);

	bars_graph.Dijkstra(start, end);

}
