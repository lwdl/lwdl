#ifndef LWDL_PARSER_H
#define LWDL_PARSER_H

/* LWDL items */ 
#include "LWDL_Tools.h"

/*
LWDL DEVELOPERS:
LWDL SCRIPTING LANGUAGE.
This file is used to include everything for the lwdl file. 
*/


/*  
LWDL FAILURE - Used if the file has not been open , or any error has occured.
LWDL_SUCCESS - Used if the file has been open, or no error has occured. 

[Aim]	Generally you should be aiming for LWDL_SUCCESS.



*/

#define LWDL_FAILURE 1 
#define LWDL_SUCCESS 0
typedef short int LWDL_STATUS;




/* 
LWDL_STATE 
used for storing the files name , file pointer, and status.
*/

struct LWDL_State {
	const char* file_name;	
	FILE* LWDL_File;
 	LWDL_STATUS status;
}; typedef struct LWDL_State LWDL_State;

/* 
LWDL_OPEN
opens file the file and stores all the data into LWDL_STATE.

STATUS:
if the LWDL_State::status equals to LWDL FAILURE, that means that there has been a error opening a file.
most errors return a error message printed onto the console.
*/
LWDL_State LWDL_Open(const char* file_name);

// LWDL_Data stores any data from the LWDL_Parse(data,state) function.


struct LWDL_Data {
    LWDL_LIST_Array list_array;
	int lwdl_data_size;

}; typedef struct LWDL_Data LWDL_Data;




// LWDL_Parse function tokenizes and stores correct syntax onto LWDL_Data.
void LWDL_Parse(LWDL_Data* data, LWDL_State state);

/*
LWDL_CLOSE(state):
frees up or closes any pointed in state.

*/
void LWDL_Close(LWDL_Data* data );
 

 // Return Types Lwdl
LWDL_string LWDL_getString(LWDL_Data data,LWDL_string list_name , LWDL_string value_name );
int LWDL_getInt           (LWDL_Data data,LWDL_string list_name , LWDL_string value_name );
 float LWDL_getFloat       (LWDL_Data data,LWDL_string list_name , LWDL_string value_name );


/*
This prints your data, in your LWDL file.
(the name says it all duh!)
*/
void LWDL_PrintData(LWDL_Data data);

#endif