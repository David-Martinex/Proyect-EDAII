/**
 * @file DataManager.c
 * @brief Modulo que se encarga de realizar todas las operaciones 
 * @version 0.1
 * @date 2021-02-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "DataManager.h"

/**=============================================================== 
 * ======================{ METODOS PRIVADOS }=====================
 * ===============================================================*/

/**
*	@brief Guarda la lista de ciudades en una base de datos SQL.
*	@param this Referecia a un objeto DataManager.
*	@return true Si se tuvo éxito al guardar.
*	@return false Si falló el guardado.
*/
bool save_Data( DataManager* this )
{
	bool result = false;
	bool DB_SQL = DB_Save_Information( this->dataBase, this->stations, this->roots /*Redefinir si es necesario*/ );
	if( DB_SQL == true ){
		result = true;
	}
	return result;
}

/**
*	@brief Carga ciudades guardadas en una base de datos SQL.
*	@param this Referencia a un objeto DataManager.
*	@return true Si se recupero con éxito la información.
*	@return false Si falló la recuperación.
*/
bool recover_Data( DataManager* this ){
	return DB_Recover_Information( this->dataBase, this->stations, this->roots );
}

/**
*	@brief Asigna la lista de vecinos de una tipo Station a su respectivo tipo roots.
*	@param this Referencia al objeto DataManager.
*/
void roots_Asigment( DataManager* this, Station* c1, Station* c2, size_t weight ){
	Roots* a = Roots_New( c1, c2, weight);
	DLL_InsertBack( this->roots, a );
}

/**=============================================================== 
 * ======================{ METODOS PUBLICOS }=====================
 * ===============================================================*/

/**
*	@brief Constructor del objeto DataManager, también carga la DB.
*	@return dm Referencia a el objeto DataManager.
*/
DataManager* DataManager_New()
{
	DataManager* dm = ( DataManager* )malloc( sizeof( DataManager ) );

	dm->dataBase = DataBase_New();
	dm->dataJson = DataJson_New();

	if( dm->stations == NULL )
		dm -> stations = DLL_New();

	if( dm->roots == NULL )
		dm -> roots = DLL_New();

	return dm;
}

/**
*	@brief Destructor del objeto DataManager, salva datos en DB antes 
*	de destruir al objeto.
*	@param this Referencia a un objeto DataManager.
*/
void DataManager_Delete( DataManager* this )
{
	assert( this );
	assert( this->dataBase );

	save_Data( this );

	size_t lenRoots = DLL_Len( this->roots );
	void* ptrRoots[ lenRoots ];

	DLL_GetInformation( this->roots, ptrRoots );

	for( size_t i = 0; i < lenRoots; ++i )
		Roots_Delete( ( Roots* )ptrRoots[ i ] );


	size_t len = DLL_Len( this->stations );
	void* ptrArr[ len ];

#if 1

	DLL_GetInformation( this->stations , ptrArr );

	for( size_t i = 0; i < len ; i++ )
		Station_Delete( ( Station* )ptrArr[ i ] );

	DataBase_Delete( this->dataBase );
	DataJson_Delete( this->dataJson );

	free( this );

#endif
}
/**
*	@brief Carga información previa de una DB.
*	@param this Referencia a un objeto DataManager.
*/
void DM_LoadInformation( DataManager* this ){ 	recover_Data( this ); }

/**
*	@brief Guarda la lista de direcciones de los vértices Station.
*	@param this Referencia al objeto DataManager.
*	@param ptrArr Referencia a la lista donde se guardaran direcciones,
*	debe tener el tamagno de numero de ciudades en DLL Stations. Usar método
*	DLL_Len() 	
*/
void DM_Get_StationList( DataManager* this, void* ptrArr[] ){ DLL_GetInformation( this->stations, ptrArr ); }

/**
*	@brief Imprime la lista de ciudades hasta el momento almacenadas en la DLL
*	Stations.
*	@param this Referencia al objeto DataManager.
*/
void DM_Print_StationsList( DataManager* this ){
	size_t dllSize = DLL_Len( this->stations ); 

	void* ptrArr[ dllSize ];
	DM_Get_StationList( this, ptrArr );

	for( size_t i = 0; i < dllSize; i++ ){
		ST_Print( ( Station* )ptrArr[ i ] );	
	}
}

/**
*	@brief Imprime la lista de roots almacenadas en su respectiva DLL.
*	@param this Referencia a una a un objeto DataManager.
*/
void DM_Print_RootsList( DataManager* this ){
	size_t rootsSize = DLL_Len( this->roots );

	void* ptrArr[ rootsSize ];

	DLL_GetInformation( this->roots, ptrArr );

	for( size_t i = 0; i < rootsSize; i++ ){
		Ro_Print( ( Roots* )ptrArr[ i ] );
	}

}

/**
*	@brief Agega un eje con direccion a la ciudad con name1 a la ciudad
*	con nombre name2, el metodo valida que las ciudades esten en la lista.
*	@param this Referencia a un objeto DataManager.
* 	@param name1 Nombre de la primer ciudad.
*	@param name2 Nombre de la segunda ciudad.
*	@return true Si se añadio con éxito.
*	@return false Si falló o no se encontraron las ciudades.
*/
bool DM_Add_Station( DataManager* this, char name[] ){
	Station* c = Station_New( name );
	return DLL_InsertBack( this->stations, c );
}

/**
*	@brief Busca una ciudad en la DLL Stations por su nombre.
*	@param name Nombre de la ciudad a buscar.
*	@param direction Apuntador a ciudad donde se guardara coincidencia de búsqueda
*	@return Referencia a una ciudad si la encontro, NULL en caso contrario.
*/
Station* DM_Find_Station( DataManager* this, char name[] ){
	size_t cLen = DLL_Len( this->stations );
	void* cList[ cLen ];

	DM_Get_StationList( this, cList );

	Station* c = NULL;

	for( size_t i = 0; i < cLen; ++i ){
		c = ( Station* )cList[ i ];
		if( strcmp( c->name, name ) == 0  )
			return c;
	}
	return c;
}

/**
*	@brief Agega un eje con direccion a la ciudad con name1 a la ciudad
*	con nombre name2, el metodo valida que las ciudades esten en la lista.
*	@param this Referencia a un objeto DataManager.
* 	@param name1 Nombre de la primer ciudad.
*	@param name2 Nombre de la segunda ciudad.
*	@return true Si se añadio con éxito.
*	@return false Si falló o no se encontraron las ciudades.
*/
bool DM_Add_StationRoots( DataManager* this, char name1[], char name2[], size_t weight ){
	Station* c1 = DM_Find_Station( this, name1 );
	Station* c2 = DM_Find_Station( this, name2 );
	if( c1 == NULL || c2 == NULL ){ return false; }

	ST_Add_Neighbor( c1, c2 );
	ST_Add_Neighbor( c2, c1 );

	roots_Asigment( this, c1, c2, weight );
	roots_Asigment( this, c2, c1, weight );

	return true;
}

/**
*	@brief Activa la busqueda de la mejor ruta utilizando un algorítmo dijkstra.
*	@param this Referencia a un objeto DataManager.
*	@param name1 Nombre de ciudad origen.
*	@param name2 Nombre de ciudad destino.
*	@param path Cadena donde se guardará la mejor ruta.
*	@param len Tama?o de path.s
*/
void DM_Obtain_Best_Path( DataManager* this, char name1[], char name2[], char path[], size_t len ){
	Station* o = DM_Find_Station( this, name1 );
	Station* d = DM_Find_Station( this, name2 );

	if( o != NULL && d != NULL )
		G_Best_Route( o, d, this->stations, this->roots, path, len);
	else
		printf("Sin coincidencia de busqueda!\n");
	
}
/**
 * @brief Activa la función para serializar, obteniendo primero las listas
 * de estaciones y rutas de la base de datos junto con el tamaño de cada una.
 * 
 * @param this Referencia a un objeto DataManager.
 */
void DM_Serialize( DataManager* this ){
    // Estaciones
    size_t dllSize = DLL_Len( this->stations );

    void* stationsList[ dllSize ];
    DM_Get_StationList( this, stationsList );

    // Rutas
    size_t rootsSize = DLL_Len( this->roots );

    void* rootsList[ rootsSize ];
    DLL_GetInformation( this->roots, rootsList );

    DataJson_Serialize(stationsList, dllSize, rootsList, rootsSize);
}