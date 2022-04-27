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
	
		//VECTOR< Vertex< T > > vertices;	// Adjacency List
		
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
		
		// Private DFS method
		void TopSort( unsigned int vertVal, VECTOR<unsigned int>& parents, VECTOR<bool>& visited ){
				
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
						
						// Otherwise, recursively call the destination vertex
						TopSort( tempEdge.destin, parents, visited );
						
					}
				}
			}
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

	   

		//NEW METHOD
		//Return number of vertices
		long unsigned int num_vertices(){
			 return vertices.size();
	   }

	   //NEW METHOD
		//Return vector of vertices
		VECTOR< Vertex<T> > get_vertices(){

			 return vertices;
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
		//Locate data - return the index for a particular data value
		unsigned int locate_data( T& data ){

			 unsigned int i;
			 const char* data_name = (data.name).c_str();


			 for (i = 0; i < this->vertices.size(); i++){

				  //Convert current name to const char*
				  const char* curr_name = (this->get_vertex_value(i).name).c_str();

				 if(strcmp(data_name, curr_name) == 0) return i;

		    }

			 return 100;

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


	 //NEW METHOD:
	 //PRUNE TREE method: prunes all additional edges from each vertex if it finds a unique edge at that vertex
	 void prune_graph(){

		  for (unsigned int iter=0; iter < vertices.size(); iter++ ){

				for (unsigned int jter=0; jter < vertices[iter].num_edges(); jter++ ){

					 unsigned int vertex_out = vertices[iter].get_edge(jter).destin;

				
					 //If we find a unique edge at a vertex, delete all other edges so that the search
					 //forces it to go to the unique destination
					 if (this->is_unique_edge(vertex_out)){

						  unsigned int kter = vertices[iter].num_edges()+1;

						  while (kter > 0){

						  								
								vertices[iter].remove_edge(vertices[iter].get_edge(kter-1).destin);

								kter --;

						  }
						  
						  int weight = 0;
						  vertices[iter].add_edge(vertex_out, weight);

					 }

				}
		  }
	 }


	 




						
	
		// Public DFS Method
		void DFS( unsigned int destin ){
			
			// If the input is invalid or the Graph is empty
			if( destin >= vertices.size() || vertices.size() == 0){
				
				std::cout << "Invalid inputs to DFS" << std::endl;
				
				return;
			}
			
			/* Initialize the Values for the DFS */
			
			// Track the parents for printing the results
			VECTOR<unsigned int> parents(vertices.size());
			
			// Keep track of the visited vertices
			VECTOR<bool> visited(vertices.size());
			
			// Create a stack to store the final path
			STACK< unsigned int > finalPath;
			bool found = false;

			// Initialize the search	
			parents[0] = -1;
			
			// Set all the visited elements to false
			for( unsigned int iter = 0; iter < vertices.size(); iter++ ){
				visited[iter] = false;
			}
			
			// If the destination is the origin, mark found as true
			if( destin == 0 ){
				
				found = true;
				
			}
			
			// Otherwise, run the recursive DFS 
			else{

				found = DFS( destin, 0, parents, visited );
			
			}
			
			// If we have not found the node, there is no path
			if( !found ){
				
				std::cout << "No valid path from 0 to " << destin << std::endl;
				return;
			}
			
			// Otherwise, go through the parents until we find the origin
			unsigned int sentinel = destin;	
			finalPath.push( sentinel );		// Push the desination onto the stack
			
			while( parents[sentinel] != -1 ){
				
				finalPath.push( parents[sentinel] );	// Push the parent onto the stack
				sentinel = parents[sentinel];			// Update the sentinel
				
			}
			
			// Stack contains the correct order 
			std::cout << "The valid DFS path from 0 to " << destin << " is: ";
			while( !finalPath.empty() ){
				
				std::cout << finalPath.top() << " ";
				finalPath.pop();
			}
			
			std::cout << std::endl;
				
			
		}
		
		
		// Public DFS Method
		void DFS( unsigned int origin, unsigned int destin ){
			
			// If the input is invalid or the Graph is empty
			if( origin >= vertices.size() || destin >= vertices.size() || vertices.size() == 0){
				
				std::cout << "Invalid inputs to DFS" << std::endl;
				
				return;
			}
			
			/* Initialize the Values for the DFS */
			
			// Track the parents for printing the results
			VECTOR<unsigned int> parents(vertices.size());
			
			// Keep track of the visited vertices
			VECTOR<bool> visited(vertices.size());
			
			// Create a stack to store the final path
			STACK< unsigned int > finalPath;
			bool found = false;

			// Initialize the search	
			parents[ origin ] = -1;
			
			// Set all the visited elements to false
			for( unsigned int iter = 0; iter < vertices.size(); iter++ ){
				visited[iter] = false;
			}
			
			// If the destination is the origin, mark found as true
			if( destin == origin ){
				
				found = true;
				
			}
			
			// Otherwise, run the recursive DFS 
			else{

				found = DFS( destin, origin, parents, visited );
			
			}
			
			// If we have not found the node, there is no path
			if( !found ){
				
				std::cout << "No valid path from " << origin << " to " << destin << std::endl;
				return;
			}
			
			// Otherwise, go through the parents until we find the origin
			unsigned int sentinel = destin;	
			finalPath.push( sentinel );		// Push the desination onto the stack
			
			while( parents[sentinel] != -1 ){
				
				finalPath.push( parents[sentinel] );	// Push the parent onto the stack
				sentinel = parents[sentinel];			// Update the sentinel
				
			}
			
			// Stack contains the correct order 
			std::cout << "The valid DFS path from " << origin << " to " << destin << " is: ";
			while( !finalPath.empty() ){
				
				std::cout << finalPath.top() << " ";
				finalPath.pop();
			}
			std::cout << std::endl;
				
			
		}
		
		void BFS( unsigned int destin ){
			
			// If Graph can't be search, inform user and return 
			// destin cannot be greater than the number of vertices
			// The number of vertices must not be 0
			if( destin >= vertices.size() || vertices.size() == 0){
				
				std::cout << destin << " is not a valid vertex location" << std::endl;
				
				return;
			}
			
			/* Create elements for the search */
			
			// queue to store the next vertex to evaluate
			QUEUE< unsigned int > theQueue;
			
			// Keeping track if the vertex has been visited. Set all initially to false
			bool* visited = new bool[vertices.size()];
			for( unsigned int iter = 0; iter < vertices.size(); iter++ ){
				
				visited[iter] = false;
			}
			
			// Keeping track of the parents 
			unsigned int* parents = new unsigned int[vertices.size()];
			
			// Use this stack for the final path
			STACK< unsigned int > finalPath;
			
			/* Initialize the search */
			bool found = false; 
			
			// Push the origin onto the Queue
			theQueue.push(0);
			
			// The origin has no parent, and the origin has been visited
			parents[0] = -1;
			
			// Set found to true if the origin is the destination
			if( destin == 0 ){
				found = true;
			}
			
			// While the element is not found and the queue is not empty
			while( !found && !theQueue.empty() ){
				
				// First step in BFS is to obtain and remove the front element from the queue 
				unsigned int vertex = theQueue.front();
				theQueue.pop();
				
				// Mark the vertex as visited
				visited[ vertex ] = true;
				
				// Iterate through each edge 
				for( unsigned int iter = 0; iter < vertices[ vertex ].num_edges(); iter++){
					
					// Get the destination from the edge
					unsigned int edgeDestin = vertices[ vertex ].get_edge( iter ).destin;
					
					// If the edge's destination matches our destination, we found the node
					if( edgeDestin == destin ){
						
						found = true;
						
						// Mark the destination's parent as vertex 
						parents[ edgeDestin ] = vertex;
						
						break;
					}
					
					// If the destination has not been visited
					else if( visited[ edgeDestin ] == false ) {
						
						// Push the destination onto the queue
						theQueue.push( edgeDestin );
						
						// Mark edgeDestin's parent as vertex
						parents[ edgeDestin ] = vertex;
						
						// Mark visited as true
						visited[ edgeDestin ] = true;

					}
				}

			}
			
			// If we have not found the node, there is no path
			if( !found ){
				
				std::cout << "No valid path from origin to " << destin << std::endl;
				return;
			}
			
			// Otherwise, go through the parents until we find the origin
			unsigned int sentinel = destin;	
			finalPath.push( sentinel );		// Push the desination onto the stack
			
			while( parents[sentinel] != -1 ){
				
				finalPath.push( parents[sentinel] );	// Push the parent onto the stack
				
				sentinel = parents[sentinel];			// Update the sentinel
				
			}
			
			// Stack contains the correct order 
			// CHANGED: formatted output to print the digits of the passcode instead of the vertices!
			std::cout << "The valid passcode is: ";
			while( !finalPath.empty() ){
				
				std::cout << this->vertices[finalPath.top()].get_vertex_value();
				finalPath.pop();
			}
			std::cout << std::endl;
		}

		// BFS with an origin and destination node
		void BFS( unsigned int origin, unsigned int destin ){
			
			// If Graph can't be search, inform user and return 
			// origin destin cannot be >= than the number of vertices
			// The number of vertices must not be 0
			if( origin >= vertices.size() || destin >= vertices.size() || vertices.size() == 0){
				
				std::cout << "Invalid BFS inputs" << std::endl;
				
				return;
			}
			
			/* Create elements for the search */
			
			// queue to store the next vertex to evaluate
			QUEUE< unsigned int > theQueue;
			
			// Keeping track if the vertex has been visited. Set all initially to false
			bool* visited = new bool[vertices.size()];
			for( unsigned int iter = 0; iter < vertices.size(); iter++ ){
				
				visited[iter] = false;
			}
			
			// Keeping track of the parents 
			unsigned int* parents = new unsigned int[vertices.size()];
			
			/* Initialize the search */
			bool found = false; 
			
			// Push the origin onto the Queue
			theQueue.push( origin );
			
			// The origin has no parent, and the origin has been visited
			parents[ origin ] = -1;
			
			// Set found to true if the origin is the destination
			if( destin == origin ){
				found = true;
			}
			
			// While the element is not found and the queue is not empty
			while( !found && !theQueue.empty() ){
				
				// First step in BFS is to obtain and remove the front element from the queue 
				unsigned int vertex = theQueue.front();
				theQueue.pop();
				
				// Mark the vertex as visited
				visited[ vertex ] = true;
				
				// Iterate through each edge 
				for( unsigned int iter = 0; iter < vertices[ vertex ].num_edges(); iter++){
					
					// Get the destination from the edge
					unsigned int edgeDestin = vertices[ vertex ].get_edge( iter ).destin;
					
					// If the edge's destination matches our destination, we found the node
					if( edgeDestin == destin ){
						
						found = true;
						
						// Mark the destination's parent as vertex 
						parents[ edgeDestin ] = vertex;
						
						break;
					}
					
					// If the destination has not been visited
					if( visited[ edgeDestin ] == false ) {
						
						// Push the destination onto the queue
						// std::cout << "pushing " << edgeDestin << std::endl;
						theQueue.push( edgeDestin );
						// Mark edgeDestin's parent as vertex
						parents[ edgeDestin ] = vertex;
						
						visited[ edgeDestin ] = true;
					}
				}

			}
			
			// If we have not found the node, there is no path
			if( !found ){
				
				std::cout << "No valid path from " << origin << " to " << destin << std::endl;
				return;
			}
			
			// Otherwise, go through the parents until we find the origin
			STACK< unsigned int > finalPath;
			unsigned int sentinel = destin;	
			finalPath.push( sentinel );		// Push the desination onto the stack
			
			while( parents[sentinel] != -1 ){
				
				finalPath.push( parents[sentinel] );	// Push the parent onto the stack
				
				sentinel = parents[sentinel];			// Update the sentinel
				
			}
			
			// Stack contains the correct order 
			std::cout << "The valid BFS path from " << origin << " to " << destin << " is: ";
			while( !finalPath.empty() ){
				
				std::cout << finalPath.top() << " ";
				finalPath.pop();
			}
			std::cout << std::endl;
		}
		
		
		// Method for Topological Sort
		Graph<T> TopSort( ){
			
			/* Initialize the Values for the Topological Sort */
			
			/* Initialize the return Graph */
			Graph<T> TopSortGraph;
			
			for( unsigned int iter = 0; iter < vertices.size(); iter++ ){
				
				// Add the value of each vertex to the TopSort graph
				TopSortGraph.add_vertex( vertices[ iter ].get_vertex_value() );
				
			}
			
			// Track the parents for printing the results
			VECTOR<unsigned int> parents(vertices.size());
			
			// Keep track of the visited vertices
			VECTOR<bool> visited(vertices.size());
			
			// Create a stack to store the final path
			STACK< unsigned int > finalPath;
			
			// Set all the visited elements to false
			for( unsigned int iter = 0; iter < vertices.size(); iter++ ){
				visited[iter] = false;
				parents[iter] = -1;
			}
			
			// Run the Topological Sort - We must check every element 
			for(unsigned int iter = 0; iter < vertices.size(); iter++ ){
				TopSort( iter, parents, visited );
			}
			
			// Add all the edges from the parent to the Graph 
			for( unsigned int iter = 1; iter < vertices.size(); iter++ ){
				
				// Get the edge weight 
				int edgeWeight = 0;
				get_edge_value( parents[iter], iter, edgeWeight );
				
				// Add the Edge
				TopSortGraph.add_edge(parents[iter], iter, edgeWeight );
			}
			
			return TopSortGraph;
		}
		
		
		// Return the Minimum Spanning Tree
		Graph<T> MST(){
			
			Graph<T> MSTGraph;
			
			// Set up the priority queue for the algorithm
			PRIORITY_QUEUE< MSTElem > MST_PQ;
			
			// Use a Hash Table for the Frontier
			UNOR_MAP< unsigned int, bool > frontier;
			
			// Track the parents of the vertex
			unsigned int* parents = new unsigned int[ vertices.size() ];
			
			// Track the weights of the edges 
			int* weights = new int[ vertices.size() ];
			
			// Initialize the origin and push onto the Priority Queue 
			MSTElem origin( 0, 0 );
			MST_PQ.push( origin );
			
			// Set the origin on the frontier to true
			frontier.insert( {0, true} );
			
			// Set the parent's origin to -1 and weight to largest negative value
			parents[0] = -1;
			weights[0] = -2147483648;
			
			for( unsigned int i = 1; i < vertices.size(); i++ ){
				
				MSTElem temp( i, 2147483647 );
				weights[i] = 2147483647;
				MST_PQ.push( temp );
				frontier.insert( {i, true} );
			}
			
			while( !MST_PQ.empty() ){
				
				// Obtain the first element
				MSTElem currElem = MST_PQ.top();
				
				// Remove the first element
				MST_PQ.pop();
				
				// Set the current node in the frontier to false
				frontier[ currElem.index ] = false;
				
				// Go through all the outgoing edges of the vertex
				for( unsigned int i = 0; i < vertices[ currElem.index ].num_edges(); i++ ){
					
					// Get the current edge from MST current element's vertex
					Edge currEdge = vertices[ currElem.index ].get_edge( i );
					
					if( currEdge.weight < weights[ currEdge.destin ] && frontier[ currEdge.destin ] ){
						
						weights[ currEdge.destin ] = currEdge.weight;
						parents[ currEdge.destin ] = currElem.index;
						
						MSTElem pushElem( currEdge.destin, currEdge.weight);
						MST_PQ.push( pushElem );
						
					}
				}
			}
			
			for( unsigned int i = 0; i < vertices.size(); i++){
				
				MSTGraph.add_vertex( vertices[i].get_vertex_value() );
			}
			
			for( unsigned int i = 0; i < vertices.size(); i++){
				
				if( parents[i] != -1 ){
					
					MSTGraph.add_edge( parents[i], i, weights[i] );
					
				}
			}
			
			return MSTGraph;
			
		}
		
		
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
				std::cout << "The valid Dijkstra path from 0 to " << destin << " is: ";
				while( !finalPath.empty() ){
					
					std::cout << finalPath.top() << " ";
					finalPath.pop();
				}
				std::cout << ", and the distance is " << distance[destin] << std::endl;
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
