#ifndef LWDL_TOOLS_H
#define LWDL_TOOLS_H
/* C Compiler items: */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LWDL_bool short int
#define LWDL_false 0
#define LWDL_true 1


typedef char* LWDL_string;
int LWDL_TOOL_characterExist(LWDL_string str,char character);
int LWDL_TOOL_length(LWDL_string str);
LWDL_string LWDL_TOOL_AppendCharacters(LWDL_string P_CHAR,char CHARACTER);
int LWDL_TOOL_WordExists(LWDL_string str,  LWDL_string exist);
int LWDL_TOOL_whereCharacterExist(LWDL_string str,char character);

/*
Dynamic Arrays: 

*/
struct LWDL_Array{
	LWDL_string* array;
	size_t used;
	size_t size;

};  typedef struct LWDL_Array LWDL_Array;

void LWDL_TOOL_INIT_ARRAY(LWDL_Array *a, int initialSize);
void LWDL_TOOL_INSERT_ARRAY(LWDL_Array *a, LWDL_string element);
void LWDL_TOOL_FREE_ARRAY(LWDL_Array *a);



struct LWDL_Data_List {
LWDL_string list_name; // list name (list (temp_list))
LWDL_Array list_values; // list value       ( x : (40) )
LWDL_Array list_values_name; // list name    ((x) : 40)
}; typedef struct LWDL_Data_List LWDL_Data_List;

struct LWDL_LIST_Array {
	LWDL_Data_List* array; // we will have our arrays.
 	size_t used;
	size_t size;
	int list_count;
	
}; typedef struct LWDL_LIST_Array LWDL_LIST_Array;

void LWDL_TOOL_INIT_LIST_ARRAY(LWDL_LIST_Array *a, int initialSize);
void LWDL_TOOL_INSERT_LIST_ARRAY(LWDL_LIST_Array *a, LWDL_Data_List element);
void LWDL_TOOL_FREE_LIST_ARRAY(LWDL_LIST_Array *a);


int LWDL_TOOL_ARRAY_whereCharacterExists(LWDL_Array* a, char character , int element);

 
#endif