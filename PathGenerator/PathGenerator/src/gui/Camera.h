#include <queue>
#include <vector>
#include "View.h"

class Camera {

	struct {
		bool operator()(const View& v1, const View& v2) const {
			return v1.depth < v2.depth;
		}
	}customComp;
	
	std::priority_queue < View, std::vector<View>, decltype(customComp)> list;
	int cameraPosX;
	int cameraPosY;
	
};