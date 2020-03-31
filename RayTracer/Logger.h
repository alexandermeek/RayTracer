#ifndef LOGGER_H
#define LOGGER_H
class Logger {
	public:
		Logger(const std::string filename);
		void createEntry(const int height, const int width, const float buildTime, const float runtime, 
			const int triangles, const int spheres, const int boxes, const int num_rays_missed, const int kdtree_max_depth, const int kdtree_leaves);
	private:
		std::string filename;
};
#endif //LOGGER_H

