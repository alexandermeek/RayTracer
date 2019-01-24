#include "pch.h"
#include "Logger.h"

#include <iomanip> // setprecision
#include <ctime> //Timings
#include <fstream>

Logger::Logger(std::string filename) {
	this->filename = filename;
}

void Logger::createEntry(int height, int width, float runtime, 
	int triangles, int spheres, int boxes, int num_rays_missed) {

	std::time_t now = time(0);
	char dateTime[26];
	ctime_s(dateTime, sizeof dateTime, &now);

	float percMiss = (float)num_rays_missed / float(height * width) * 100.0f;

	std::ofstream logfile;
	logfile.open(filename, std::ios_base::app);
	logfile << std::fixed << std::setprecision(2)
		<< std::string(dateTime).substr(0, 24)
		<< ", Image size: " << height << "x" << width
		<< ", Runtime: " << runtime << " secs"
		<< ", Triangles: " << triangles
		<< ", Spheres: " << spheres
		<< ", Boxes: " << boxes
		<< ", % miss: " << percMiss
		<< std::endl;
	logfile.close();
}
