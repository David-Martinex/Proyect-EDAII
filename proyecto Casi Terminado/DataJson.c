#include "DataJson.h"

/**=============================================================== 
 * ======================{ METODOS PÚBLICOS }=====================
 * ===============================================================*/

DataJson* DataJson_New()
{
    DataJson* db = ( DataJson* )malloc( sizeof( DataJson ) );

    if( db != NULL ){
        FILE *fp = fopen("test.json", "r");

        if( fp != NULL ){
            fread( db->buffer, 1024, 1, fp );
            fclose( fp );

            return db;
        }
        printf( "\n==>No se pudo abrir el archivo\n");
    }else{
        printf("\n==>!! Error ¡¡\n=>No se pudo crear el Objeto.");
    }

    return db;
}

void DataJson_Delete( DataJson* file ) 
{
    assert( file );
    free( file );
}

/**
 * @brief función encargada de serializar las estaciones y las rutas en un 
 * archivo .json.
 * 
 * @param stations referencia a un puntero de stations. 
 * @param n_stations número de estaciones (stations).
 * @param roots referenacia a un puntero de roots. 
 * @param n_roots número de rutas (roots).
 */
void DataJson_Serialize( void** stations, size_t n_stations, void** roots, size_t n_roots )
{
    Station** stationsList = (Station **) stations;
    Roots** rootsList = (Roots **) roots;

    FILE *fp = fopen("test.json", "w");

    fputs("{\n", fp);

    fputs("   \"Estaciones\" : [", fp);
    //un ciclo para guardar todas las estaciones.
    for (size_t i = 0; i < n_stations; i++) {
        fputs("\"", fp);
        fputs(stationsList[i]->name, fp);
        fputs(i == n_stations-1 ? "\"" : "\", ", fp);
    }

    fputs("],\n   \"Rutas\" : [\n", fp);
    //Un ciclo que guarde todas las rutas.
    for (size_t i = 0; i < n_roots; i += 2) {
        fputs("        {\"origen\" : \"", fp);
        fputs(rootsList[i]->first->name, fp);
        fputs("\", \"destino\" : \"", fp);
        fputs(rootsList[i]->last->name, fp);
        fputs("\", \"minutos\" : \"", fp);
        fprintf(fp, "%ld", rootsList[i]->weight);
        fputs(i == n_roots-2 ? "\"}\n" : "\"},\n", fp);
    }

    fputs("   ]", fp);
    fputs("\n}", fp);
    fclose( fp );
}

void DataJson_Deserialize( DataJson* file, DLL* stations, DLL* roots )
{
    struct json_object *parsed_json;
    struct json_object *estaciones;
    struct json_object *estacion;
    
    struct json_object *rutas;
    struct json_object *ruta;
    struct json_object *origen;
    struct json_object *destino;
    struct json_object *minutos;

    parsed_json = json_tokener_parse( file->buffer );
    json_object_object_get_ex( parsed_json,"Estaciones", &estaciones);

    size_t n_estaciones = json_object_array_length( estaciones );
    void* StationLis[ n_estaciones ];
    for(size_t i = 0; i < n_estaciones; ++i ){

        estacion = json_object_array_get_idx( estaciones, i );
        char name1[10];
        strcpy( name1, json_object_get_string( estacion ));

        Station* c = Station_New( name1 );
        StationLis[ i ] = c;
        //DLL_InsertBack( stations, c );
    }

    json_object_object_get_ex( parsed_json, "Rutas", &rutas );

    size_t n_rutas = json_object_array_length( rutas );

    void* RootsList[ n_rutas ];

    char route[256];
    for(size_t j = 0; j < n_rutas; ++j ){
        ruta = json_object_array_get_idx( rutas, j );

        strcpy( route, json_object_get_string( ruta) );

        struct json_object *saves;

        saves = json_tokener_parse( route );

        json_object_object_get_ex(saves, "origen", &origen );
        json_object_object_get_ex(saves, "destino", &destino );
        json_object_object_get_ex(saves, "minutos", &minutos );
        int weight = json_object_get_int( minutos );

        char name1[10], name2[10];
        strcpy(name1, json_object_get_string( origen ) );
        strcpy(name2, json_object_get_string( destino ) );

        Station* tmp1 = Station_New( name1 );
        Station* tmp2 = Station_New( name2 );

        Roots* a = Roots_New( tmp1, tmp2, weight );
        DLL_InsertBack( roots, a);
        RootsList[ j ] = a;
    }
    printf("\nBandera\n");
    DataJson_Add_neigbors( stations, roots );
}

void DataJson_Add_neigbors( DLL* stations, DLL* roots)
{
    size_t NumStat = DLL_Len( stations );
    void* ArrayStat[ NumStat ];

    DLL_GetInformation( stations, ArrayStat );

    size_t NumRoos = DLL_Len( roots );
    void* ArrayRoos[ NumRoos ];

    DLL_GetInformation( roots, ArrayRoos );

    for(size_t i = 0; i < NumStat ; ++i ){
        Station* c = ( Station* )ArrayStat[ i ];
        for( size_t j = 0; j < NumRoos; ++j ){
            Roots* a = ( Roots* )ArrayRoos[ j ];
            if( strcmp( c->name, a->first->name) == 0 ){
                printf("[%s, vecino: %s],", c->name, a->last->name );
                ST_Add_Neighbor( ArrayStat[ i ] , a->last );
            }
            //Roots_Delete( a );
        }
        ArrayStat[ i ] = c;
        //Station_Delete( c );
    }

    DLL_Purge( stations );
    for( size_t k = 0; k < NumStat; ++k ){
        DLL_InsertBack( stations, ( Station* )ArrayStat[ k ] );
    }
    //DLL_Delete( tmp );
    
}