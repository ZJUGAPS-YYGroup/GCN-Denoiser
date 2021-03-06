#ifndef MESHDENOISINGBASE_H
#define MESHDENOISINGBASE_H

#include "datamanager.h"

class MeshDenoisingBase
{
public:
	MeshDenoisingBase(DataManager *_data_manager);
	~MeshDenoisingBase() {}

public:
	virtual void initParameters() = 0;

	// some basic function
	double getAverageEdgeLength(TriMesh &mesh);
	void getFaceArea(TriMesh &mesh, std::vector<double> &area);
	void getFaceCentroid(TriMesh &mesh, std::vector<TriMesh::Point> &centroid);
	void getFaceNormal(TriMesh &mesh, std::vector<TriMesh::Normal> &normals);

	// two stage method, first update normals, second update vertices
	enum FaceNeighborType { kVertexBased, kEdgeBased, kRadiusBased };
	enum DenoiseType { kLocal, kGlobal };

	void getFaceNeighbor(TriMesh &mesh, TriMesh::FaceHandle fh, FaceNeighborType face_neighbor_type, std::vector<TriMesh::FaceHandle> &face_neighbor);
	void getAllFaceNeighbor(TriMesh &mesh, std::vector< std::vector<TriMesh::FaceHandle> > &all_face_neighbor, FaceNeighborType face_neighbor_type = kVertexBased, bool include_central_face = false);
	virtual void updateFilteredNormals(TriMesh &mesh, std::vector<TriMesh::Normal> &filtered_normals) {}
	void updateVertexPosition(TriMesh &mesh, std::vector<TriMesh::Normal> &filtered_normals, int iteration_number, bool fixed_boundary = false);

	// error metric
	double getMeanSquareAngleError(TriMesh &DenoisedMesh, TriMesh &OriginalMesh);
	double updategetError(std::vector<TriMesh::Normal> &filtered_normals);
	double getError();

	double getMeanSquareAngleErrorMSEA(TriMesh &DenoisedMesh, TriMesh &OriginalMesh);
	double getVerticesDistance(TriMesh &DenoisedMesh, TriMesh &OriginalMesh);
	double getErrorMSAE();
	double getErrorDv();

public:
	DataManager *data_manager_;
};

#endif // MESHDENOISINGBASE_H