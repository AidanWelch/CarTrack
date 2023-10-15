#ifndef CARTRACK_UTILS_CAMERAKDTREE_H_
#define CARTRACK_UTILS_CAMERAKDTREE_H_

#include "read_cameras.h"

Camera* camera_kd_tree_create( CameraVector& cameras, int start, int end, int depth = 0 );

#endif