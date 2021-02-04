#include "DLL.h"

//================================================================
//==================={  Funciones Privadas }======================
//================================================================

/**
 * @brief Funcion Privada de DLL.c encargado de crear Nodes con la informacion que se le
 * pase, ya sean tipos primitivos, abstractos, etc.
 * 
 * @param value la informacion, tipo primitivo, abstracto a guardar en nuestro Node.
 * @return Node* Regresa un nodo listo para insertarse en nuestra DLL (Lista Doblemente Enlazada).
 */
static Node* newNode( Item value )
{
	Node* n = ( Node* ) malloc( sizeof ( Node ) );
	if( NULL != n ) {
		n->info = value;
		n->next = NULL;
		n->prev = NULL;
	}

	return n;
}

/**
 * @brief Funcion encargada de recorrer toda nuestra DLL (Lista Doblemente Enlazada)
 * en busca de algun nodo que tenga la misma informacion que se indica.
 * 
 * @param this Referencia a Nuestra DLL a procesar.
 * @param value Referencia a nuestro objeto, tipo primitivo, abstracto, etc. a buscar.
 * @return Node* Regresa el Node con una coincidencia.
 */
Node* findNode (  DLL* this, Item value ){
	assert( this );
	if( DLL_IsEmpty( this ) ) { return NULL; }	
	Node* tmp = this->first;
	for( size_t i = 0; i < DLL_Len( this ); ++i ){
		if( value == tmp->info ){
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

//================================================================
//==================={  Funciones Publicas }======================
//================================================================

DLL* DLL_New()
{
	DLL* p = ( DLL* ) malloc( sizeof( DLL ) );
	if( NULL != p ) {
		p->first = NULL;
		p->last = NULL;
		p->len = 0;
	}

	return p;
}

void DLL_Delete( DLL* this )
{
	assert( this );

	while( this->first != NULL ) {
		Node* tmp = this->first->next;
		free( this->first );
		this->first = tmp;
	}

	free( this );
	this = NULL;
}

bool DLL_InsertBack( DLL* this, Item value )
{
	assert (this);

	Node* n = newNode( value );
	if( n == NULL ) { return false;	}

	if( this->first == NULL ){
		this->first = n;
		this->last = n;
	}
	else {
		this->last->next = n;
		n->prev = this->last;
		this->last = n;
	}

	++this->len;

	return true;
}


bool DLL_RemoveFront( DLL* this, Item* value )
{
	assert( this );

	if( NULL == this->first ) return false;

	*value = this->first->info;

	if( this->first == this->last ){
		free( this->first );
		this->first = NULL;
		this->last = NULL;
	}
	else{
		Node* tmp = this->first->next;
		free( this->first );
		this->first = tmp;
		this->first->prev = NULL;
	}
	--this->len;

	return true;
}

bool   DLL_IsOnList  (  DLL* this, Item value )
{
	assert( this );
	if( DLL_IsEmpty( this ) ) { return false ; }	
	Node* tmp = this->first;
	for( size_t i = 0; i < DLL_Len( this ); ++i ){
		if( value == tmp->info )
			return true;
		tmp = tmp->next;
	}
	return false;
}

bool DLL_RemoveNode(  DLL* this, Item value)
{
	assert( this );
	if( DLL_IsOnList( this, value ) ){
		Node* n = findNode( this, value );

		if( n != NULL ){
			Node* tmp1 = n->prev; 
			Node* tmp2 = n->next;

			free( n );

			if( tmp1 != NULL )
				tmp1->next = tmp2;

			if( tmp2 != NULL )
				tmp2->prev = tmp1;

			--this->len;

			return true;
		}
	}
	return false;
}

bool DLL_IsEmpty (DLL* this)
{
	assert( this );

	return this->first == NULL ? true : false;
}

void DLL_Purge( DLL* this )
{
	assert( this );

	if( DLL_IsEmpty( this ) ) { return; }

	while( this->first != NULL ){
		Node* tmp = this->first->next;
		free( this->first );
		this->first = tmp;
	}

	this->len = 0;
}

size_t DLL_Len( DLL* this )
{
	return this->len;
}

bool DLL_Peek( DLL* this, Item* value )
{
	assert( this );

	if( NULL == this->first ) return false;

	*value = this->first->info;
	return true;
}

void DLL_GetInformation( DLL* this, void* ptrArr[] ){
	assert( this );
	if( DLL_IsEmpty( this ) ) { return; }	
	Node* tmp = this->first;
	for( size_t i = 0; i < DLL_Len( this ); ++i ){
		ptrArr[ i ] = tmp->info;
		tmp = tmp->next;
	}
}