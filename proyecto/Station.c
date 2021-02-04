#include "Station.h"

/**
*	@brief Crea un vértice de tipo Station.
*	@return Referencia a un nuevo vértice de tipo Station listo para usar.
*/
Station* Station_New( char name[] ){
	Station* c = ( Station* ) malloc( sizeof( Station ) );

	strcpy( c->name, name );

	c->neighbors = DLL_New();

	c->color = BLACK;
	c->distance = 0;
	strcpy( c->predecesor, "" );
	c->discoveryTime = 0;
	c->finishTime = 0;

	return c;
}

/**
 * @brief Destructor del objeto Station.
 * @param this Referencia al objeto a destruir de tipo Station.
 */
void Station_Delete( Station* this ){
	assert( this );
	assert( this->neighbors );

	free( this->neighbors );

	free( this );
}

/**
*	@brief Agrega una nueva estacion vecina.
*	@param this Referencia al vertice dode se agregara un nuevo vecino.
*	@param station Referencia a la estacion a agregar.
*	@return true Si se ha añadido con éxito.
*	@return false Si NO se añadio con éxico. 
*/
bool ST_Add_Neighbor( Station* this, Station* station ){ return DLL_InsertBack( this->neighbors, station ); }

/**
*	@brief Setter del atributo distance.
*	@param this Referencia a un objeto de tipo Station.
*	@param distance Valor a insertar.
*/
void ST_Set_Distance( Station* this, int distance ){ this->distance = distance; }

/**
*	@brief Setter del atributo color.
*	@param this Referencia a l objeto.
*	@param color Valor a insertar.
*/
void ST_Set_Color( Station* this, int color ){ this->color = color; }

/**
*	@brief Setter del atributo predecesor.
*	@param this Referencia a l objeto.
*	@param predecesor Valor a insertar.
*/
void ST_Set_Predecesor( Station* this, char predecesor[] ){ strcpy( this->predecesor, predecesor ); }

/**
*	@brief Setter del atributo discoveryTime.
*	@param this Referencia a l objeto.
*	@param discoveryTime Valor a insertar.
*/
void ST_Set_DiscoveryTime( Station* this, size_t discoveryTime ){ this->discoveryTime = discoveryTime; }

/**
*	@brief Setter del atributo finishTime.
*	@param this Referencia a l objeto.
*	@param finishTime Valor a insertar.
*/
void ST_Set_FinishTime( Station* this, size_t finishTime ){ this->finishTime = finishTime; }

/**
*	@brief Imprime lista de vecinos recuperando su direcicon de memoria
*	@param this Referencia a un objeto de tipo Station.
*	@param str Cadena donde se guardara la candena
*	@param len Tamagno de str view str.
*/
void ST_To_String_Neighbors( Station* this, char str[], size_t len ){
	size_t lenNeighbors = DLL_Len( this->neighbors );
	if(  lenNeighbors == 0 ) { 
		str = "";
		return; 
	}

	void* ptrArr[ lenNeighbors ];
	char name[64] = "";
	DLL_GetInformation( this->neighbors, ptrArr );

	for( size_t i = 0; i < lenNeighbors; ++i){
		Station* c = ( Station* )ptrArr[i];
		strcat( name, c->name );
		strcat( name, "->" );
		
	}

	snprintf( str, len - 1, "%s", name );

}

/**
*	@brief Convierte un objeto a cadena de texto.
*	@param this Referencia a la estacion a convertir.
*	@param chain Arreglo donde se guardara el formato de texto.
*	@param len Tamano de la cadena.
*/
void ST_To_String( Station* this, char chain[], size_t len ){
	char color[10] = "";
	char neighbors[256] = "";

	ST_To_String_Neighbors( this, neighbors, len );

	switch( this->color ){
		case BLACK: strcpy( color, "BLACK" ); break;
		case GRAY:  strcpy( color, "GRAY" ); break;
		case WHITE: strcpy( color, "WHITE" ); break;
	}

	snprintf( chain, len - 1,
		"Name: %s\n"
		"Color: %s\n"
		"Distance: %ld\n"
		"Predecesor: %s\n"
		"DTime %ld\n"
		"FTime %ld\n"
		"Neighbors: %s\n",
		this->name,
		color,
		this->distance,
		this->predecesor, 
		this->discoveryTime,
		this->finishTime,
		neighbors
	);
}

/**
 * @brief Imprime en consola un objeto Station.
 * @param this referencia a la estacion a imprir.
 */
void ST_Print( Station* this ){ 
	char str[256];
	ST_To_String( this, str, 256 );
	printf( "%s\n", str ); 
}