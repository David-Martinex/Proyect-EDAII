#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// para declarar y procesar cadenas
#include "Vertex.hpp"
#include "Graph.hpp"


int main()
{
	char vertices[11] = { "K", "J", "I", "H", "G", "F", "E", "D", "C", "B", "A"};
	char edges[11] = { "AE", "AB", "BC", "BF", "DH", "EI", "FG", "FI", "GJ", "GK", "HK" };

	Graph g;

	for( auto& v : vertices ){ g.add_vertex( Vertex( v ) ); }

	for( auto& e : edges ){ g.add_edge( e.substr( 0, 1 ), e.substr( 1, 1 ) ); }
	// .substr( a_partir_de_dónde, cuántos_queremos_leer )
	//for( auto& e : edges ){ g.add_edge_directed( e.substr( 0, 1 ), e.substr( 1, 1 ) ); }
	//for( auto& e : edges ){ g.add_edge_weighted( e.substr( 0, 1 ), e.substr( 1, 1 ), 2 ); }

	g.print();

	g.bfs( "F" );
	
	std::cout << "\nRuta:\n";
	g.bfs_printBack("D");
}