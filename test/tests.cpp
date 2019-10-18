//
// Created by Nikolay Shulga on 2019-06-18.
//

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <iostream>
#include "deserialize.h"

// stub to test the framework. Replace/modify as needed.

TEST_CASE("stub","[deserialize_lines]"){
    std::string input{"{\"lines\":[{\"id\":\"0-1\",\"start\":[373.44034013711515,-582.9714893905727],\"end\":[562.5097926743379,67.6201009971137]},{\"id\":\"0-2\",\"start\":[-395.24361297250138,-598.0232377709511],\"end\":[373.44034013711515,-582.9714893905727]}]}"};
    std::cout <<"Test case for string input" << std::endl;
  
    deserialize_from_string(input);
    std::cout << "\n\n" ;
    REQUIRE(true);
}

TEST_CASE("stub1","[deserialize_from_1-reference]"){
    std::cout <<  "Test case for 1-reference.json" << std::endl;
    deserialize_from_file("1-reference.json");
    std::cout << "\n\n" ;
    REQUIRE(true);
}


TEST_CASE("stub2","[deserialize_from_1-split]"){
    
    std::cout <<  "Test case for 1-split.json" << std::endl;
    deserialize_from_file("1-split.json");
    REQUIRE(true);
}