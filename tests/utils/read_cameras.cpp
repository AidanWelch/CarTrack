#include "utils.h"
#include <cassert>
#include <cstddef>
#include <string>

CameraVector test_read_cameras() {
	char* camera_path = const_cast<char *>("../tests/sample_cameras.json"); // NOLINT
	CameraVector cams = read_cameras(camera_path);
	for (size_t i = 0; i < cams.size(); i++) {
		std::string correct_name = "cam " + std::to_string(i);
		assert(cams[i].description == correct_name);
		assert(cams[i].url == correct_name);
	}
	assert(cams[0].state == "my state");
	assert(cams[1].state == "my state");
	assert(cams[2].state == "my state");
	assert(cams[3].state == "other state");
	assert(cams[4].state == "other state");
	assert(cams[0].county == "my county");
	assert(cams[1].county == "my county");
	assert(cams[2].county == "other");
	assert(cams[3].county == "other");
	assert(cams[4].county == "other");
	return cams;
}