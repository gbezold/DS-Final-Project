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
	

	 //6.2 : Parse the individual weights

	 //Iterate through the list of vertices
	 for(i=0; i < 1; i++){

		  VECTOR<unsigned int> destins;
		  VECTOR<unsigned int> weights;
		  
		  std::stringstream list(edges);
		  int iter=0;

		  //PARSE EACH LINE OF INPUT FOR THE WEIGHTS AND DESTINATIONS
		  while(std::getline(list, curr_edge, ',')){

				if ((iter%2 == 0)) destins.push_back((unsigned int) std::stoi(curr_edge));

				else weights.push_back((unsigned int) std::stoi(curr_edge));

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










