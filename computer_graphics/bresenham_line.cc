#include<eigen3/Eigen/Eigen>

void set_piexl(Eigen::Vector3f point);

void DrawLine(Eigen::Vector3f begin, Eigen::Vector3f end) {
	int x_begin = begin.x();
	int x_end = end.x();
	int y_begin = begin.y();
	int y_end = end.y();

    Eigen::Vector3f line_color = {255, 255, 255};

	if(x_end - x_begin < 0) {
		std::swap(x_begin, x_end);
		std::swap(y_begin, y_end);
	}

	int dx = x_end - x_begin;
	int dy = y_end - y_begin;

	if(dx >= abs(dy)) {
		int e = -dx, cy = dy < 0 ? -1 : 1;
		dy = abs(dy);
		for(int x = x_begin, y = y_begin; x != x_end; x++) {
			Eigen::Vector3f point(x, y, 1.0f);
			set_pixel(point, line_color);
			e += 2 * dy;
			if(e > 0) {
				e -= 2 * dx;
				y += cy;
			}
		}
	}else {
		int e = -dy, cy = dy < 0 ? -1 : 1;
		dy = abs(dy);
		for(int x = x_begin, y = y_begin; y != y_end; y += cy) {
			Eigen::Vector3f point(x, y, 1.0f);
			set_pixel(point, line_color);
			e += 2 * dx;
			if(e > 0) {
				e -= 2 * dy;
				x++;
			}
		}
	}
	Eigen::Vector3f point(x_end, y_end, 1.0f);
	set_pixel(point, line_color);
}
