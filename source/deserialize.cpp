//
// Created by Nikolay Shulga on 2019-06-18.
//


#include "deserialize.h"
#include <cmath>
// STL
#include <string>
#include <fstream>
#include "rapidjson/filereadstream.h"
// RapidJSON
#include "document.h"
#include "rapidjson.h"
#include <vector> 
#include <iostream>
#include <sstream>
#include <map> 
#include <iomanip>
#include <algorithm>
#include <string>
using namespace rapidjson;


// Input data format/parsing.
// Input is a JSON file. The root object is an array called "lines". These are line segments.
// Each line segment has an id "id" (string), starting point "start and an end point "end".
// Points are represented as an array of two doubles. These correspond to X and Y cartesian coordinates.

struct final_segments{
    double start_x;
    double end_x;
    double start_y;
    double end_y;

};
std::vector<final_segments> solution;

void deserialize(Document& doc) {
    
    std::vector<double> slopes;
   // std::map<double,similar_slopes> dictionary; 
    std::map<double, std::vector<double>> dictionary;

    auto const& lines_json = doc["lines"];
    if (lines_json.IsArray()){
        auto lines_array = lines_json.GetArray();
        for (auto& line : lines_array) {
            auto const& id_json = line["id"];
            auto const& start_json = line["start"];
            auto const& end_json = line["end"];
            if (id_json.IsString() && start_json.IsArray() && end_json.IsArray()) {
                auto start_x = start_json.GetArray()[0].GetDouble(),
                    start_y = start_json.GetArray()[1].GetDouble(),
                    end_x = end_json.GetArray()[0].GetDouble(),
                    end_y = end_json.GetArray()[1].GetDouble();

                

                auto id = id_json.GetString();
                //lets get the slope of the lines and see
                //which ones are *parallel and might merge at some point
                auto slope = (end_y-start_y)/(end_x-start_x);
                
                //i did not find an exact value match of slopes except for 1, 
                slope = (int)(slope * 100.0)/100.0;
                slopes.push_back(slope);


                //now check the dictionary
                // if it is empty, add the slope to the dictionary.
                //goal here is to place together line segments that have quite close slopes,
                //i found very similar slopes however, around 6 that were off .01,
                //decided to round down to 2 decimal place
                //i did not round i cut to the last 2 decimal places


                //need to see a better method than manually pushing back 4 elements but it was simpler than creating a new vector and then adding that
                //vector to the vector
                if(dictionary.empty()){
                  dictionary.insert(std::pair<double,std::vector<double>>(slope,std::vector<double>()));
                  dictionary[slope].push_back(start_x);
                  dictionary[slope].push_back(start_y);  
                  dictionary[slope].push_back(end_x);  
                  dictionary[slope].push_back(end_y);    

                }

                //next is a comparison, if it exists add the other line segments that have the same slope,
                //if not, make an entry then for the slope and coordinates


                //now if dictionary is not empty, 
                if(dictionary.count(slope) == 0){
                    //slope not in key, add element
                    dictionary.insert(std::pair<double,std::vector<double>>(slope,std::vector<double>()));
                    dictionary[slope].push_back(start_x);
                    dictionary[slope].push_back(start_y);  
                    dictionary[slope].push_back(end_x);  
                    dictionary[slope].push_back(end_y);

                }
                else if(dictionary.count(slope) == 1){
                    dictionary[slope].push_back(start_x);
                    dictionary[slope].push_back(start_y);  
                    dictionary[slope].push_back(end_x);  
                    dictionary[slope].push_back(end_y);
                }



            }

        }
    }
   

    
    for(auto it = dictionary.cbegin(); it!=dictionary.cend(); ++it){
        //going to iterate over the dictionary and only look at keys that contain more than 1 line segments ( more than 4 coordinate values or more than 2 pairs)
        if(it->second.size() > 4){
            std::vector<double> x_coordinates;
            std::vector<double> y_coordinates;

            for (auto it2 = it->second.begin();it2 != it->second.end(); ++it2)
            {
                 //if it does have more than 1 line segment, we are going to find the min and max coordinates to draw the line
                //this newly merged line should have the endpoints of the other line.

                
                //take the even positions and put them in the x_coordinates
                //take the odd positions and put them in the y_coordinates
                if((it2 - it->second.begin())%2){
                    //x is odd
                    y_coordinates.push_back(*it2);
                }
                else
                    x_coordinates.push_back(*it2);

                //now we can find the min and max of the x coordinates, find their position
                //in the vector and use that to get the position from the y_coordinates vector
                //everything was added subsequently so using the index for one vector for another should work



            }
            auto result = std::minmax_element(x_coordinates.begin(),x_coordinates.end());
            int min_index = result.first-x_coordinates.begin();
            int max_index = result.second-x_coordinates.begin();

            //lets add solution to vector

            //now we have a solution for the max values, we need to get the positions in the x vector, y vector,
            //i have made a struct to store the merged lines, we can add many of these structs to a final vector
            //that contains all of the newly created line segments

            solution.push_back(final_segments());
           
            solution[solution.size()-1].start_x = *result.first;
            solution[solution.size()-1].end_x = *result.second;
            

            solution[solution.size()-1].start_y = y_coordinates[min_index];
            solution[solution.size()-1].end_y = y_coordinates[max_index];
            

            //lets print out the answer
            std::cout << "start_x " << solution[solution.size()-1].start_x << " start_y " << solution[solution.size()-1].start_y << " end x " << solution[solution.size()-1].end_x << " end y " << solution[solution.size()-1].end_y << "\n";


            //garbacge collecting the vectors, not sure if this is needed or if the vectors will automatically
            //be killed off once out of scope like other variables.


        }
       
       

     //lets    
    }

    //now all the keys that contain a vecto with more than 4 elements are the coordinates

   






    
}

void deserialize_from_string(std::string const &json_data){

    
    Document doc;
   
    doc.Parse(json_data.c_str());
    deserialize(doc);

}

void deserialize_from_file(std::string const file_name){

    //FILE* fp = fopen("../test/assets/1-split.json", "r"); // 
    
    //quick string concatenation
    //later see how to just use the one function

    std::string path = "../test/assets/" + file_name;
    FILE* fp = fopen(path.c_str(), "r");
    //need to do error checking that the file actually works
    //this is done by checking the value of the file and making sure
    //it is not equal to 0 or Nullptr?

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));


  
    Document doc;
    doc.ParseStream(is);
    fclose(fp);
    deserialize(doc);
   
    

}



