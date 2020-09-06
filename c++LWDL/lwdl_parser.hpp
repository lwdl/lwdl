#ifndef LWDL_PARSER_HPP
#define LWDL_PARSER_HPP
#include <iostream>
#include <fstream>
#include <vector>
namespace LWDL {
    enum class status {
        LWDL_FAILURE = 1, 
        LWDL_SUCCESS = 2
    };

    struct LWDL_lists {
        std::string list_name;
        std::vector<std::string> list_value_name;
        std::vector<std::string> list_value;
    }; 
    class Parser {

        public:
        Parser(std::string str);
        Parser() {};

        public:
        void openFile(std::string str);
        void close();
        void parse(); // tokenizes it and then afterwards stores the results
        public:


        const status getStatus();
        
        std::string getString(std::string list_name , std::string value_name);
        int getInt           (std::string list_name , std::string value_name );
        double getDouble     (std::string list_name , std::string value_name );
        float getFloat       (std::string list_name , std::string value_name );

    
        private:
        
        std::vector<LWDL::LWDL_lists> list;
        std::ifstream LWDL_Parser;
        status _status;

    };

}

 

#endif