#include "pch.h"
#include "Options.h"

#include <fstream>

Options::Options(const std::string path) {
	std::string line;
	std::ifstream options_file(path);

	if (options_file.is_open()) {
		std::getline(options_file, line);
		image_filename = read_string(line);

		std::getline(options_file, line);
		log_filename = read_string(line);

		std::getline(options_file, line);
		model_path = read_string(line);

		std::getline(options_file, line);
		model_filename = read_string(line);

		std::getline(options_file, line);
		image_width = read_int(line);

		std::getline(options_file, line);
		image_height = read_int(line);

		std::getline(options_file, line);
		image_scale = read_int(line);

		std::getline(options_file, line);
		projection_type = read_projection_type(line);

		std::getline(options_file, line);
		shadows = read_bool(line);

		std::getline(options_file, line);
		kdtree_max_depth = read_int(line);

		std::getline(options_file, line);
		background_colour = read_colour(line);

		std::getline(options_file, line);
		camera_position = read_point(line);

		std::getline(options_file, line);
		light_position = read_point(line);

		std::getline(options_file, line);
		light_intensity = read_colour(line);

		std::getline(options_file, line);
		kA = read_colour(line);

		std::getline(options_file, line);
		kD = read_colour(line);

		std::getline(options_file, line);
		kS = read_colour(line);
	}
}

std::string Options::read_string(std::string line) const {
	int start, end;
	std::string token;

	start = line.find('"') + 1;
	token = line.substr(start, line.length());
	end = token.find('"');
	token = line.substr(start, end);

	return token;
}

int Options::read_int(std::string line) const {
	int start;
	std::string token;

	start = line.find(DELIMITER) + 2;
	token = line.substr(start, line.length());
	
	return std::atoi(token.c_str());
}

int Options::read_projection_type(std::string line) const {
	int start;
	std::string token;
	
	start = line.find(DELIMITER) + 2;
	token = line.substr(start, line.length());

	if (token == "orthographic") {
		return Camera::ORTHOGRAPHIC;
	}
	else {
		return Camera::PERSPECTIVE;
	}
}

bool Options::read_bool(std::string line) const {
	int start;
	std::string token;

	start = line.find(DELIMITER) + 2;
	token = line.substr(start, line.length());

	if (token == "true") {
		return true;
	}
	else {
		return false;
	}
}

FloatRGB Options::read_colour(std::string line) const {
	int start;
	std::string token;
	float v[3];

	start = line.find(DELIMITER) + 2;
	token = line.substr(start, line.length());
	
	v[0] = std::atof(token.c_str());
	
	start = token.find(' ');
	token.erase(0, start + 1);

	v[1] = std::atof(token.c_str());

	start = token.find(' ');
	token.erase(0, start + 1);

	v[2] = std::atof(token.c_str());

	return FloatRGB(v[0], v[1], v[2]);
}

Vector3D Options::read_point(std::string line) const {
	int start;
	std::string token;
	float v[3];

	start = line.find(DELIMITER) + 2;
	token = line.substr(start, line.length());

	v[0] = std::atof(token.c_str());

	start = token.find(' ');
	token.erase(0, start + 1);

	v[1] = std::atof(token.c_str());

	start = token.find(' ');
	token.erase(0, start + 1);

	v[2] = std::atof(token.c_str());

	return Vector3D(v[0], v[1], v[2]);
}
