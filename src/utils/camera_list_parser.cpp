#include <iostream>
#include <fstream>
#include "camera_list_parser.h"

enum NEST {NONE, COUNTRY, STATE, COUNTY, CAMERA, LOCATION};

CameraList CameraParse(std::string file_path) {
	std::ifstream file;
	file.open(file_path, std::ios::in);
	if(!file.is_open()){
		std::cerr << "Could not open \"" << file_path << '"' << std::endl;
		exit(EXIT_FAILURE);
	}
	CameraList cameras;
	cameras.emplace_back();
	NEST nesting = NONE;
	std::string cur_state;
	std::string cur_county;
	bool escaped = false;
	bool in_string = false;
	std::string key;
	bool key_ended = false;
	std::string value;
	std::string line;
	while(std::getline(file, line)){
		for (unsigned long long int i = 0; i < line.length(); i++){
			if (in_string) {
				if (line[i] == '"' && !escaped) {
					in_string = false;
				} else {
					if (key_ended) {
						value.push_back(line[i]);
					} else {
						key.push_back(line[i]);
					}
					if (escaped) {
						escaped = false;
					} else if (line[i] == '\\') {
						escaped = true;
					}
				}
			} else {
				switch (line[i]) {
					case ' ':
					case '	':
					case '\r':
					case '\n':
						break;
					case '"':
						in_string = true;
						break;
					case ':':
						key_ended = true;
						value.clear(); // Clear value before next
						break;
					case '{':
					case '[':
						nesting = static_cast<NEST>(nesting+1);
						switch (nesting) {
							case STATE:
								cur_state = key;
								break;
							case COUNTY:
								cur_county = key;
								break;
							default:
								break;
						}
						key.clear();
						key_ended = false;
						break;
					case '}':
					case ']':
						if (!key_ended) {
							if (nesting == CAMERA) {
								cameras.back().state = cur_state;
								cameras.back().county = cur_county;
								cameras.emplace_back();
							}
							nesting = static_cast<NEST>(nesting-1);
							break;
						}
						// Fallthrough if last member not pushed(it generally isn't)
					case ',':
						key_ended = false;
						if (nesting == CAMERA || nesting == LOCATION){
							if(!key.empty() && !value.empty()){
								if(key == "description"){
									cameras.back().description = std::move(value);
								} else if (key == "direction") {
									cameras.back().direction = std::move(value);
								} else if (key == "latitude") {
									cameras.back().latitude = std::stof(value);
								} else if (key == "longitude") {
									cameras.back().longitude = std::stof(value);
								} else if (key == "url") {
									cameras.back().url = std::move(value);
								} else if (key == "encoding") {
									cameras.back().encoding = std::move(value);
								} else if (key == "update_rate") {
									cameras.back().update_rate = std::move(value);
								} else if (key == "marked_for_review"){
									cameras.back().marked_for_review = std::move(value);
								}
							}
						}
						if (line[i] == '}' || line[i] == ']') {
							if (nesting == CAMERA) {
								cameras.back().state = cur_state;
								cameras.back().county = cur_county;
								cameras.emplace_back();
							}
							nesting = static_cast<NEST>(nesting-1);
						}
						key.clear();
						break;
					default:
						// no point of checking if in key because key must be string
						value.push_back(line[i]);
						break;
				}
			}
			// LOGGING
			// std::cout << std::endl << "char: " << line[i] << " i: " << i;
			// std::cout << " [instring, escaped, keyended]: [" << in_string << ", ";
			// std::cout << escaped << ", " << key_ended << "] " << "key: ";
			// std::cout << key << " value: " << value << " nesting: ";
			// std::cout << nesting << " size: " << cameras.size();
		}
	}
	cameras.pop_back();
	file.close();
	return cameras;
}