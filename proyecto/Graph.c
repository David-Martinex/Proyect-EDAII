#include "Graph.h"


Graph::Graph()
{
	// nada (por el momento)
}

bool Graph::add_vertex( Vertex v )
{
	auto ret = vertices.insert( { v.get_name(), v } );
	// 'map' no permite duplicados, así que no hay necesidad de buscarlos
	
	return ret.second;
}

bool Graph::add_edge( std::string edge1, std::string edge2 )
{
	bool res = false;
	// uno, o ambos nodos, no existen

	auto v1 = this->vertices.find( edge1 );
	auto v2 = this->vertices.find( edge2 );

	if( v1 != this->vertices.end() and v2 != this->vertices.end() ){

		v1->second.add_neighbor( v2->second );
		v2->second.add_neighbor( v1->second );

		return true;
	}

	return res;
}

bool Graph::add_edge_directed( std::string edge1, std::string edge2 )
{
	bool res = false;

	auto v1 = this->vertices.find( edge1 );
	auto v2 = this->vertices.find( edge2 );

	if( v1 != this->vertices.end() and v2 != this->vertices.end() ){

		v1->second.add_neighbor( v2->second );
		
		return true;
	}

	return res;
}

#if 1
bool Graph::add_edge_weighted( std::string edge1, std::string edge2, int weigth )
{
    bool res = false;
    
    auto v1 = this->vertices.find( edge1 );
	auto v2 = this->vertices.find( edge2 );

	if( v1 != this->vertices.end() and v2 != this->vertices.end() ){

		v1->second.add_neighbor( v2->second );
		v2->second.add_neighbor( v1->second );
		
		weigths.insert({v1->second.get_name() + v2->second.get_name(), weigth});
		weigths.insert({v2->second.get_name() + v1->second.get_name(), 100});
		
		return true;
	}

	return res;
}

int Graph::get_weigth( std::string u , std::string v ){
    auto V1 = this->vertices.find(u);
    auto V2 = this->vertices.find(v);
    
    if(V1 != this->vertices.end() and V2 != this->vertices.end() ){
        
        auto weigth = this->weigths.find( u + v );
        return weigth->second;

    }
    return 0;
}

#endif

void Graph::print()
{
	for( auto v : this->vertices ){
		std::cout << "\n" << v.second.get_name() << ": ";
		v.second.print_neighbors();
	}
	std::cout << "\n";
}

std::map<std::string, Vertex>* Graph::get_vertices()
{
	return &(this->vertices);
}

Vertex* Graph::get_vertex( std::string name )
{
	auto v = this->vertices.find( name );
	// .find() devuelve un iterador (apuntador) a la posición donde haya 
	// encontrado la coincidencia con la clave 'name'
	
	return &(v->second);
}

#ifdef DEBUG
// función auxiliar para imprimir el contenido de la cola
static void print_queue( std::deque<std::string> queue )
{
	std::cout << "El contenido de la cola es: ";
	for( auto q : queue ){
		std::cout << q << ", ";
	}
	std::cout << "\n";
}
#endif  

void Graph::bfs( std::string start )
{

   	// inicializamos TODOS los vértices a su valor por defecto (con respecto a
   	// los atributos que tienen que ver con el algoritmo bfs)
	for( auto it = this->vertices.begin(); it != this->vertices.end(); ++it ){ 

		(it->second).set_color( Vertex::Colors::BLACK );
		// el vértice no ha sido descubierto ni visitado

		(it->second).set_distance( 0 );
		(it->second).set_predecesor( "Nil" );
	}


	get_vertex( start )->set_color( Vertex::Colors::GRAY );
   	// marcamos al vértice de inicio como descubierto


#ifdef DEBUG
	std::cout << "Antes: \n";
	for( auto it = this->vertices.begin(); it != this->vertices.end(); ++it ){ 
		(it->second).print();
	}
#endif  

	std::deque<std::string> queue;
   	// una 'list' serviría al mismo propósito, pero 'deque' tiene más espíritu de
   	// cola que una lista plana. 'deque' es por: double ended queue


   queue.push_back( start );
   // insertamos (encolamos) al vértice de inicio en la parte trasera de la cola

   while( not queue.empty() ){

#ifdef DEBUG
      print_queue( queue );
#endif  

      std::string next_vertex = queue.front(); queue.pop_front();
      // obtenemos el NOMBRE asociado al vértice de trabajo ...
      // (desencolar toma dos operaciones: .front() y .pop_front())


#ifdef DEBUG
      std::cout << "Vértice de trabajo: " << next_vertex << std::endl;
#endif  

      Vertex* vertex = get_vertex( next_vertex );
      // obtenemos una REFERENCIA al vértice de trabajo ...

      std::list<Vertex>* v = vertex->get_neighbors();
      // obtenemos el original de la LISTA de vértices vecinos ...

      for( auto w = v->begin(); w != v->end(); ++w ){ 

         Vertex* neighbor = get_vertex( w->get_name() );

         if( neighbor->get_color() == Vertex::Colors::BLACK ){

#ifdef DEBUG
            std::cout << "* procesando al vértice: " << neighbor->get_name() << std::endl;
#endif

            neighbor->set_color( Vertex::Colors::GRAY );
            // vertice descubierto ...

            neighbor->set_distance( vertex->get_distance() + 1 );
            // establecemos la distancia desde 'start' ...

            neighbor->set_predecesor( vertex->get_name() );
            // establecemos al predecesor ...

            queue.push_back( neighbor->get_name() );
            // encolamos al vértice recién descubierto
         }
#ifdef DEBUG
         else{
            std::cout << "El vértice: " << neighbor->get_name();
            std::cout << " ya había sido descubierto. No se hace nada\n";
         }
#endif  
      }
      
      vertex->set_color( Vertex::Colors::WHITE );
      // vértice visitado
   }

#ifdef DEBUG
   std::cout << "Después: \n";
	for( auto it = this->vertices.begin(); it != this->vertices.end(); ++it ){ 
      (it->second).print();
   }
#endif  
}

#if 1
//Version 1 sin ponderacion
void Graph::bfs_printBack( std::string start )
{
    if( get_vertex( start )->get_predecesor() == "Nil" ){
        std::cout << "El punto de destino es igual al punto de salida. Nada que hacer.\n";
        return;
    }
    
    auto v = get_vertex( start );
    
    auto name = v->get_name();
    auto distance = v->get_distance();
    auto predecesor = v->get_predecesor();
    
    while( 1 ){
        std::cout << name << ":" << distance << ". " << predecesor << std::endl;
        
        if( predecesor == "Nil" ) break;
        else v = get_vertex( predecesor );
        
        name = v->get_name();
        distance = v->get_distance();
        predecesor = v->get_predecesor();
    }
    std::cout << "\n";
}
#endif

#if 0
//version 2
void Graph::bfs_printBack( std::string start )
{
    if( get_vertex( start )->get_predecesor() == "Nil" ){
        std::cout << "El punto de destino es igual al punto de salida. Nada que hacer.\n";
        return;
    }
    
    auto v = get_vertex( start );
    
    auto name = v->get_name();
    auto distance = v->get_distance();
    auto predecesor = v->get_predecesor();
    
    auto ponderacion = get_weigth( start, predecesor);
    
    while( 1 ){
        std::cout << name << ":" << distance << ". " << predecesor << std::endl;
        
        if( predecesor == "Nil" ) break;
        else v = get_vertex( predecesor );
        
        name = v->get_name();
        distance = v->get_distance();
        predecesor = v->get_predecesor();
    }
    std::cout << "\n";
}
#endif