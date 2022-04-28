/**************************************************************
 * Authors: Ava DeCroix, Grace Bezold, Claire DeMeo, Mia Patel
 * Emails: adecroix@nd.edu, gbezold@nd.edu, cdemeo@nd.edu, rpatel7@nd.edu
 * Date Created: 4/16/22
 * File Name: barcrawl.cpp 
 * File Contents: This file contains the functions for FinalProject.cpp
 * CREDIT: Graph.h, Vertex.h, Edge.h, MSTElem.h are all provided by Dr. Morrision
 * **********************************************************/

#include "../include/barcrawl.h"

void generate_crawl(VECTOR<std::string> bar_names, Graph<Bar> &bars_graph) {
	
	char name_start[BUFSIZ];
	unsigned int to_visit = 0;

	COUT << "Enter name of bar to start at: ";
	CIN >> name_start;

	COUT << "Enter the number of bars to visit: ";
	CIN >> to_visit;

	if (to_visit > bar_names.size()) {
		COUT << "requested to visit too many bars" << ENDL;
		return;
	} else if (to_visit < 2) {
		COUT << "requested to visit too few bars" << ENDL;
		return;
	}
	
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
	//traverse graph//
	bars_graph.Dijkstra(start, end);

}

void add_bar(Graph<Bar>& bar_graph, Bar& new_bar){

	//Note: requires you to have created a new Bar node in main to pass in
	
	//Create variables to hold name/edges and unsigned ints to hold data
	std::string name;
	unsigned int rating;
	unsigned int price_tier;
	std::string edges;

	//Prompt the user for input:	 	 
	//Name:
	fprintf(stdout, "Please enter a bar name (use underscores instead of spaces for more than one word):\n");
	CIN >> name;

	//Rating:
	fprintf(stdout, "Please enter a rating: \n");
	CIN >> rating;
		 
	//Price tier:
	fprintf(stdout, "Please enter a price tier (1 = least expensive, 2 = medium expensive, 3 = very expensive):\n");
	CIN >> price_tier;
		  	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 
	//Edges:
	fprintf(stdout, "Please enter a list of comma-separated edges (ex. 1,2,3,2,4,1,5,2,6,3) where each odd digit is the destination vertex and each subsequent digit is the distance to that vertex (from the example, the first edge goes to vertex 1, and is 2 miles away):\n");
	CIN >> edges;
		 
	//Fill in the info for the bar struct
	const char *new_bar_name = name.c_str();

	new_bar.name = strdup(new_bar_name);
		
	new_bar.rating = rating;
	new_bar.price_tier = price_tier;
		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 
	//Add the struct to the graph
	bar_graph.add_vertex(new_bar);

	//Get the index of the newly inserted node (will be used as origin when inserting vertices)
	unsigned int origin = bar_graph.locate_data(new_bar);

	 //ADD EDGES:
	 std::string curr_edge;
	 unsigned int i, j;	 	
	 //Parse the individual weights
	 //Iterate through the list of vertices
	 for(i=0; i < 1; i++){
	 
	 	VECTOR<unsigned int> destins;
	    VECTOR<unsigned int> weights;
		 	 		 	 	 		  		  		  
	 	std::stringstream list(edges);
	 	int iter=0;
	
		//PARSE EACH LINE OF INPUT FOR THE WEIGHTS AND DESTINATIONS
	 	while(std::getline(list, curr_edge, ',')){
	 
			if ((iter%2 == 0)) {
				if ((unsigned int)std::stoi(curr_edge) > bar_graph.num_vertices()) {
					COUT << "invalid destination input" << ENDL;
					return;
				}
				destins.push_back((unsigned int) std::stoi(curr_edge));
			} else {
				weights.push_back((unsigned int) std::stoi(curr_edge));
			}
	
		 	iter++;
	 	}
	 	//INSERT THE EDGES
	 	for(j=0; j < destins.size(); j++){
	
	 		bar_graph.add_edge(origin, destins[j], weights[j]);	 
	 	}
	  }

}

//prune_by_price function prunes the tree to only bars above or below a certain price tier
void prune_by_price(Graph<Bar>& bar_graph, unsigned int& price_tier){

	unsigned int i;
	unsigned int num_vertex = (unsigned int) bar_graph.num_vertices();


	//Cycle through all the vertices
	for (i=0; i < num_vertex; i++){

	//If the current vertex (Bar node) has a price tier greater than the one specified, remove it
		if((bar_graph.get_vertex_value(i)).price_tier > price_tier){
			bar_graph.remove_vertex(i);
		}
	}

}

void prune_by_rating(Graph<Bar>& bar_graph, unsigned int& rating){

	unsigned int i;
	unsigned int num_vertex = (unsigned int) bar_graph.num_vertices();

	//Cycle through all the vertices
	for(i=0; i < num_vertex; i++){
		//If the current vertex (Bar node) had a rating less than the one specified, remove it
		if((bar_graph.get_vertex_value(i)).rating < rating){
			bar_graph.remove_vertex(i);
		}
	}
}


//Copy graph function returns a copy of the current graph//
Graph <Bar> copy_graph(Graph<Bar>&bars_graph){
	
		 //Make copy graph
		 Graph<Bar> copy_graph;
		 unsigned int iter;
		 
		 //Read in all of the bar data from the original graph
		 for(iter=0; iter < bars_graph.num_vertices(); iter++){
		 
		 	Bar newBar = bars_graph.get_vertex_value(iter);
		 	copy_graph.add_vertex(newBar);
			copy_graph.vertices[iter].set_valid(bars_graph.vertices[iter].get_valid());

		 
		 }
		 
		 //Copy edges
		 VECTOR< Vertex<Bar> > original_vertices = bars_graph.get_vertices();
		 
		 unsigned int ii, jj;
		 
		 for(ii=0; ii<bars_graph.num_vertices(); ii++){
		 
		 	Vertex<Bar> curr_vertex = original_vertices[ii];

		 
		 	for(jj=0; jj<original_vertices[ii].num_edges(); jj++){
		 
		 		Edge copy_edge = bars_graph.vertices[ii].get_edge(jj);
		  		int copy_weight = copy_edge.weight;
 	 	 	 	unsigned int copy_destin = copy_edge.destin;
				copy_graph.add_edge(ii, copy_destin, copy_weight);
		 	}

		 }
		 //Return the copy
		 return copy_graph;	
}	 
