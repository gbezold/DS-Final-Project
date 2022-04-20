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

	//check for proper number of command line arguments (there should be two, the executable and the input file):
	if (argc < 2){
		COUT << "Error: improper number of command line arguments." << ENDL;
		return(ERROR_EXIT);
	}
	
	//create a vector to hold the bars
	VECTOR<std::string> bar_names;
	VECTOR<unsigned int> ratings;
	VECTOR<unsigned int> price_tiers;
	VECTOR<std::string> edges;


	//CREATE A GRAPH to hold the bars
	Graph<Bar> bars_graph;
	int selection = -1; 

	while (selection != 0) {

		//print menu selection for users//
		COUT << "Menu: " << ENDL;
		COUT << "1. Load default South Bend bar data" << ENDL;
		COUT << "2. Print Graph" << ENDL;
		COUT << "3. Input another bar" << ENDL;
		COUT << "4. Generate optimal bar crawl" << ENDL;
		COUT << "5. Prune Bars by factor" << ENDL;
		COUT << "0. Quit" << ENDL;
		
		COUT << "Selection: ";	
		CIN >> selection;
	
		switch(selection) {
		
			//read in default data//
			case 1: {
	 			//create an input stream from the file passed to the command line
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


	 			//6. ADD EDGES:
	 			std::string curr_edges;
	 			unsigned int i, j;
	 			unsigned int destin, weight;

	 			//6.1 : Read in the strings of edges 
	 			while (edges_input >> curr_edges){

		  			edges.push_back(curr_edges);

	 			}
		
	 			//Insert each edge (format: j = destin, j+1 = weight)
	 
	 			//Iterate through the list of edges for each vertex
	 			for (i=0; i < edges.size(); i++){

		  			for(j=0; j < edges[i].size(); j+=2){

						//Get the destination
						destin = edges[i][j] - '0';

						//Get the weight
						weight = edges[i][j+1] - '0';

						//Add edge from origin to destin of weight weight
						bars_graph.add_edge(i, destin, weight);


		  			}
	 			}
			
				break;
			}
		
			//print graph//
			case 2: {
				bars_graph.print_graph();
				break;
			}

			case 4: {
				dijkstras_search(bar_names, bars_graph);	
			}

		}
	}

	 return 0;
}



	 





