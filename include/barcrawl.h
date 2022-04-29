/****************************************************************
 * Author: Ava DeCroix, Grace Bezold, Mia Patel, Claire DeMeo
 * (some code provided by Matthew Morrison)
 * Date: 4/15/22
 * File name: barcrawl.h
 * File contents: header file for our final project
 * *************************************************************/

//Include libraries

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<string.h>
#include<sstream>



//.h files provided by Dr. Morrison in PC07
#include "../include/Edge.h"
#include "../include/Graph.h"
#include "../include/MSTElem.h"
#include "../include/Vertex.h"

//Define for easier coding
#define COUT std::cout
#define CIN std::cin
#define ENDL std::endl
#define VECTOR std::vector
#define IFSTREAM std::ifstream
#define OFSTREAM std::ofstream
#define ERROR_EXIT -1

//DEFINE bar node struct:
struct Bar{

	 public:
		  std::string name;
		  unsigned int rating;
		  unsigned int price_tier;

	
	//Default constructor
	Bar() : name(), rating(0), price_tier(0) {}

		  //Overloaded constructor:
		  Bar(const std::string& name_in, const unsigned int& rating_in, const unsigned int& price_tier_in):
				name(name_in), rating(rating_in), price_tier(price_tier_in) {}

		  void print_Bar(){
				COUT << "---------------------------------" << ENDL;
				COUT << "Name: " << this->name << ENDL;
				COUT << "Rating: " << this->rating << ENDL;
				COUT << "Price tier " << this->price_tier << ENDL;
				COUT << "---------------------------------" << ENDL;

		  }


};


//Typedef so that we can just reference Bar
typedef struct Bar Bar;

//function declarations//
void generate_crawl(VECTOR<std::string> bar_names, Graph<Bar> &bars_graph);
void add_bar(Graph<Bar> &bar_graph, Bar& new_bar);
void prune_by_price(Graph<Bar> &bar_graph, unsigned int& price_tier);
void prune_by_rating(Graph<Bar> &bar_graph, unsigned int& rating);
Graph<Bar> copy_graph(Graph<Bar> &bars_graph);
