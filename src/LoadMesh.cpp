#include "Core.h"
#include "LoadMesh.h"

#include <vector>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

Mesh * LoadMesh(const char * filename)
{
	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* aiscene = importer.ReadFile( filename, 
		aiProcess_CalcTangentSpace       | 
		aiProcess_Triangulate            |
		aiProcess_JoinIdenticalVertices  |
		aiProcess_SortByPType);

	// If the import failed, report it
	if( !aiscene)
	{
		printf("%s \n", importer.GetErrorString());
		return NULL;
	}

	aiMesh * aimesh;
	Mesh * mesh = new Mesh();

	std::vector<vec3> vertex;
	std::vector<vec3> normal;
	std::vector<vec3> tangent;
	std::vector<vec2> texCoord;

	// Now we can access the file's contents.
	for(u32 i=0; i<aiscene->mNumMeshes(); ++i)
	{
		aimesh = aiscene->mMeshes[i];

		if(aimesh->HasPositions())
		{

		}
	}

	return mesh;
}