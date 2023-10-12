#include "camera_kd_tree.h"
#include "read_cameras.h"
#include <algorithm>

void camera_kd_tree( CameraVector& cameras ) {
	std::sort( cameras.begin(), cameras.end(),
		[]( const Camera& cam1, const Camera& cam2 ) { return cam1.longitude < cam2.longitude; } );
}