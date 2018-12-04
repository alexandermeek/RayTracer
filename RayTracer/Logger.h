#ifndef LOGGER_H
#define LOGGER_H
class Logger {
	public:
		Logger(std::string filename);
		void createEntry(int height, int width, float duration, int triangles, int spheres);
	private:
		std::string filename;
};
#endif //LOGGER_H

