#ifndef  DLL_INC
#define  DLL_INC

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "Station.h"

typedef void* Item;

/**
 * @brief declaramos un tipo Abtsracto denominado Node que servira como nodo para ir 
 * insertando en nuestras DLL(Listas DOblemente Enlazadas).
 * Entre sus atributos se encuentra Item el cual se puede adaptar al tipo abstracto, tipo primitivo, etc. con 
 * el que se encuentre, esto nos sera muy util para guardar nuestros tipos abstractos.
 * Tambien tendra entre sus atributos Nodes denomidados next y prev, los
 * cuales guardaran la direccion de los nodos que le siguen o que se encuentran antes
 * de el.
 * 
 */
typedef struct Node
{
	Item info;

	struct Node* next;
	struct Node* prev;
} Node;

/**
 * @brief declaramos un tipo Abstracto denominado DLL (Lista Doblemente Enlazada) que
 * estara compuesta por Nodes.
 * Entre sus atributos se encuentra:
 * - 3 Nodes donde:
 * -first y last se encargaran de indicarnos
 * los extremos de nuestra DLL, de lo contraria perderiamos todo control sobre nuestra
 * DLL y perderiamos la memoria en bano sin posibilidad de interactuar con la DLL.
 * -Un Node cursor que es libre de moverse por toda la DLL
 * y un size_t len que nos servira para saber cuantos elementos tenemos en nuestra 
 * DLL.
 */
typedef struct DLL
{
	Node*  first;
	Node*  last;
	Node*  cursor;
	size_t len;
} DLL;

/**
 * @brief Es nuestro constructor del tipo abstracto DLL, el cual se encargara de pedirle
 * memoria prestada para el uso de un DLL.  
 * 
 * @return DLL* regresa un Tipo Abstracto DLL listo para usarse.
 */
DLL*   DLL_New();

/**
 * @brief Destructor de DLLs, se encarga de eliminar y vacial las DLL y regresar su
 * memoria para evitar fugas de memoria. Por esta razon es muy importante.
 * 
 * @param this Referencia a un tipo Abstracto DLL el cual sera eliminado y liberada su
 * memoria. 
 */
void   DLL_Delete(      DLL* this );

/**
 * @brief Funcion encargada de Insertar la informacion a un DLL, sin importar si son
 * objetos, tipos abstractos, etc. esto gracias a void* que en este caso lo conocemos como Item.
 * 
 * @param this Referencia a una DLL a la cual se le insertara la informacion, objeto, tipo abstracto, etc.
 * @param value Referecia a la informacion u tipo primitivo, tipo abstracto, etc. que se guardara en nuestra DLL.
 * @return true si la operacion se realizo con exito. 
 * @return false si la operacion no se realizo con exito.
 */
bool   DLL_InsertBack(  DLL* this, Item value );

/**
 * @brief Funcion que se encarga de extraer la informacion de nuestra DLL (Lista Doblemente Enlazada)
 * 
 * @param this Referencia a nuestra DLL a procesar.
 * @param value Refrencia a un tipo primitivo, tipo abstracto, etc. al cual se le asignara la informacion recuperada.
 * @return true Si la operacion se realizo con exito.
 * @return false Si la operacion NO se realizo con exito.
 */
bool   DLL_RemoveFront( DLL* this, Item* value );

/**
 * @brief Funcion encargada de extraer la informacion de nuestra DLL (Lista Doblemente Enlazada)
 * de un nodo en especifico, aqui se ara uso de cursor.
 * 
 * @param this Referencia a Nuestra DLL a procesar.
 * @param value Referencia a un tipo primitivo, tipo abstracto, etc. al cual se le asignara la informacion recuperada.
 * @return true Si la operacion se realizo con exito.
 * @return false Si la operacion NO se realizo con exito.
 */
bool   DLL_RemoveNode(  DLL* this, Item value);

/**
 * @brief Funcion encargada de recuperar mas no extraer informacion de nuestra DLL (Lista Doblemente Enlazada)
 * del nodo al que este apuntando nuestro first.
 * 
 * @param this Referencia a nuestra DLL a procesar.
 * @param value Referencia a un tipo primitivo, tipo abstracto, etc. donde se guadara la informacion encontrada en 
 * el nodo al que apunta nuestro first.
 * @return true Si la operacion se realizo con exito.
 * @return false Si la operacion NO se realizo con exito.
 */
bool   DLL_Peek(        DLL* this, Item* value );

/**
 * @brief Funcion encargada de preguntar si nuestra DLL (Lista Doblemente Enlazada) se 
 * encuentra basia gracias al atributo len.
 * 
 * @param this Referencia a nuestra DLL a procesar.
 * @return true Si la DLL se encuentra vacia.
 * @return false Si la DLL NO se encuentra vacia.
 */
bool   DLL_IsEmpty (    DLL* this);

/**
 * @brief Funcion encargada de pasar por toda la DLL (Lista Doblemente Enlazada) en busca de
 * algun nodo que contenga la info que se busca y se indique.
 * 
 * @param this Referencia a nuestra DLL a procesar.
 * @param value Referencia a un tipo primitivo, tipo abstracto, etc. donde se encuentra la info a buscar.
 * @return true Si se encontro algun nodo con la misma informacion. 
 * @return false Si No se encontro algun nodo con la misma informacion.
 */
bool   DLL_IsOnList  (  DLL* this, Item value );

/**
 * @brief Funcion encargada de Limpiar nuestra DLL (Lista Doblemente Enlazada).
 * 
 * @param this Referencia a nuestra DLL a procesar.
 */
void   DLL_Purge(       DLL* this );

/**
 * @brief Funcion encargada de regresar el numero exacto de Nodes guardados en nuestra DLL
 * (Lista Doblemente Enlazada). 
 * 
 * @param this Referencia a nuestra DLL a procesar.
 * @return size_t regresa el numero de elementos en nuestra DLL.
 */
size_t DLL_Len(         DLL* this );

/**
 * @brief Funcion encargada de extraer todos nuestros Items info de nuestros Nodes en la 
 * DLL (Lista Doblemente Enlazada) en un arreglo el cual se puede concatenar.
 * 
 * @param this Referencia a nuestra DLL a procesar.
 * @param ptrArr Referencia a un Arreglo void* el cual puede representar cualquier tipo primivito, abstracto, etc.
 * con el que se concatene despues.
 */
void   DLL_GetInformation( DLL* this, void* ptrArr[] );

#endif   /* ----- #ifndef DLL_INC  ----- */