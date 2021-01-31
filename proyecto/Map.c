#include "Map.h"

/**
 * @brief Crea un nuevo mapa.
 *
 * @param size El máximo número de elementos que se podrán guardar.
 * @param empty El valor que indicará que el slot está vacío. Depende de cada
 * aplicación.
 * @param hash Es una función hash inyectada por el usuario.
 * @param coll_res Es una función de resolución de colisiones inyectada por el usuario.
 *
 * @return Una referencia a un nuevo objeto Map. NULL en caso de que falle la asignación de memoria.
 */
MapPtr Map_New( size_t capacity, size_t empty_val, pHash hash, pCollRes coll_res )
{
	MapPtr map = malloc( sizeof( Map ) );
	// creamos al objeto Map

	if( NULL != map ){
		
		map->table = malloc( sizeof( Entry ) * capacity );
		// creamos al arreglo que servirá de contenedor a la tabla hash

		if( NULL != map->table ){

			for( size_t i = 0; i < capacity; ++i ){ 
				map->table[ i ].key[0] = empty_val; 
				map->table[ i ].station = Station_New( "" );
			}
			// limpiamos la tabla
				map->size = capacity;
				map->len = 0L;
				map->empty = empty_val;
				map->hash = hash;
				map->coll_res = coll_res;

		} else{
			free( map );
			// si no hay contenedor, entonces no hay mapa

			map = NULL;
		}
	}
	return map;
}

/**
 * @brief Destruye a un objeto Map.
 *
 * @param this Referencia a un objeto Map.
 */
void Map_Delete( MapPtr this )
{
	assert( this );

	free( this->table );
	// devolvemos la memoria del contenedor
	
	free( this );
	// devolvemos la memoria del objeto
}

/**
 * @brief Inserta un objeto City en el mapa.
 *
 * @param this        Referencia a un objeto Map.
 * @param nombre      Cadena de texto asociada al registro (key).
 * @param city        Referencia a un objeto City (value).
 *
 * @return true si el elemento pudo ser insertado en el mapa; false en cualquier otro caso.
 */
bool Map_Insert( MapPtr this, char nombre[], Station* station )
{
	size_t loc = this->hash( nombre, this->size );
	while( this->table[ loc ].key[0] != this->empty /*¿y si no hay slots libres?*/ ){
		loc = this->coll_res( loc, this->size );
	}

	strcpy(this->table[ loc ].key, nombre);
	this->table[ loc ].station = station;

	++this->len;
	
	return true;
}

/**
 * @brief Busca y retorna el valor asociado a la clave.
 *
 * @param this        Referencia a un objeto Map.
 * @param nombre      Cadena de texto asociada al registro (key).
 *
 * @return La referencia del objeto City asociado a la clave si está en almacenado en la tabla, en cualquier otro caso la referenciade a un objeto City con valores iniciales "vacios".
 */

Station* Map_Retrieve( MapPtr this, char nombre[])
{
	size_t start_loc = this->hash( nombre, this->size );

	size_t loc = start_loc;

	bool more_to_search = true;

	do{

		if( (0 == strcmp(this->table[ loc ].key, nombre)) or this->table[ loc ].key[0] == this->empty ){
			more_to_search = false;
		} else{
			loc = this->coll_res( loc, this->size );
		}

	} while( loc != start_loc and more_to_search == true );


	bool found = 0 == strcmp(this->table[ loc ].key, nombre);

	if( found == true ){

		//city = (this->table[ loc ].city);
		return this->table[ loc ].station;
	}

	return Station_New( "" );
}

/**
 * @brief Devuelve el número de elementos actualmente almacenados en la tabla.
 *
 * @param this Referencia a un objeto Map.
 *
 * @return El número de elementos actualmente almacenados en la tabla.
 */
size_t Map_Len( MapPtr this )
{
	return this->len;
}

/**
 * @brief Devuelve el número máximo de elementos que se pueden almacenar en la tabla.
 *
 * @param this Referencia a un objeto Map.
 *
 * @return El número máximo de elementos que se pueden almacenar en la tabla.
 */
size_t Map_Size( MapPtr this )
{
	return this->size;
}