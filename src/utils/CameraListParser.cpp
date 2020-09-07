#include <iostream>
#include <fstream>
#include "CameraListParser.h"

CameraList CameraParse(std::string file_path) {
    std::ifstream file;
    file.open(file_path, std::ios::in);
    if(file){
        CameraList cameras;
        enum Nest {NONE, COUNTRY, STATE, COUNTY, CAMERA, LOCATION} nesting = NONE;
        std::string cur_state_name;
        std::string cur_county_name;
        std::string line;
        while(std::getline(file, line)){
            bool in_string = false;
            for(uint i = 0; i < line.length(); i++){
                in_string = (line[i] == '"') ^ in_string;
                if(line[i] == '{' || line[i] == '['){
                    nesting = static_cast<Nest>(nesting-1);
                } else if (line[i] == '}' || line[i] == ']') {
                    nesting = static_cast<Nest>(nesting+1);
                } else {
                    switch
                }
            }
        }
        return cameras;
    } else {
        std::cerr << "Could not open \"" << file_path << '"' << std::endl;
        exit(EXIT_FAILURE);
    }
}