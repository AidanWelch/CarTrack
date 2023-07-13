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
		State cur_state;
		std::string cur_county_name;
		County cur_county;
		Camera cur_camera;
		std::string line;
		while(std::getline(file, line)){
			int movement = 0;
			bool escaped = false;
			bool in_string = false;
			std::string key;
			bool key_ended = false;
			std::string value;
			for(uint i = 0; i < line.length(); i++){
				if((line[i] == '{' || line[i] == '[') && !in_string ){
					movement--;
					nesting = static_cast<Nest>(nesting+1);
				} else if ((line[i] == '}' || line[i] == ']') && !in_string ) {
					movement++;
					nesting = static_cast<Nest>(nesting-1);
				} else if (line[i] == ':' && !in_string && !key_ended) {
					key_ended = true;
				} else if (line[i] == '"' && !escaped) {
					in_string = !in_string;
				} else if ((line[i] != ' ' && line[i] != ',') || in_string){
					if(!key_ended){
						key.push_back(line[i]);
					} else {
						value.push_back(line[i]);
					}
				}
				escaped = (line[i] == '\\' && !escaped);
			}
			switch(nesting){
				case NONE:
					break;
				case COUNTRY:
					if (movement == 1) {
						cameras[cur_state_name] = cur_state;
					}
					break;
				case STATE:
					if(key_ended && movement == -1){
						cur_state_name = key;
						cur_state.clear();
					} else if (movement == 1) {
						cur_state[cur_county_name] = cur_county;
					}
					break;

				case COUNTY:
					if(key_ended && movement == -1){
						cur_county_name = key;
						cur_county.clear();
					} else if (movement == 1) {
						cur_county.push_back(std::move(cur_camera));
					}
					break;

				case CAMERA:
				case LOCATION:
					if(key.length() != 0 && value.length() != 0){
						if(key == "description"){
							cur_camera.description = value;
						} else if (key == "direction") {
							cur_camera.direction = value;
						} else if (key == "latitude") {
							cur_camera.latitude = value;
						} else if (key == "longitude") {
							cur_camera.longitude = value;
						} else if (key == "url") {
							cur_camera.url = value;
						} else if (key == "encoding") {
							cur_camera.encoding = value;
						} else if (key == "update_rate") {
							cur_camera.update_rate = value;
						} else if (key == "marked_for_review"){
							cur_camera.marked_for_review = value;
						}
					}
					break;
			}
		}
		file.close();
		return cameras;
	} else {
		std::cerr << "Could not open \"" << file_path << '"' << std::endl;
		exit(EXIT_FAILURE);
	}
}