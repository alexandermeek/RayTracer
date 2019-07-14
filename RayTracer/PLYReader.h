#ifndef PLYREADER_H
#define PLYREADER_H

#include <vector>
class PLYReader {
	public:
		PLYReader(const std::string filename);

		std::string getFilename();
		int getNumVertices();
		int getNumFaces();

		bool readPLY(std::vector<Object3D*>& objects, std::vector<Vector3D*>& vertices);
	private:
		std::string filename;
		int numVertices = 0;
		int numFaces = 0;

		const std::string DELIMITER = " ";
		const std::string DESC_PLY = "ply";
		const std::string DESC_VERTICES = "element vertex";
		const std::string DESC_FACES = "element face";
		const std::string DESC_END_HEADER = "end_header";

		Vector3D* readPoint(std::string line) const;
		Triangle3D readTriangle(std::string line, const std::vector<Vector3D*>& vertices) const;
		Sphere readSphere(std::string line, const std::vector<Vector3D*>& vertices) const;
		Box readBox(std::string line, const std::vector<Vector3D*>& vertices) const;
};
#endif // PLYREADER_H
