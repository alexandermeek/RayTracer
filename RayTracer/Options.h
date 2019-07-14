#pragma once
class Options
{
public:
	Options(const std::string path);

	std::string image_filename;
	std::string log_filename;
	std::string model_path;
	std::string model_filename;

	int image_width;
	int image_height;
	int image_scale;
	int projection_type;
	bool shadows;
	int kdtree_max_depth;

	FloatRGB background_colour;
	FloatRGB light_intensity;
	FloatRGB kA, kD, kS;

	Vector3D camera_position;
	Vector3D light_position;
private:
	const char DELIMITER = '=';

	std::string read_string(std::string line) const;
	int read_int(std::string line) const;
	int read_projection_type(std::string line) const;
	bool read_bool(std::string line) const;
	FloatRGB read_colour(std::string line) const;
	Vector3D read_point(std::string line) const;
};

