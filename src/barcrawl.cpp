/***************************************************************
 * Authors: Ava DeCroix, Claire DeMeo, Grace Bezold, Mia Patel
 * Date: 4/11/22
 * File name: barcrawl.cpp
 * Contents: Functions file for Final DS Project
 *************************************************************/

#include "../include/barcrawl.h"
#include <string.h>


//Add bar function: adds a new bar node to the graph
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
	 fprintf(stdout, "Please enter a list of edges (ex. 1232415263) where each odd digit is the destination vertex and each subsequent digit is the distance to that vertex (from the example, the first edge goes to vertex 1, and is 2 miles away):\n");
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


	 //Add the edges:
	 unsigned int i;
	 unsigned int weight;
	 unsigned int destin;

	 for(i=0; i < edges.size(); i+=2){

		  //Get the destination
		  destin = edges[i] - '0';

		  //Get the weight
		  weight = edges[i+1] - '0';


		  //Add edge from origin to destin of weight weight
		  bar_graph.add_edge(origin, destin, weight);

	 }


}











