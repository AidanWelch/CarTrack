#include "camera_kd_tree.h"
#include "read_cameras.h"
#include <algorithm>
#include <cstddef>

// consider no recursion implementation
Camera* camera_kd_tree_create( CameraVector& cameras, int start, int end, int depth ) {
	if ( start == end ) {
		return nullptr;
	}
	std::sort( cameras.begin() + start, cameras.begin() + end,
		[depth]( const Camera& cam1, const Camera& cam2 ) {
			if ( depth % 2 == 0 ) {
				return cam1.longitude < cam2.longitude;
			}
			return cam1.latitude < cam2.latitude;
		} );
	Camera* node = &cameras[static_cast<std::size_t>( ( ( end - start ) / 2 ) ) +
		static_cast<std::size_t>( start )];
	node->left =
		camera_kd_tree_create( cameras, start, start + ( ( end - start ) / 2 ), depth + 1 );
	node->right =
		camera_kd_tree_create( cameras, 1 + start + ( ( end - start ) / 2 ), end, depth + 1 );
	return node;
}