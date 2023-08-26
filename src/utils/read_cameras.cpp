#include "read_cameras.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

enum NEST { NONE, COUNTRY, STATE, COUNTY, CAMERA, LOCATION };

CameraVector read_cameras( char*& file_path ) {
	std::ifstream file;
	file.open( file_path, std::ios::in );
	if ( !file.is_open() ) {
		throw std::runtime_error( "Could not open " + static_cast<std::string>( file_path ) );
	}
	CameraVector cameras;
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
	while ( std::getline( file, line ) ) {
		for ( const char& c : line ) {
			if ( in_string ) {
				if ( c == '"' && !escaped ) {
					in_string = false;
				} else {
					if ( key_ended ) {
						// key_ended can only be true after a value.clear() call
						// value is only std::move'd after key_ended is set false
						value.push_back( c );  // NOLINT
					} else {
						key.push_back( c );
					}
					if ( escaped ) {
						escaped = false;
					} else if ( c == '\\' ) {
						escaped = true;
					}
				}
			} else {
				switch ( c ) {
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
						value.clear();  // Clear value before next
						break;
					case '{':
					case '[':
						nesting = static_cast<NEST>( nesting + 1 );
						switch ( nesting ) {
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
						if ( !key_ended ) {
							if ( nesting == CAMERA ) {
								cameras.back().state = cur_state;
								cameras.back().county = cur_county;
								cameras.emplace_back();
							}
							nesting = static_cast<NEST>( nesting - 1 );
							break;
						}
						[[fallthrough]];  // Fallthrough if last member not pushed(it generally isn't)
					case ',':
						key_ended = false;
						if ( nesting == CAMERA || nesting == LOCATION ) {
							if ( !key.empty() && !value.empty() ) {
								if ( key == "description" ) {
									cameras.back().description = std::move( value );
								} else if ( key == "direction" ) {
									cameras.back().direction = std::move( value );
								} else if ( key == "latitude" ) {
									cameras.back().latitude = std::stof( value );
								} else if ( key == "longitude" ) {
									cameras.back().longitude = std::stof( value );
								} else if ( key == "url" ) {
									cameras.back().url = std::move( value );
								} else if ( key == "encoding" ) {
									cameras.back().encoding = std::move( value );
								} else if ( key == "update_rate" ) {
									cameras.back().update_rate = std::move( value );
								} else if ( key == "marked_for_review" ) {
									cameras.back().marked_for_review = std::move( value );
								}
							}
						}
						if ( c == '}' || c == ']' ) {
							if ( nesting == CAMERA ) {
								cameras.back().state = cur_state;
								cameras.back().county = cur_county;
								cameras.emplace_back();
							}
							nesting = static_cast<NEST>( nesting - 1 );
						}
						key.clear();
						break;
					default:
						// no point of checking if in key because key must be string
						value.push_back( c );
						break;
				}
			}
			// LOGGING
			// std::cout << std::endl << "char: " << c << " i: " << i;
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