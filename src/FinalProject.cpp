/*****************************************************************
 * Author: Ava DeCroix, Grace Bezold, Claire DeMeo, Mia Patel
 * Email: adecroix@nd.edu
 * Date created: 4/15/22
 * File name: FinalProject.cpp
 * File contents: Main driver for implementation of the final project
 * CREDIT: Professor Morrison's Graph.h, Vertex.h, and Edge.h
 * are used in this project
 * **************************************************************/


#include "../include/barcrawl.h"


int main(const int argc, const char *argv [] ){

	 //1. Reading in the data to populate the graph
	 
	 //1(a): check for proper number of command line arguments (there should be two, the executable and the input file):
	 if (argc < 2){

		  COUT << "Error: improper number of command line arguments." << ENDL;

		  return(ERROR_EXIT);

	 }



	 //1(b): create an input stream from the file passed to the command line
	 IFSTREAM names_input;
	 IFSTREAM ratings_input;
	 IFSTREAM price_input;
	 IFSTREAM edges_input;

	 //1.b.1 : Get the file names from argv
	 const char* names_file = argv[1];
	 const char* ratings_file = argv[2];
	 const char* price_file = argv[3];
	 const char* edges_file = argv[4];

	 //1.b.2 : open the file
	 names_input.open(names_file);
	 ratings_input.open(ratings_file);
	 price_input.open(price_file);
	 edges_input.open(edges_file);


	 //1.b.3 : Check to make sure valid file
	 if(names_input == NULL || ratings_input == NULL || price_input == NULL){

		  COUT << "Invalid input file" << ENDL;
		  return -1;
	 }


	 //1.c : create a vector to hold the bars
	 VECTOR<std::string> bar_names;
	 VECTOR<unsigned int> ratings;
	 VECTOR<unsigned int> price_tiers;
	 VECTOR<std::string> edges;


	 //2. CREATE A GRAPH to hold the bars
	 Graph<Bar> bars_graph;


	 //3. Read in all of the bar data from the three files

	 //3.1: Names:
	 std::string curr_item;
	 while(std::getline(names_input, curr_item)){

				bar_names.push_back(curr_item);

	 }

	 //3.2 Ratings:
	 unsigned int temp_int;


	 while(ratings_input >> temp_int){
		  ratings.push_back(temp_int);

	 }

	 //3.3: Price:
	 while(price_input >> temp_int){
		  price_tiers.push_back(temp_int);
	 }


	 //4. Add nodes to the graph
	 for (unsigned int i = 0; i < bar_names.size(); i++){

		  //Use overloaded constructor to add a bar node with all of the correct info
		  Bar curr_bar(bar_names[i], ratings[i], price_tiers[i]);

		  //Print the bar node (this is a test, can be removed at the end)
		  curr_bar.print_Bar();

		  //Add the bar node to the graph
		  bars_graph.add_vertex(curr_bar);


		  //Print total number of bars in the graph
		  COUT << "Bars in graph: " << i+1 << ENDL;


	 }


	 //5. Print the graph (edited code in Vertex.h to print the bar's name instead of just "data", since the data is a struct)
	 bars_graph.print_graph();



	 //6. ADD EDGES:
	 std::string curr_edge;
	 unsigned int i, j;
	 //unsigned int destin, weight;

	 //6.1 : Read in the strings of edges
	 while(std::getline(edges_input, curr_edge)){
		  edges.push_back(curr_edge);
	 }


	 //6.2 : Parse the individual weights

	 //Iterate through the list of vertices
	 for(i=0; i < edges.size(); i++){

		  VECTOR<unsigned int> destins;
		  VECTOR<unsigned int> weights;
		  
		  std::stringstream list(edges[i]);
		  int iter=0;

		  //PARSE EACH LINE OF INPUT FOR THE WEIGHTS AND DESTINATIONS
		  while(std::getline(list, curr_edge, ',')){

				if ((iter%2 == 0)) destins.push_back((unsigned int) std::stoi(curr_edge));

				else weights.push_back((unsigned int) std::stoi(curr_edge));

				iter++;

		  }


		  //INSERT THE EDGES
		  for(j=0; j < destins.size(); j++){

				bars_graph.add_edge(i, destins[j], weights[j]);
		  }
	 }



	 //7: Print the graph after adding the edges
	 COUT << "With edges added: " << ENDL;
	 bars_graph.print_graph();


	 //8. TEST: add bar
	 //Bar new_bar;
	 //add_bar(bars_graph, new_bar);
	 //COUT << "New bar added, printing updated graph...." << ENDL;
	 //bars_graph.print_graph();

	 //9. TEST: prune by price tier
	 //COUT << "Pruning all bars above price tier 2...." << ENDL;
	 //unsigned int max_price_tier = 2;
	 //prune_by_price(bars_graph, max_price_tier);
	 //COUT << "Updated graph: " << ENDL;
	 //bars_graph.print_graph();


	 //10. TEST: prune by rating
	 //COUT << "Pruning all bars below rating 4..." << ENDL;
	 //unsigned int min_rating = 4;
	 //prune_by_rating(bars_graph, min_rating);

	 //COUT << "Updated graph: " << ENDL;
	 //bars_graph.print_graph();






	 return 0;

}



	 





