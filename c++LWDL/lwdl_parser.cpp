#include "lwdl_parser.hpp"


LWDL::Parser::Parser(std::string str){
    openFile(str);
}


void LWDL::Parser::openFile(std::string str){
     LWDL_Parser.open(str);
    if (LWDL_Parser.fail()){
        this->_status = LWDL::status::LWDL_FAILURE;
        exit(-1);
    }else{
        this->_status = LWDL::status::LWDL_SUCCESS;
    }
}

void LWDL::Parser::close(){
    LWDL_Parser.close();
}


const LWDL::status LWDL::Parser::getStatus(){
    return _status;
}

void LWDL::Parser::parse(){
       // tokenizes
    std::vector<std::string> tokens;
    std::string str_temp;
     do {
        LWDL_Parser >> str_temp;  
        tokens.push_back(str_temp);
    }
    while (!this->LWDL_Parser.eof());

    LWDL_lists lwdl_l;
    for (int i=0;i<tokens.size();i++){
        if (tokens[i] == "list"){

            if (tokens[i + 1] == "{"){
                std::cout << "[ERR]: Cannot name a list a {\n";
                this->_status = LWDL::status::LWDL_FAILURE;
                exit(-1);
            }

            else if (tokens[i + 1] == "}"){
                std::cout << "[ERR]: Cannot name a list a }\n";
                this->_status = LWDL::status::LWDL_FAILURE;
                exit(-1);

            }
            else {
                lwdl_l.list_name = tokens[i+1];
            }

        }

        if (tokens[i] == ":"){
            lwdl_l.list_value.push_back(tokens[i+1]);
            lwdl_l.list_value_name.push_back(tokens[i-1]);
        }

        if (tokens[i] == "}"){
                this->list.push_back(lwdl_l);
                /* time to clean up */
                lwdl_l.list_name  = "";
                lwdl_l.list_value.clear();
                lwdl_l.list_value_name.clear();
        }
    }


    tokens.clear();
    


} 


std::string LWDL::Parser::getString(std::string list_name , std::string value_name)
{
    std::string ret = "-1";
    for (int i=0;i<list.size();i++){
    if (this->list[i].list_name == list_name){
        for (int d=0;d < list.size();d++){
             if (this->list[i].list_value_name[d] == value_name){
                 ret = this->list[i].list_value[d]; 
             }
        }
    }

    }
    return ret;
}

int LWDL::Parser::getInt(std::string list_name , std::string value_name)
{
return std::stoi(getString(list_name, value_name));
}

double LWDL::Parser::getDouble(std::string list_name , std::string value_name)
{
    return std::stod(getString(list_name, value_name));

}

float LWDL::Parser::getFloat(std::string list_name , std::string value_name)
{
    return std::stof(getString(list_name, value_name));

}