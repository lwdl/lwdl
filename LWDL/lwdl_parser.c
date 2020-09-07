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
     LWDL_TOOL_INIT_LIST_ARRAY(&data->list_array , 5);
    LWDL_TOOL_INIT_LIST_ARRAY(&data->list_array,5);
    LWDL_TOOL_INIT_ARRAY(&tokens, 5);	// 5  is starting size. 

    while ((ch = fgetc(state.LWDL_File)) != EOF)
    {
        contents = LWDL_TOOL_AppendCharacters(contents, ch); // Visit LWDLTOOL (name explains it)
    }

    chunks = strtok(contents, "\t \n"); // token
     while (chunks != NULL)
    {
        
       
       
        LWDL_TOOL_INSERT_ARRAY(&tokens, chunks); // we insert a array from chunks
   
        
        chunks = strtok(NULL, "\t \n");

    }

    for (int i=0;i<tokens.used;i++){
        printf("%s\n", tokens.array[i]);
    }
    /* Parser, this uses the tokenized values,
    and stores them into the data arguments.
    afterwards, the user can fetch the data, converted , changed
    This parser also is a error.  */ 
 
     LWDL_bool inScope = LWDL_false;
    int read_list_scope_pos =0 ;
     
    for (int i = 0; i < tokens.used; i++)
    {
        if ((strcmp(tokens.array[i], "list")) == 0)
        {
            
            if ((  strcmp(tokens.array[i + 1], "{")) == 0){
        		printf("[ERROR]::(%s) list cannot have a name of a {.  \n", state.file_name );
                state.status = LWDL_FAILURE;
        	} else if (( strcmp(tokens.array[i + 1], "}")) == 0){
        		printf("[ERROR]::(%s) list cannot have a name of a }.  \n", state.file_name );
                state.status = LWDL_FAILURE;
        	
            } else{

                 read_list_scope_pos = read_list_scope_pos  ;
                LWDL_TOOL_INIT_ARRAY(&data->list_array.array[read_list_scope_pos  ].list_values,5);
                data->list_array.array[read_list_scope_pos ].list_name = tokens.array[i + 1];
                LWDL_TOOL_INIT_ARRAY(&data->list_array.array[read_list_scope_pos  ].list_values_name,5);

        	} 
        		
        }
        if ((  strcmp(tokens.array[i], "{")) == 0)
        {
        	inScope = LWDL_true;
         
            

        }

           if ((  strcmp(tokens.array[i], ":")) == 0 && inScope)
           {
                if (tokens.array[i + 1] != NULL || tokens.array[i - 1] != NULL){
                 
                LWDL_TOOL_INSERT_ARRAY(&data->list_array.array[read_list_scope_pos  ].list_values      , tokens.array[i + 1]);
                LWDL_TOOL_INSERT_ARRAY(&data->list_array.array[read_list_scope_pos  ].list_values_name , tokens.array[i - 1]);
                } else {
                    printf("[ERROR] There is no value_name or value\n");
                    state.status = LWDL_FAILURE;
                }

           }




        else if ((  strcmp(tokens.array[i], "}")) == 0 && inScope == LWDL_true)
        {
            LWDL_TOOL_INSERT_LIST_ARRAY(&data->list_array , data->list_array.array[read_list_scope_pos  ]);
        	inScope = LWDL_false;
            
        }
        
          

    }


    data->lwdl_data_size = read_list_scope_pos  ;
      LWDL_TOOL_FREE_ARRAY(&tokens); // free the token array.
     fclose(state.LWDL_File);
         
}


LWDL_string LWDL_getString(LWDL_Data data,LWDL_string list_name , LWDL_string value_name ){
   int o = 0 , b = 0;
  char* rett = "-1";
 for (o=0;o<data.lwdl_data_size  ;o++){
        if (( strcmp(data.list_array.array[o].list_name,list_name)) == 0){
            
            for (b =0;b<data.list_array.array[o].list_values_name.used;b++){
                    if ((  strcmp(data.list_array.array[o].list_values_name.array[b],value_name)) == 0){
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

 
float LWDL_getFloat(LWDL_Data data,LWDL_string list_name , LWDL_string value_name){
return atof(LWDL_getString(data,list_name,value_name));
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

void LWDL_Close(LWDL_Data* data  )
{
    LWDL_TOOL_FREE_LIST_ARRAY(&data->list_array);    

}