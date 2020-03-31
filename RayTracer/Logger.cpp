#include "pch.h"
#include "Logger.h"

#include <iomanip> // setprecision
#include <ctime> //Timings
#include <fstream>

Logger::Logger(const std::string filename) : filename(filename) {}

void Logger::createEntry(const int height, const int width, const float buildTime, const float runtime, 
	const int triangles, const int spheres, const int boxes, const int num_rays_missed, const int kdtree_max_depth, const int kdtree_leaves) {

	std::time_t now = time(0);
	char dateTime[26];
	#if WINDOWS
		ctime_s(dateTime, sizeof dateTime, &now);
	#else
		ctime_r(&now, dateTime);
	#endif

	float percMiss = (float)num_rays_missed / float(height * width) * 100.0f;

	std::ifstream f(filename);
	bool new_file = f.good();

	std::ofstream logfile;
	logfile.open(filename, std::ios_base::app);
	if (!new_file) logfile << "date, num_pixels, build_time, runtime, num_triangles, num_spheres, num_boxes, %_miss, kdtree_max_depth, kdtree_leaves" << std::endl;
	logfile << std::fixed << std::setprecision(2)
		<< std::string(dateTime).substr(0, 24) << ", "
		<< height*width << ", "
		<< buildTime << ", "
		<< runtime << ", "
		<< triangles << ", "
		<< spheres << ", "
		<< boxes << ", "
		<< percMiss << ", "
		<< kdtree_max_depth << ", "
		<< kdtree_leaves << std::endl;
	logfile.close();
}
