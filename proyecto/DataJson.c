/**
 * @file DataJson.c
 * @brief Se encarga de ejecutar Metodos relacionados con el tipo Abstracto denominado
 * DataJson.
 * @version 0.1
 * @date 2021-02-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
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
