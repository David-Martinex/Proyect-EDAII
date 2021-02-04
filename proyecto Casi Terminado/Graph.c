#include "Graph.h"

/**=============================================================== 
 * ======================{ METODOS PRIVADOS }=====================
 * ===============================================================*/

static size_t hash( char key[], size_t max )
{
	return (int)key[0] % max;
}

static size_t coll_res( size_t index, size_t max )
{
	 size_t new_index = (index + 1) % max;
	 return new_index;
}

/**=============================================================== 
 * ======================{ METODOS PUBLICOS }=====================
 * ===============================================================*/
/**
 * @brief Calcula la mejor ruta y el costo de dicha ruta.
 * @Se hace uso del algoritmo Dijkstra y el algoritmo BFS (Breadth First Search)
 *
 * @param origen        Referencia a un objeto Station con el que comenzaremos nustro algoritmo.
 * @param destino       Referencia a un objeto Station con el que terminaremos nuestro algoritmo.
 * @param stations        Referencia a una DLL donde se almacenan todos nuestros nodos representados por ciudades.
 * @param roots          Referencia a una DLL donde se almacenan todas nustras aristas junto con sus pesos.
 * @param path          Cadena de texto que nos permitira mostrar la mejor ruta y el costo final.
 * @param len           Tamaño de la cadena de texto que usamos para mostrar la mejor ruta y el costo final.
 */
void G_Best_Route(  Station* origen, Station* destino, DLL* stations, DLL* roots, char path[], size_t len)
{
	MapPtr vertices = Map_New( 10, 0L, hash, coll_res );  ///Se crea el mapa
	char route[100];
	strcpy(route, origen->name);							///Se obtiene el nombre del nodo inicial
	size_t menor_peso = 1000, best_neighbor = 0, peso_final = 0;
	Station* start;

	G_Add_Station( stations, vertices);							///Se agregan todas los nodos (ciudades) al mapa
	start = Map_Retrieve( vertices, origen->name);  ///Se hace la busqueda del nodo origen en el mapa
	DLL* queue = DLL_New();
	DLL_InsertBack(queue, start);							///Se inserta el nodo origen en una cola
	start->color = GRAY;

	while( !(DLL_IsEmpty(queue)) )				///Mientras la cola no esté vacia se genera todo el algoritmo
	{
		void* c;
		DLL_RemoveFront( queue, &c );			///Se extrae una ciudad de la cola
		Station* u = ( Station* )c;					///Se castea a un objeto Station 

		size_t listLen = DLL_Len( u->neighbors );
		void* nodesList[ listLen ];
		DLL_GetInformation( u->neighbors, nodesList);  ///Se obtienen todos sus vecinos

		for( size_t i=0; i < listLen; i++ )    		///Se itera sobre todos sus vecinos
		{
			Station* n = ( Station* )nodesList[i];	///Se castea cada vecino a un objeto Station 

			size_t listLen2 = DLL_Len( roots );
			void* nodesList2[ listLen2 ];
			DLL_GetInformation( roots, nodesList2);  ///Se obtinen todas las aristas del grafo

			for( size_t j=0; j < listLen2; j++ )	///Se itera sobre todas las aristas del grafo
			{
				Roots* a = ( Roots* )nodesList2[j];	///Se castea cada arista a un objeto Roots
				
				if(( 0 == strcmp(u->name, a->first->name)) && (0 == strcmp(n->name, a->last->name)))  ///Se compara hasta obtener 
				{																					///la arista buscada y así saber su peso
					if((a->weight < menor_peso) && (n->color == BLACK))  ///Se valida que el vecino econtrado no haya sido visitado
					{													///y que el peso sea el menor entre todas las aristas
						menor_peso = a->weight;							///De ser así se asume que es la mejor ruta para continuar
						best_neighbor = i;								///y que el vecino es el mejor cadidato entre todos los vecinos
					}
				}			
			}
		}

		Station* n2 = ( Station* )nodesList[best_neighbor]; 	///Se busca en la tabla y se castea al mejor vecino
		n2->color = GRAY;								///Se colorea al mejor vecino como descubierto
		peso_final = peso_final + menor_peso;			///Se suma el peso final
		menor_peso = 1000;								///Se reinicia el menor peso
		strcpy(n2->predecesor, u->name);
		strcat(route,n2->name);							///Se concatena el nombre del vecino a la mejor ruta
		if(0 != strcmp(n2->name, destino->name)){		///Todo el ciclo While depende de que haya elementos en la cola
			DLL_InsertBack(queue, n2);					///no se agregan elementos a la cola si ya llegamos al nodo (ciudad) destino
		}else{
			break;
		}
		u->color = WHITE;
	}

	snprintf( path, len - 1, "MEJOR RUTA: %s\nCOSTO FINAL: %ld\n", route, peso_final); ///Al finalizar el ciclo While se ha generado
	Map_Delete( vertices );
	DLL_Delete( queue );
}																						///la mejor ruta y el costo final

void G_Best_Route_Quick(  Station* origen, Station* destino, DLL* stations, DLL* roots, char path[], size_t len)
{
	MapPtr vertices = Map_New( 10, 0L, hash, coll_res );  ///Se crea el mapa
	char route[100];
	strcpy(route, origen->name);							///Se obtiene el nombre del nodo inicial
	size_t menor_peso = 1000, best_neighbor = 0, peso_final = 0;
	Station* start;

	G_Add_Station( stations, vertices);							///Se agregan todas los nodos (ciudades) al mapa
	start = Map_Retrieve( vertices, origen->name);  ///Se hace la busqueda del nodo origen en el mapa
	DLL* queue = DLL_New();
	DLL_InsertBack(queue, start);							///Se inserta el nodo origen en una cola
	start->color = GRAY;

	while( !(DLL_IsEmpty(queue)) )				///Mientras la cola no esté vacia se genera todo el algoritmo
	{
		void* c;
		DLL_RemoveFront( queue, &c );			///Se extrae una ciudad de la cola
		Station* u = ( Station* )c;					///Se castea a un objeto Station 

		size_t listLen = DLL_Len( u->neighbors );
		void* nodesList[ listLen ];
		DLL_GetInformation( u->neighbors, nodesList);  ///Se obtienen todos sus vecinos

		for( size_t i=0; i < listLen; i++ )    		///Se itera sobre todos sus vecinos
		{
			Station* n = ( Station* )nodesList[i];	///Se castea cada vecino a un objeto Station

			size_t listLen2 = DLL_Len( roots );
			void* nodesList2[ listLen2 ];
			DLL_GetInformation( roots, nodesList2);  ///Se obtinen todas las aristas del grafo

			for( size_t j=0; j < listLen2; j++ )	///Se itera sobre todas las aristas del grafo
			{
				Roots* a = ( Roots* )nodesList2[j];	///Se castea cada arista a un objeto Roots 
				
				if(( 0 == strcmp(u->name, a->first->name)) && (0 == strcmp(n->name, a->last->name)))  ///Se compara hasta obtener 
				{																					///la arista buscada y así saber su peso
					if((a->weight < menor_peso) && (n->color == BLACK))  ///Se valida que el vecino econtrado no haya sido visitado
					{													///y que el peso sea el menor entre todas las aristas
						menor_peso = a->weight;							///De ser así se asume que es la mejor ruta para continuar
						
						best_neighbor = i;								///y que el vecino es el mejor cadidato entre todos los vecinos
					}
				}			
			}
		}

		Station* n2 = ( Station* )nodesList[best_neighbor]; 	///Se busca en la tabla y se castea al mejor vecino
		n2->color = GRAY;								///Se colorea al mejor vecino como descubierto
		peso_final = peso_final + menor_peso;			///Se suma el peso final
		menor_peso = 1000;								///Se reinicia el menor peso
		strcpy(n2->predecesor, u->name);
		strcat(route,n2->name);							///Se concatena el nombre del vecino a la mejor ruta
		if(0 != strcmp(n2->name, destino->name)){		///Todo el ciclo While depende de que haya elementos en la cola
			DLL_InsertBack(queue, n2);					///no se agregan elementos a la cola si ya llegamos al nodo (ciudad) destino
		}else{
			break;
		}
		u->color = WHITE;
	}

	snprintf( path, len - 1, "MEJOR RUTA: %s\nCOSTO FINAL: %ld\n", route, peso_final); ///Al finalizar el ciclo While se ha generado
	Map_Delete( vertices );
	DLL_Delete( queue );
}
/**
 * @brief Inserta todos los nodos (stations) en la tabla.
 *
 * @param stations        Referencia a una DLL que contiene objetos Station. 
 * @param vertices      Referencia a un objeto Map.
 */
void G_Add_Station( DLL* stations, MapPtr vertices )
{
	size_t listLen = DLL_Len( stations );

	void* nodesList[ listLen ];

	DLL_GetInformation( stations, nodesList);

	for( size_t i=0; i < listLen; i++ ){
		Station* c = ( Station* )nodesList[i];

		Map_Insert( vertices, c->name , c);
	}
}