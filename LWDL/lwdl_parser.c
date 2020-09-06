#include "lwdl_parser.h"

LWDL_State LWDL_Open(const char *file_name)
{
    LWDL_State temp;
    temp.file_name = file_name;
    temp.LWDL_File = fopen(temp.file_name, "r"); /*allow for reading */
    if (temp.LWDL_File == NULL)
    {
    	// failed to recieve the file. will occur in a empty temp.
        perror("[LDWL_ERROR] : Failed to open file.[REASON] :");
        temp.status = LWDL_FAILURE;
    }
    else if (temp.LWDL_File != NULL)
    {
        /*Succesfully fetched file. */
        temp.status = LWDL_SUCCESS;
    }
    return temp;

}
// we'll return LWDL_Data
void LWDL_Parse(LWDL_Data* data, LWDL_State state)
{
    char ch; 
    LWDL_string contents; // this is defined to remove the bug that deletes the first line of the code.
    LWDL_string chunks; // chunks are used to parse the tokens.
    LWDL_Array tokens; // this array will be used to store the tokens within the file.
    const char remove[4] = "	 \n"; 
    LWDL_TOOL_INIT_LIST_ARRAY(&data->list_array , 5);
    LWDL_TOOL_INIT_ARRAY(&tokens, 1);	// 5  is starting size. 
    LWDL_TOOL_INIT_LIST_ARRAY(&data->list_array,5);

    while ((ch = fgetc(state.LWDL_File)) != EOF)
    {
        contents = LWDL_TOOL_AppendCharacters(contents, ch); // Visit LWDLTOOL (name explains it)
    }

    chunks = strtok(contents, remove); // token
    while (chunks != NULL)
    {
       
            LWDL_TOOL_INSERT_ARRAY(&tokens, chunks); // we insert a array from chunks
         
        chunks = strtok(NULL, remove);

    }


    /* Parser, this uses the tokenized values,
    and stores them into the data arguments.
    afterwards, the user can fetch the data, converted , changed
    This parser also is a error.  */ 
    int ret = 0; // this is a int that is used for comparing ints using strcmp.
    LWDL_bool inScope = LWDL_false;
    int read_list_scope_pos =0 ;
     
    for (int i = 0; i < tokens.used; i++)
    {
        if ((ret = strcmp(tokens.array[i], "list")) == 0)
        {
            
            if ((ret = strcmp(tokens.array[i + 1], "{")) == 0){
        		printf("[ERROR]::(%s) list cannot have a name of a {.  \n", state.file_name );
        		exit(-1); // exits if there is a issue.
        	} else if ((ret = strcmp(tokens.array[i + 1], "}")) == 0){
        		printf("[ERROR]::(%s) list cannot have a name of a }.  \n", state.file_name );
        		exit(-1); // exits if there is a issue.
        	} else{

                 read_list_scope_pos = read_list_scope_pos + 1;
                LWDL_TOOL_INIT_ARRAY(&data->list_array.array[read_list_scope_pos - 1].list_values,5);
                data->list_array.array[read_list_scope_pos - 1].list_name = tokens.array[i + 1];
                LWDL_TOOL_INIT_ARRAY(&data->list_array.array[read_list_scope_pos - 1].list_values_name,5);

        	} 
        		
        }
        if ((ret = strcmp(tokens.array[i], "{")) == 0)
        {
        	inScope = LWDL_true;
         
            

        }

           if ((ret = strcmp(tokens.array[i], ":")) == 0 && inScope)
           {

                LWDL_TOOL_INSERT_ARRAY(&data->list_array.array[read_list_scope_pos - 1].list_values      , tokens.array[i + 1]);
                LWDL_TOOL_INSERT_ARRAY(&data->list_array.array[read_list_scope_pos - 1].list_values_name , tokens.array[i - 1]);

           }




        else if ((ret = strcmp(tokens.array[i], "}")) == 0 && inScope == LWDL_true)
        {
            LWDL_TOOL_INSERT_LIST_ARRAY(&data->list_array , data->list_array.array[read_list_scope_pos - 1]);
        	inScope = LWDL_false;
            
        }
        
          

    }


        data->lwdl_data_size = read_list_scope_pos  ;
     
        LWDL_TOOL_FREE_ARRAY(&tokens); // free the token array.

}


LWDL_string LWDL_getString(LWDL_Data data,LWDL_string list_name , LWDL_string value_name ){
  int ret = 0, o = 0 , b = 0;
  char* rett = "-1";
 for (o=0;o<data.lwdl_data_size  ;o++){
        if ((ret = strcmp(data.list_array.array[o].list_name,list_name)) == 0){
            
            for (b =0;b<data.list_array.array[o].list_values_name.used;b++){
                    if ((ret = strcmp(data.list_array.array[o].list_values_name.array[b],value_name)) == 0){
                        rett =  data.list_array.array[o].list_values.array[b];
                    }
            }

        }
    }
    return rett;
 }


 
int LWDL_getInt(LWDL_Data data,LWDL_string list_name , LWDL_string value_name ){

return atoi(LWDL_getString(data,list_name,value_name));
}

double LWDL_getDouble(LWDL_Data data,LWDL_string list_name , LWDL_string value_name ){
return (double)LWDL_getInt(data,list_name,value_name);
}
float LWDL_getFloat(LWDL_Data data,LWDL_string list_name , LWDL_string value_name){
return (float)LWDL_getInt(data,list_name,value_name);
}

void LWDL_PrintData(LWDL_Data data){
    for (int o=0;o<data.lwdl_data_size  ;o++){

        printf("list : %s\n     " , data.list_array.array[o].list_name);
        for (int b =0;b<data.list_array.array[o].list_values_name.used;b++){
            printf("%s : %s\n     ", data.list_array.array[o].list_values_name.array[b],data.list_array.array[o].list_values.array[b]);
       
        }
        printf("\n");
    }
}

void LWDL_Close(LWDL_Data* data , LWDL_State state)
{
    fclose(state.LWDL_File); // closes the state of the file opening 
    LWDL_TOOL_FREE_LIST_ARRAY(&data->list_array);    

}