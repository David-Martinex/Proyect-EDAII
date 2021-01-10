#include "Axis.h"


/**
*	@brief Constructor de la clase Axis.
*	@param firts Referencia a un objeto City.
*	@param last Referencia a un objeto City.
*	@param weight Costo de movimiento entre dos tipos City.
*	@return Referencia aun objeto Axis.
*/
Axis* Axis_New( City* first, City* last, size_t weight){
	Axis* a = ( Axis* )malloc( sizeof( Axis ) );

	a->first = first;
	a->last  = last;
	a->weight = weight;

	return a;
}

/**
*	@brief Imprime lista de ejes almacenados
*	@param this Referencia al objeto.
*	@param str Cadena donde se guardara la candena
*	@param len Tamagno de str view str.
*/
void Ax_To_String( Axis* this, char str[], size_t len ){
		snprintf( str, len - 1,
		"Origen: %s\n"
		"Destino: %s\n"
		"Peso: %ld\n",
		this->first->name,
		this->last ->name,
		this->weight
	);

}

/**
*	@brief Imprime en consola un objeto Axis.
*	@param this referencia a el eje a imprmir.
*/
void Ax_Print( Axis* this ){ 
	char str[256];
	Ax_To_String( this, str, 256 );
	printf( "%s\n", str ); 
}

/**
*	@brief Destructor de la clase Axis.
*	@param this Referencia a un objeto Axis.
*/
void Axis_Delete( Axis* this ){
	assert( this );
	free( this );
}

