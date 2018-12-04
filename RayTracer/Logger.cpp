#include "pch.h"
#include "Logger.h"

#include <ctime> //Timings
#include <fstream>

Logger::Logger(std::string filename) {
	this->filename = filename;
}

void Logger::createEntry(int height, int width, float duration, int triangles, int spheres) {
	std::time_t now = time(0);
	char dateTime[26];
	ctime_s(dateTime, sizeof dateTime, &now);

	std::ofstream logfile;
	logfile.open(filename, std::ios_base::app);
	logfile << std::string(dateTime).substr(0, 24)
		<< ", Image size: " << height << "x" << width
		<< ", Duration: " << duration << " secs"
		<< ", Triangles: " << triangles
		<< ", Spheres: " << spheres
		<< std::endl;
	logfile.close();
}
