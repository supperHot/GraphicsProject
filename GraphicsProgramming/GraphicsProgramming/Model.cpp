// Below ifdef required to remove warnings for unsafe version of fopen and fscanf.
// Secure version won't work cross-platform, forcing this small hack.
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "model.h"

bool model::load(char* modelFilename, char* textureFilename)
{
	bool result;

	// Load in the model data,
	result = loadModel(modelFilename);
	if (!result)
	{
		MessageBox(NULL, "Model failed to load", "Error", MB_OK);
		return false;
	}

	// Load the texture for this model.
	loadTexture(textureFilename);

	return true;
}

void model::render()
{
	
	glBindTexture(GL_TEXTURE_2D, texture);//here we add our texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < triangles.size(); i++) {
		glVertex3f(triangles[i][0].x + (postition.x+1), triangles[i][0].y + (postition.y + 1), triangles[i][0].z + (postition.z + 1));
		//set coordinate 
		glNormal3f(triangles[i][1].x, triangles[i][1].y, triangles[i][1].z);
		//set normal
		glTexCoord2f(triangles[i][2].x, triangles[i][2].y);
		//set texture coordinate
	}//for every piont
	glEnd();
	
}


// Modified from a mulit-threaded version by Mark Ropper.
bool model::loadModel(char* filename)
{
	vector<Vector3> verts;
	vector<Vector3> norms;
	vector<Vector3> texCs;
	vector<unsigned int> faces;
	
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		return false;
	}
	while (true)
	{
		char lineHeader[128];

		// Read first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break; // exit loop
		}
		else // Parse
		{
			if (strcmp(lineHeader, "v") == 0) // Vertex
			{
				Vector3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				verts.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) // Tex Coord
			{
				Vector3 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				texCs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) // Normal
			{
				Vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				norms.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) // Face
			{
				unsigned int face[9];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &face[0], &face[1], &face[2],
																			&face[3], &face[4], &face[5],
																			&face[6], &face[7], &face[8]);
				if (matches != 9)
				{
					// Parser error, or not triangle faces
					return false;
				}
				
				for (int i = 0; i < 9; i++)
				{
					faces.push_back(face[i]);
				}


			}
		}
	}

	triangles.resize(faces.size());
	for (int i = 0; i < faces.size(); i = i + 1) {
		triangles[i].resize(3);
	}//we need to make our vectors the right size

	int faceCounter = 0;
	//the face counter keeps track of witch number we are on when counting
	//up the faces array, since we go up by 3 every row in the array

	for (int i = 0; i < triangles.size() - 1; i ++) {
		if (faceCounter < faces.size()) {
			if (faces[faceCounter] <= verts.size()) {
				triangles[i][0] = verts[faces[faceCounter] - 1]; // the minus one is bc the faces array counts form one and not zero
			}faceCounter++;
			//vertcies
			if (faces[faceCounter] <= norms.size()) {
				triangles[i][1] = norms[faces[faceCounter] - 1];
			}faceCounter++;
			//normals
			if (faces[faceCounter] <= texCs.size()) {
				triangles[i][2] = texCs[faces[faceCounter] - 1];
			}faceCounter++;
			//texture coords
		}
	}
	//there are alot of ifs, I'm not 100% sure if I need all of them, it's just to stop errors with numbers being too big for the vectors
	


	// Once data has been sorted clear read data (which has been copied and are not longer needed).
	verts.clear();
	norms.clear();
	texCs.clear();
	faces.clear();

	return true;
}

void model::loadTexture(char* filename)
{
	texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y // Depending on texture file type some need inverted others don't.
	);

	//check for an error during the load process
	if (texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

}

void model::setPosition(float x,float y ,float z) {
	postition.x = x;
	postition.y = y;
	postition.z = z;
}



