#include "lwdl_parser.hpp"


LWDL::Parser::Parser(const std::string& str){
    openFile(str);
}


void LWDL::Parser::openFile(const std::string&  str){
     file.open(str);
    if (file.fail()){
        this->_status = LWDL::status::LWDL_FAILURE;
    }else{
        this->_status = LWDL::status::LWDL_SUCCESS;
    }
}

void LWDL::Parser::close(){
    file.close();
}


const LWDL::status LWDL::Parser::getStatus(){
    return _status;
}

void LWDL::Parser::parse(){
       // tokenizes
    std::vector<std::string> tokens;
    std::string str_temp;
     do {
        file >> str_temp;  
        tokens.push_back(str_temp);
    }
    while (!this->file.eof());

    lists lwdl_l;
    bool inScope = false;
    for (int i=0;i<tokens.size();i++){
        if (tokens[i] == "list"){

            if (tokens[i + 1] == "{"){
                std::cout << "[ERR]: Cannot name a list a {\n";
                this->_status = LWDL::status::LWDL_FAILURE;
 
            }

            else if (tokens[i + 1] == "}"){
                std::cout << "[ERR]: Cannot name a list a }\n";
                this->_status = LWDL::status::LWDL_FAILURE;
      

            }
            else {
                lwdl_l.list_name = tokens[i+1];
            }

        }
        else if (tokens[i] == "{"){

            inScope = true;
        }
       else if (tokens[i] == ":" && inScope){
            lwdl_l.list_value.push_back(tokens[i+1]);
            lwdl_l.list_value_name.push_back(tokens[i-1]);
        }

       else if (tokens[i] == "}" and inScope){
                this->list.push_back(lwdl_l);
                /* time to clean up */
                lwdl_l.list_name  = "";
                lwdl_l.list_value.clear();
                lwdl_l.list_value_name.clear();
                inScope = false;
        }
    }


    


} 


std::string LWDL::Parser::getString(const std::string&  list_name , const std::string&  value_name)
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

int LWDL::Parser::getInt(const std::string&  list_name , const std::string&  value_name)
{
return std::stoi(getString(list_name, value_name));
}

double LWDL::Parser::getDouble(const std::string&  list_name , const std::string&  value_name)
{
    return std::stod(getString(list_name, value_name));

}

float LWDL::Parser::getFloat(const std::string& list_name , const std::string&  value_name)
{
    return std::stof(getString(list_name, value_name));

}