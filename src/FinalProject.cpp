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
				
				std::string curr_edge;
				unsigned int i, j;	
				
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
						if (iter%2 == 0) {
							destins.push_back((unsigned int) std::stoi(curr_edge));
						} else {
							weights.push_back((unsigned int) std::stoi(curr_edge));
						}
						
						iter++;
					}	 	
					
					//INSERT THE EDGES 
					for(j=0; j < destins.size(); j++){
			  			bars_graph.add_edge(i, destins[j], weights[j]);
				 	}
				}
				
				break;
			} 	 	 	 	 		  	 	 	 	 		  		  		  		  		  		  		  														  		  		  				

	 					
			//print graph//
			case 2: {
				bars_graph.print_graph();
				break;
			}

			case 3: {
				Bar the_bar;
				add_bar(bars_graph, the_bar);
				break;
			}
			
			//optimal bar crawl//
			case 4: {
				Graph <Bar> graph_copy = copy_graph(bars_graph);
				generate_crawl(bar_names, graph_copy);
				break;	
			}

			case 5: {

				Graph<Bar> graph_copy = copy_graph(bars_graph);
			
				int prune_select = 0;

				COUT << "Select 1 to prune by price" << ENDL;
				COUT << "Select 2 to prune by rating" << ENDL;
				CIN >> prune_select;
				
				if (prune_select == 1) {
					unsigned int price;
					COUT << "Enter which price tier bars have to be below (2 ($$) or 3 ($$$))" << ENDL;
					CIN >> price;
					if (price != 2 && price != 3) {
						COUT << "Invalid price tier selection" << ENDL;
						return -1;
					}
					prune_by_price(graph_copy, price);
				} else if (prune_select == 2) {
					unsigned int rating;
					COUT << "Enter which rating tier bars have to be above (1 - 5 stars)" << ENDL;
					CIN >> rating;
					if (rating > 5 && rating < 1) {
						COUT << "Invalid rating tier selection" << ENDL;
						return -1;
					}
					prune_by_price(graph_copy, rating);
				} else {
					COUT << "Invalid selection" << ENDL;
				}
				
				COUT << "Updated graph" << ENDL;
				graph_copy.print_graph();

				//save changes//
				int save = 0;
				COUT << "Select 1 to save changes, or 0 to discard changes" << ENDL;
			    CIN >> save;	
				if (save == 1) {
					bars_graph = copy_graph(graph_copy);
				}

				break;
			}

		}
	}

	 return 0;
}



	 





