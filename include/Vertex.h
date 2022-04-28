#ifndef VERTEX_H
#define VERTEX_H

#include "Edge.h"

#include <iostream>
#include <vector>

#define VECTOR std::vector
#define COUT std::cout
#define ENDL std::endl

template<class T>
class Vertex{

	private:
	
		VECTOR< Edge > edges;
		T data;
		bool valid;			// Valid Vertex
		
	public:
	
		Vertex( ) : edges(), data( ), valid( true ) {}
	
		Vertex( const T& dataIn ) : edges(), data( dataIn ), valid( true ) {}
		
		~Vertex(){ }
		
		bool get_valid(){

			return valid;
		}
	
		void set_valid(bool val){

			this->valid = val;
		}

		T get_vertex_value() const{
			
			return data;
		}

		void set_vertex_value(const T& dataIn){
			
			data = dataIn;
		}
		
		// Adding an Edge to a Vertex
		void add_edge( unsigned int destin, int weight ){
			
			// If not, put the edge on the back of the array
			edges.push_back( Edge(destin, weight) );
			
		}
		
		// Pass the destination, return weight with call be reference, bool if found
		bool get_edge_value( unsigned int destin, int& weight ) const{
			
			bool edgeFound = false;
			
			for( unsigned int i = 0; i < edges.size(); i++){
				if( edges[i].destin == destin ){

					edgeFound = true;
					weight = edges[i].weight;
				}					
			}
			
			return edgeFound;
		}


		

		// Pass the destination and weight, bool if found		
		bool set_edge_value( unsigned int destin, int weight) {
			
			bool edgeFound = false;
			
			for( unsigned int i = 0; i < edges.size(); i++){
				if( edges[i].destin == destin ){

					edgeFound = true;
					edges[i].weight = weight;
				}
			}
			
			return edgeFound;
		}
		
		// Remove the edge to an input destination
		void remove_edge( unsigned int edgeLoc ){
			
			for(unsigned int i = 0; i < edges.size(); i++){
				
				if( edges[i].destin == edgeLoc ){
					edges.erase( edges.begin() + i);
				   break;
				}
			}
	
		}
		
		// Return an edge
		Edge get_edge( unsigned int edgeOrder ) {
			
			return edges[ edgeOrder ];
		}
		
		// Return the number of edges
		unsigned int num_edges() const{
			
			return (unsigned int)edges.size();
		}
		
		// Clear the vertex 
		void lazy_delete(){
			
			valid = false;
			
			while( edges.size() > 0 ){
				
				// Remove the front edge
				edges.erase( edges.begin() );
			}
			
		}
		
		// Print to the Output
		void print_vertex(){

			// If the vertex is valid
			if( this->valid ){
			
				// Print the data element first
				COUT << "[" << this->data.name << ": "; //added .name
				
				// 
				for( long unsigned int iter = 0; iter < this->edges.size(); iter++ ){
					
					// Print the destination
					COUT << "{" << this->edges[iter].destin << ", ";
					
					// Print the weight
					COUT << this->edges[iter].weight << "} ";
					
				}
				COUT << "]";
			
			}
			// If the vertex is not valid, indicate Lazy Deletion
			else{
				COUT << "[DELETED]";
			}		
			
		}

		//NEW METHOD//
		//will return index of edge with min weight//
		int min_weight() {
			
			int index = -1;
			int min = 1000000000;

			for (unsigned int i = 0; i < edges.size(); i++) {
				if (edges[i].weight < min) {
					min = edges[i].weight;
					index = i;
				}
			}
		
			return edges[index].destin;
		}

		//NEW METHOD- GRACE//
		std::string get_name() {

			return this->data.name;
		
		}

		
};

#endif
