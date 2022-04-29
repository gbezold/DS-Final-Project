#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "MSTElem.h"
#include <stack>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string.h>

#define VECTOR std::vector
#define STACK std::stack
#define QUEUE std::queue
#define PRIORITY_QUEUE std::priority_queue
#define UNOR_MAP std::unordered_map

template< typename T >
struct Graph{
	
	private:
			
		// Private DFS method
		bool DFS( unsigned int destin, unsigned int vertVal, VECTOR<unsigned int>& parents, VECTOR<bool>& visited ){
				
			if( !visited[ vertVal ] ){
				
				// Set the visited edges to true
				visited[ vertVal ] = true;
				
				// Check each outgoing edge 
				for( unsigned int iter = 0; iter < vertices[ vertVal ].num_edges(); iter++ ){
					
					// Obtain a temporary copy of the Edge
					Edge tempEdge = vertices[ vertVal ].get_edge( iter );
					
					// If the destination has not been visited, make recursive call
					if( !visited[ tempEdge.destin ] ){
						
						// Set the destination's parent to vertVal
						parents[ tempEdge.destin ] = vertVal;
						
						// If we found the vertex, return true
						if( tempEdge.destin == destin ){
							
							return true;
						}
						
						// Otherwise, recursively call the destination vertex
						bool check = DFS( destin, tempEdge.destin, parents, visited );
						
						// Recursively return true if check is true
						if( check ){
							
							return true;
						}
					}
					
				}
			}
			
			// Otherwise, return false
			return false;
				
		}
		
				
	public:
		
		VECTOR< Vertex< T > > vertices;	// Adjacency List

		// Constructor
		Graph( ) : vertices() {}
		
		// Destructor
		~Graph( ) { }
		
		// Add a vertex prior to any edges
		void add_vertex( const T& vertexData ){
			
			Vertex<T> theVertex( vertexData );
		   vertices.push_back( theVertex );
	  }

		//NEW METHOD//
		//Return number of vertices
		long unsigned int num_vertices() {
			return vertices.size();
		}

		//Return vector of veritces//
		VECTOR< Vertex<T> > get_vertices() {
			return vertices;
		}
		
		//Locate data- return the index for a particular data value
		unsigned int locate_data(T& data) {
			
			unsigned int i;
			const char* data_name = (data.name).c_str();

			for (i = 0; i < this->vertices.size(); i++) {
				
				//convert current name to const char*//
				const char* curr_name = (this->get_vertex_value(i).name).c_str();

				if(strcmp(data_name, curr_name) == 0) return i;

			}

			return 100;
		
		}
		
		// Add Edge from Origin to Destination, with weight
		void add_edge(unsigned int origin, unsigned int destin, int weight ){
			if( origin < vertices.size() && destin < vertices.size() ){
			
				vertices[origin].add_edge( destin, weight );
		
			}
		}
		
		// Return the value with a Call by Reference
		T get_vertex_value( const unsigned int vertex){
							
				T val = vertices.at(vertex).get_vertex_value();
				return val;
		  			
		}


	   
		//NEW METHOD:
		//Checks if a particular data value is in the graph
		bool in_graph( T& value){

			 unsigned int i;
			 for (i=0; i < this->vertices.size(); i++){

				  if (this->get_vertex_value(i) == value) return true;

		    }

			 return false;
	   }
		
		// Set the value at a given vertex 
		// bool for if the vertex requested was valid
		bool set_vertex_value( const unsigned int vertex, T& value ){
						
			if( vertex < vertices.size() ){
				
				value = vertices[vertex].set_vertex_value( value );
				return true;
			}			
			return false;
		}
		
		// Return the value with a Call by Reference
		// bool for if the origin and destination requested were valid
		bool get_edge_value( const unsigned int origin, const unsigned int destin, int& weight){
				
			if( origin < vertices.size() && destin < vertices.size() ){
				
				return vertices[origin].get_edge_value( destin, weight );
			}
			
			return false;
		}
		
		// Set the value at a given origin and destination 
		// bool for if the origin and destination requested were valid
		bool set_edge_value( const unsigned int origin, const unsigned int destin, int weight){
				
			if( origin < vertices.size() && destin < vertices.size() ){
				
				return vertices[origin].set_edge_value( destin, weight );
			}
			
			return false;
		}
		
		// Remove an edge
		bool remove_edge( unsigned int origin, unsigned int destin){
				
			// If the origin and destination are valid
			if( origin < vertices.size() && destin < vertices.size() ){
				
				// From the Origin vertex, remove the destination vertex
				return vertices[origin].remove_edge( destin );
			}
			
			return false;
		}
		
		
		void remove_vertex( unsigned int vertVal ){
			
			// First, perform Lazy Deletion on the vertex 
			vertices[ vertVal ].lazy_delete();
			
			// Next, go through each vertex and remove all edges with the destination to the vertex 
			for( unsigned int iter = 0; iter < vertices.size(); iter++ ){
				
				int jter = 0;
				
				// While the increment is less than the number of edges
				while( jter < vertices[iter].num_edges() ){
					
					// If the destination of the edge is the vertex we are removing
					if( vertices[iter].get_edge( jter ).destin == vertVal ){
						
						// Remove that edge
						vertices[iter].remove_edge( vertVal );
					}
					else{
						// Only increment jter is there is not any deletion
						jter++;
					}
				}
			}
		}


	   
	 //NEW METHOD:
	 //Checks if an edge is unique
	 bool is_unique_edge( unsigned int& destin ){

		  int times_in_graph = 0;

		  for (unsigned int iter= 0; iter < vertices.size(); iter++ ){

				for(unsigned int jter = 0; jter < vertices[iter].num_edges(); jter++ ){

					 if (vertices[iter].get_edge(jter).destin == destin) times_in_graph++;

				}

		  }

		  if (times_in_graph == 1) return true;

		  else return false;

	 }

	 

	 //GRACE NEW METHOD//
	 //Prune edges based on distance//
	 int prune_distance(unsigned int num_bars, int start) {
		
		int end = -1;

		int curr_index = start;
		
		VECTOR<int> the_bars(1, start);
		
	 	//loop until have bars == num_bars//
	 	while (the_bars.size() < num_bars) {
				
	 		//look for edge with shortest distance from curr_index//
			int new_index = vertices[curr_index].min_weight();
		
			if (curr_index == start) {
				for (unsigned int i = 0; i < vertices.size(); i++) {
					vertices[i].remove_edge(curr_index);
				}
			}
		
			//take that minimum weight bar and add to the_bars//
			the_bars.push_back(new_index);
			//remove edges pointing back to bar we've already visited//
			for (unsigned int i = 0; i < vertices.size(); i++) {
				//if not new_index, remove all edges to curr_index//
				if (i != curr_index) {
					vertices[i].remove_edge(new_index);
				}
			}
			curr_index = new_index;

		}
		
		end = the_bars[the_bars.size() - 1];
		
		return end;
	 }
		

		//UPDATED METHOD- Grace//	
		// Dijkstra's Algorithm
		void Dijkstra( unsigned int origin, unsigned int destin ){
			
			
			if( origin >= vertices.size() || destin >= vertices.size() || vertices.size() == 0 ){
				
				std::cout << "Invalid Inputs" << std::endl;
				return;
				
			}
			
			/* Initialize the Elements */
			PRIORITY_QUEUE< unsigned int > the_PQ;
			VECTOR< unsigned int > parents( vertices.size(), -1 );
			VECTOR< int > distance( vertices.size(), 2147483647 );
			STACK< unsigned int > finalPath;
			
			bool found = false;
			
			/* Initialize the origin */
			the_PQ.push( origin );
			distance[origin] = 0;
			parents[origin] = -1;
			
			if( destin == origin ){	
				found = true;
			}
			
			if( !found ){
				
				/* Run the shortest path algorithm */
				while( !the_PQ.empty() ){
					
					// Get the top element of the stack and pop
					unsigned int index = the_PQ.top();
					the_PQ.pop();
					
					// Evaluate the edges from the vertex 
					for(unsigned int iter = 0; iter < vertices[ index ].num_edges(); iter++ ){
						
						// Obtain the edge
						Edge tempEdge = vertices[ index ].get_edge( iter );
						
						// If the weight of the edge plus distance of the  distance is less than the destin weight
						if( distance[ index ] + tempEdge.weight < distance[ tempEdge.destin ] ) {
							
							// Update the distance
							distance[ tempEdge.destin ] = distance[ index ] + tempEdge.weight;
							
							// Update the parent of the destin 
							parents[ tempEdge.destin ] = index;
							
							// Check if destin is the result;
							if( tempEdge.destin == destin && !found ){
								
								found = true;
							}
							
							the_PQ.push( tempEdge.destin );
						}
					}
				}
			}
			
			// Otherwise, go through the parents until we find the origin
			if( found ){
				
				unsigned int sentinel = destin;	
				finalPath.push( sentinel );		// Push the desination onto the stack
				
				while( parents[sentinel] != -1 ){
					
					finalPath.push( parents[sentinel] );	// Push the parent onto the stack
					sentinel = parents[sentinel];			// Update the sentinel
					
				}
				
				// Stack contains the correct order 
				std::cout << "The optimal barcrawl path from " << vertices[origin].get_name() <<  " is: ";
				while( !finalPath.empty() ){
					
					//find name of vertex to print name rather than number//	

					COUT << vertices[finalPath.top()].get_name() << ", ";
					finalPath.pop();
				}
				std::cout << "and the distance is " << distance[destin] << " miles" << std::endl;
				std::cout << std::endl;		
			}
			
		}		


		
		// Overloaded Operator
		void print_graph(){
			
			for( unsigned int iter = 0; iter < this->vertices.size(); iter++ ){
				
				COUT << iter << ": "; 
				this->vertices[ iter ].print_vertex();
				COUT << ENDL;
				
			}
			
		}
};

#endif
