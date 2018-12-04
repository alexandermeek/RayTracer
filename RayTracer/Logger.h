#ifndef LOGGER_H
#define LOGGER_H
class Logger {
	public:
		Logger(std::string filename);
		void createEntry(int height, int width, float runtime, 
			int triangles, int spheres, int num_rays_missed);
	private:
		std::string filename;
};
#endif //LOGGER_H

