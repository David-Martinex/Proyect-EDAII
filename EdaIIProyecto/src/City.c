#include "City.h"

/**
*	@brief Crea un vértice de tipo City.
*	@return Referencia a un nuevo vértice.
*/
City* City_New( char name[] ){
	City* c = ( City* ) malloc( sizeof( City ) );

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
*	@brief Destructor del objeto City.
*	@param this Referencia al objeto a destruir.
*/
void City_Delete( City* this ){
	assert( this );
	assert( this->neighbors );

	free( this->neighbors );

	free( this );
}

/**
*	@brief Agrega una nueva ciudad vecina
*	@param this Referencia al vertice dode se agregara un nuevo vecino.
*	@param city Referencia a la ciudad a agregar.
*	@return true Si se ha añadido con éxito.
*	@return false Si no se añadio con éxico. 
*/
bool CT_Add_Neighbor( City* this, City* city ){ return DLL_InsertBack( this->neighbors, city ); }

/**
*	@brief Setter del atributo distance.
*	@param this Referencia a l objeto.
*	@param distance Valor a insertar.
*/
void CT_Set_Distance( City* this, int distance ){ this->distance = distance; }

/**
*	@brief Setter del atributo color.
*	@param this Referencia a l objeto.
*	@param color Valor a insertar.
*/
void CT_Set_Color( City* this, int color ){ this->color = color; }

/**
*	@brief Setter del atributo predecesor.
*	@param this Referencia a l objeto.
*	@param predecesor Valor a insertar.
*/
void CT_Set_Predecesor( City* this, char predecesor[] ){ strcpy( this->predecesor, predecesor ); }

/**
*	@brief Setter del atributo discoveryTime.
*	@param this Referencia a l objeto.
*	@param discoveryTime Valor a insertar.
*/
void CT_Set_DiscoveryTime( City* this, size_t discoveryTime ){ this->discoveryTime = discoveryTime; }

/**
*	@brief Setter del atributo finishTime.
*	@param this Referencia a l objeto.
*	@param finishTime Valor a insertar.
*/
void CT_Set_FinishTime( City* this, size_t finishTime ){ this->finishTime = finishTime; }

/**
*	@brief Imprime lista de vecinos recuperando su direcicon de memoria
*	@param this Referencia al objeto.
*	@param str Cadena donde se guardara la candena
*	@param len Tamagno de str view str.
*/
void CT_To_String_Neighbors( City* this, char str[], size_t len ){
	size_t lenNeighbors = DLL_Len( this->neighbors );
	if(  lenNeighbors == 0 ) { 
		str = "";
		return; 
	}

	void* ptrArr[ lenNeighbors ];
	char name[64] = "";
	DLL_GetInformation( this->neighbors, ptrArr );

	for( size_t i = 0; i < lenNeighbors; ++i){
		City* c = ( City* )ptrArr[i];
		strcat( name, c->name );
		strcat( name, "->" );
		
	}

	snprintf( str, len - 1, "%s", name );

}

/**
*	@brief Convierte un objeto a cadena de texto.
*	@param this Referencia a la ciudad a convertir.
*	@param chain Arreglo donde se guardara el formato de texto.
*	@param len Tamano de la cadena.
*/
void CT_To_String( City* this, char chain[], size_t len ){
	char color[10] = "";
	char neighbors[256] = "";

	CT_To_String_Neighbors( this, neighbors, 256 );

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
*	@brief Imprime en consola un objeto City.
*	@param this referencia a la ciudad a imprir.
*/
void CT_Print( City* this ){ 
	char str[256];
	CT_To_String( this, str, 256 );
	printf( "%s\n", str ); 
}