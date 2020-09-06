#include "LWDL_Tools.h"
 


int LWDL_TOOL_length(LWDL_string str){ 
	int size = 0;
	while (str[size] != '\0'){
		size++;
	}

	if (str[size] == '\0'){
		return size;

	}

}


int LWDL_TOOL_characterExist(LWDL_string str,char character){
	int exists = 0; 
	for (int i=0;i<LWDL_TOOL_length(str);i++){
		if (str[i] == character){
			exists= 1;
		}

	}
	return exists;
}

int LWDL_TOOL_whereCharacterExist(LWDL_string str,char character){
	int exists = 0; 
	for (int i=0;i<LWDL_TOOL_length(str);i++){
		if (str[i] == character){
			exists = i;
		}

	}
	return exists;
}


LWDL_string LWDL_TOOL_AppendCharacters(LWDL_string P_CHAR, char CHARACTER)
{

   	size_t len = LWDL_TOOL_length(P_CHAR);
    LWDL_string str2 = malloc(len + 1 + 1 );  
    strcpy(str2, P_CHAR);
    str2[len] = CHARACTER; 
    str2[len + 1] = '\0';
    return str2;
}

int LWDL_TOOL_WordExists(LWDL_string str,  LWDL_string exist)
{

if (strstr(str,exist))
{
	return 1;
}

else
{
	return 0;
}


}



void LWDL_TOOL_INIT_ARRAY(LWDL_Array *a, int initialSize){
  a->array = malloc(initialSize * sizeof(LWDL_string));
  a->used = 0;
  a->size = initialSize;


}
void LWDL_TOOL_INSERT_ARRAY(LWDL_Array *a, LWDL_string element){
 if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(LWDL_string));
  }
  a->array[a->used++] = element;


}
void LWDL_TOOL_FREE_ARRAY(LWDL_Array *a){
	if (a->array != NULL){
  	free(a->array);
    a->array = NULL;
    a->used = a->size = 0;

	}

}


int LWDL_TOOL_ARRAY_whereCharacterExists(LWDL_Array* a, char character , int element){
 		for (unsigned int i=0;i < LWDL_TOOL_length(a->array[element]);i++){
 			if (a->array[element][i] == character){
 				return i;
 			}
 		} 		
 	 return -1;

}



void LWDL_TOOL_INIT_LIST_ARRAY(LWDL_LIST_Array *a, int initialSize){
  a->array = malloc(initialSize * sizeof(LWDL_Data_List));
  a->used = 0;
  a->size = initialSize;

	
}
void LWDL_TOOL_INSERT_LIST_ARRAY(LWDL_LIST_Array *a, LWDL_Data_List element){

 if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(LWDL_Data_List));
  }
  a->array[a->used++] = element;


}
void LWDL_TOOL_FREE_LIST_ARRAY(LWDL_LIST_Array *a){
	if (a->array != NULL){
  	free(a->array);
    a->array = NULL;
    a->used = a->size = 0;

	}


}
