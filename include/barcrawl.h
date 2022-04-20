/****************************************************************
 * Author: Ava DeCroix, Grace Bezold, Mia Patel, Claire DeMeo
 * (some code provided by Matthew Morrison)
 * Date: 4/15/22
 * File name: barcrawl.h
 * File contents: header file for our final project
 * *************************************************************/

//Include libraires

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>

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

		  //Method to print a bar's info
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


//Function declarations:
void add_bar(Graph<Bar>& bar_graph, Bar& new_bar);

