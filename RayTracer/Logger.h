#ifndef LOGGER_H
#define LOGGER_H
class Logger {
	public:
		Logger(std::string filename);
		void createEntry(int height, int width, float buildTime, float runtime, 
			int triangles, int spheres, int boxes, int num_rays_missed, int kdtree_max_depth, int kdtree_leaves);
	private:
		std::string filename;
};
#endif //LOGGER_H

