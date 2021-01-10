#include "DataBase.h"

/**
*  @brief Salva los datos de los vecinos de una ciudad.
*  @param this Referencia a DataBase.
*  @param c Referencia a un objeto City.
*  @param axis Referencia a una DLL de tipos Axis.
*/
void neighborsSave( DataBase* this, City* c, DLL* axis ){
	size_t listLen = DLL_Len( c->neighbors );

	void* nodesList[ listLen ];

	DLL_GetInformation( c->neighbors, nodesList );

	for( size_t i = 0; i < listLen; i++ ){
		City* n = ( City* )nodesList[ i ];

      size_t nLen = DLL_Len( axis );
      void* aList[ nLen ];

      DLL_GetInformation( axis, aList );

      Axis* a = NULL;

      for( size_t j = 0; j < nLen; j++ ){
         Axis* aTmp = ( Axis* )aList[ j ];

         City* o = aTmp->first;
         City* d = aTmp->last;

         if( strcmp( c->name, o->name ) == 0 && strcmp( n->name, d->name) == 0){ 
            a = aTmp;
         }

      }

		char chain[ 256 ] = "";

      char str[ 12 ];

      sprintf(str, "%ld", a->weight);


		strcat( chain, "INSERT INTO axis ( origen, destino, peso ) VALUES  ( '" );
		strcat( chain, c->name );
		strcat( chain, "' , '" );
		strcat( chain, n->name );
      strcat( chain, "' , '" );
      strcat( chain, str );
		strcat( chain, "' );" );

		char* sql = &chain[0];

		char* err_msg = NULL;

		int rc = sqlite3_exec( this->dataBase, sql, NULL, 0, &err_msg );

   		if( rc != SQLITE_OK ){
      		fprintf( stderr, "SQL error: %s\n", err_msg );
      		sqlite3_free( err_msg );
   		} else{
	      	fprintf( stdout, "[axis] Data has been inserted!\n" );
   		}

	}
}

/**
*	@brief Recorre una la lista de nodos para guardarlos en la DB.
*	@param this Referencia a el objeto DataBase.
*	@param dll Referencia a una DLL.
*/
void nodesSave( DataBase* this, DLL* dll, DLL* axis ){
	size_t listLen = DLL_Len( dll );
	void* nodesList[ listLen ];

	DLL_GetInformation( dll, nodesList );

	for( size_t i = 0; i < listLen; i++ ){
		City* c = ( City* )nodesList[ i ];

		char chain[ 256 ] = "";

		strcat( chain, "INSERT INTO cities ( name ) VALUES  ( '" );
		strcat( chain, c->name );
		strcat( chain, "');" );

		char* sql = &chain[0];

		char* err_msg = NULL;

   		int rc = sqlite3_exec( this->dataBase, sql, NULL, 0, &err_msg );

   		if( rc != SQLITE_OK ){
      		fprintf( stderr, "SQL error: %s\n", err_msg );
      		sqlite3_free( err_msg );
   		} else{
	      	fprintf( stdout, "[cities] Data has been inserted!\n" );
   		}

   		neighborsSave( this, c, axis );
	}
}

/**
 * @brief Callback para las consultas (query)
 *
 * @param data Campo de uso para el usuario. El usuario la usa como quiera.
 * @param argc Número de columnas encontradas
 * @param argv Valor (como texto) de cada columna
 * @param col_name Nombre (en la base de datos) de cada columna
 *
 * @return 0: ok, !0: algún error
 */
int callback_node( void* data, int argc, char** argv, char** col_name )
{
   	DLL* dll = ( DLL* )data;


   	for( int i = 0; i < argc; ++i ){
      	City* c = City_New( argv[ i ] );
      	DLL_InsertBack( dll, c );
   	}
   	printf( "\n" );
   	return 0;
}

/**
 * @brief Callback para las consultas (query)
 *
 * @param data Campo de uso para el usuario. El usuario la usa como quiera.
 * @param argc Número de columnas encontradas
 * @param argv Valor (como texto) de cada columna
 * @param col_name Nombre (en la base de datos) de cada columna
 *
 * @return 0: ok, !0: algún error
 */
int callback_neighbors( void* data, int argc, char** argv, char** col_name )
{
	DLL* dll = ( DLL* )data;

	size_t listLen = DLL_Len( dll );
	void* nodesList[ listLen ];

	DLL_GetInformation( dll, nodesList );

   City* c = NULL;

   for( size_t i = 0; i < listLen; ++i ){
      City* tmpC = ( City* )nodesList[ i ];
      if( strcmp( tmpC->name, argv[ 0 ] ) == 0 )
         c = tmpC;
   }

   for( size_t i = 1; i < argc; ++i ){
      for( size_t j = 0; j < listLen; ++j ){
         City* n = ( City* )nodesList[ j ];
         if( strcmp( n->name, argv[ i ] ) == 0 ){
            CT_Add_Neighbor( c, n );
         }
      }
   }
   printf( "\n" );
   return 0;
}

/**
 * @brief Callback para las consultas (query)
 *
 * @param data Campo de uso para el usuario. El usuario la usa como quiera.
 * @param argc Número de columnas encontradas
 * @param argv Valor (como texto) de cada columna
 * @param col_name Nombre (en la base de datos) de cada columna
 *
 * @return 0: ok, !0: algún error
 */
int callback_weight(  void* data, int argc, char** argv, char** col_name ){
   size_t* weight = ( size_t* )data;

   for (int i = 0; i < argc; ++i)
   {
      printf( "%s = %s\n", col_name[ i ], argv[ i ] ? argv[ i ] : "NULL" );
   }

   *weight = atoi( argv[ 0 ] );

   return 0;
}




/**
*	@brief Inicializa la clase, recuperará datos preexistentes en caso de haber.
*	@return Apuntador a un objeto.
*/
DataBase* DataBase_New(){
	DataBase* db = ( DataBase* )malloc( sizeof( DataBase ) );

	db->dataBase = NULL;

	int rc = sqlite3_open( "./dataBase/dataBase.sqlite3", &( db->dataBase ) );

	if( rc ){
		fprintf(stderr, "Can't open data base [dataBase]: %s\n", sqlite3_errmsg( db->dataBase ) );
		db = NULL;
		return db;
	}else
		fprintf(stderr, "Opened data base [dataBase] successfully\n" );
	return db;
}

/**
*	@brief Destructor del objeto DataBase.
*	@param Referencia a un objeto DataBase,
*/
void DataBase_Delete( DataBase* this ){
	assert( this );

	if( this->dataBase != NULL ){
		sqlite3_close( this->dataBase );
		fprintf(stderr, "Closed data base [dataBase] successfully\n" );
	}

	free( this );
}

/**
*	@brief Salva la informacion de los vertices en su repectiva BD.
*	@param this Referencia a la base de datos.
*	@param dll Referencia a una DLL con las ciudades a guardar.
*	@return true Si se ha salvado informacion con éxito
*/
bool DB_Save_Information( DataBase* this, DLL* dll, DLL* axis ){
	char* sql ="CREATE TABLE cities( " 
               "name TEXT PRIMARY KEY NOT NULL ); "
               
               "CREATE TABLE axis ("
               "origen TEXT NOT NULL, "
               "destino TEXT NOT NULL, "
               "peso INTEGER NOT NULL, "
               "PRIMARY KEY ( origen, destino ) );"
               ; // cierra a '='

   	char* err_msg = NULL;

   	int rc = sqlite3_exec( this->dataBase, sql, NULL, 0, &err_msg );

   	if( rc != SQLITE_OK ){
      	fprintf( stderr, "SQL error: %s\n", err_msg );
      	sqlite3_free( err_msg );
   	} else{
      	fprintf( stdout, "Tabla creada!\n" );
   	}
   	nodesSave( this, dll, axis );

	return true;
}

/**
*	@brief Recobra información y la guarda en una DLL. En caso de estar vaciá
*	la BD el la DLL apuntara a NULL
*	@param this Referencia a un objeto DataBase.
*	@param dll Referencia a una DLL donde se guardaran vértices recuperados.
*	@return true Si se recuperó con éxito.
*/
bool DB_Recover_Information( DataBase* this, DLL* dll, DLL* axis ){
	
	char* sql = "SELECT * FROM cities;";

   	char* err_msg = NULL;

	int rc = sqlite3_exec( this->dataBase, sql, callback_node, (void*)dll, &err_msg );

   	if( rc != SQLITE_OK ){
      	fprintf( stderr, "SQL error: %s\n", err_msg );
      	sqlite3_free( err_msg );
   	} else{ fprintf( stdout, "[cities] Data has been recovered!\n" ); }


   	size_t listLen = DLL_Len( dll );
   	void* nodesList[ listLen ];

   	DLL_GetInformation( dll, nodesList );

   	for( size_t i = 0; i < listLen; i++ ){
   		City* c = ( City* )nodesList[ i ];

   		char chain[ 256 ] = "";

	   	strcat( chain, "SELECT origen, destino FROM axis WHERE origen == '" );
   		strcat( chain, c->name );
   		strcat( chain, "';" );

   		sql = &chain[0];
   		err_msg = NULL;

   		rc = sqlite3_exec( this->dataBase, sql, callback_neighbors, (void*)dll, &err_msg );

   		if( rc != SQLITE_OK ){
      		fprintf( stderr, "SQL error: %s\n", err_msg );
      		sqlite3_free( err_msg );
   		} else{ fprintf( stdout, "[axis] Data has been recovered!\n" ); }


         size_t lenN = DLL_Len( c->neighbors );
         void* arrN[ lenN ];

         DLL_GetInformation( c->neighbors, arrN );

         for( size_t j = 0; j < lenN; j++ ){
            




            City* n = ( City* )arrN[ j ];

            printf("CIUDAD: %s\n",c->name );
            printf("VECINO: %s\n",n->name );

            size_t weight = 0;

            strcpy( chain, "" );
            err_msg = NULL;

            strcat( chain, "SELECT peso FROM axis WHERE origen == '" );
            strcat( chain, c->name );
            strcat( chain, "' AND destino == '" );
            strcat( chain, n->name );
            strcat( chain, "';" );   

            sql = &chain[0];

            rc = sqlite3_exec( this->dataBase, sql, callback_weight, (void*)&weight, &err_msg ); 

            if( rc != SQLITE_OK ){
               fprintf( stderr, "SQL error: %s\n", err_msg );
               sqlite3_free( err_msg );
            } else{ fprintf( stdout, "[axis-weight] Data has been recovered!\n" ); }

            if( weight != 0 ){
               

               Axis* a = Axis_New( c, n, weight);

               DLL_InsertBack( axis, a );

            }
         }



   	}


	return true;
}