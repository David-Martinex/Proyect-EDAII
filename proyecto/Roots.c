#include "Roots.h"

/**
*	@brief Constructor de la clase Roots.
*	@param firts Referencia a un objeto Station.
*	@param last Referencia a un objeto Station.
*	@param weight Costo de movimiento entre dos tipos Station.
*	@return Referencia aun objeto Roots.
*/
Roots* Roots_New( Station* first, Station* last, size_t weight)
{
	Roots* a = ( Roots* )malloc( sizeof( Roots ) );

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
void Ro_To_String( Roots* this, char str[], size_t len )
{
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
void Ro_Print( Roots* this ){ 
	char str[256];
	Ro_To_String( this, str, 256 );
	printf( "%s\n", str ); 
}

/**
*	@brief Destructor de la clase Axis.
*	@param this Referencia a un objeto Axis.
*/
void Roots_Delete( Roots* this ){
	assert( this );
	free( this );
}
