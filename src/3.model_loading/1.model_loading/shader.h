#pragma once

#include <glad/glad.h>
#include <stdlib.h> 
#include "raytraceData.h"

class shader {
public: 
	shader();
	~shader();

	// 여기 수정함
	raytraceData::material* makeMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat amb, GLfloat dif, GLfloat spec, GLfloat transparency, GLfloat reflectivity);	
	void shade(raytraceData::point* p, raytraceData::vector* n, raytraceData::material* m, raytraceData::color* c);
};
