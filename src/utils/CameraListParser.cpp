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
            bool moved_up = false;
            bool escaped = false;
            bool in_string = false;
            std::string key;
            bool key_ended = false;
            std::string value;
            for(uint i = 0; i < line.length(); i++){
                if(line[i] == '{' || line[i] == '[' && !in_string ){
                    nesting = static_cast<Nest>(nesting-1);
                } else if (line[i] == '}' || line[i] == ']' && !in_string ) {
                    moved_up = true;
                    nesting = static_cast<Nest>(nesting+1);
                } else if (line[i] == ':' && !in_string && !key_ended) {
                    key_ended = true;
                } else if (line[i] == '"' && !escaped) {
                    in_string = !in_string;
                } else if (line[i] != ' ' || in_string){
                    if(!key_ended){
                        key.push_back(line[i]);
                    } else {
                        value.push_back(line[i]);
                    }
                }
                escaped = (line[i] == '\\' && !escaped);
            }

        }
        return cameras;
    } else {
        std::cerr << "Could not open \"" << file_path << '"' << std::endl;
        exit(EXIT_FAILURE);
    }
}