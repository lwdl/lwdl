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

    struct lists {
        std::string list_name;
        std::vector<std::string> list_value_name;
        std::vector<std::string> list_value;
    }; 
    class Parser {

        public:
        Parser(const std::string& str);
        Parser() {};

        public:
        void openFile(const std::string& str);
        void close();
        void parse(); // tokenizes it and then afterwards stores the results
        public:


        const status getStatus();
        
        std::string getString(const std::string& list_name , const std::string& value_name);
        int getInt           (const std::string& list_name , const std::string& value_name );
        double getDouble     (const std::string& list_name , const std::string& value_name );
        float getFloat       (const std::string& list_name , const std::string& value_name );

    
        private:
        
        std::vector<LWDL::lists> list;
        std::ifstream file;
        status _status;

    };

}

 

#endif