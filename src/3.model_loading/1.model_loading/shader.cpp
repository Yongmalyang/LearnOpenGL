#include "shader.h"
#include <math.h>

using namespace raytraceData;

shader::shader()
{
}

shader::~shader()
{
}

material* shader::makeMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat amb, GLfloat dif, GLfloat spec, GLfloat transparency, GLfloat reflectivity) {
	material* m;

	/* allocate memory */
	m = new material();

	/* put stuff in it */
	m->c.r = r;
	m->c.g = g;
	m->c.b = b;
	m->amb = amb;

	// 여기서부터 직접 추가한 내용
	m->dif = dif;
	m->spec = spec;
	m->transparency = transparency;
	m->reflectivity = reflectivity;
	return(m);
}

float dotProduct(vector* v1, vector* v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

void normalize(vector* v) {
    float length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    if (length > 0.0f) {
        v->x /= length;
        v->y /= length;
        v->z /= length;
    }
}

void reflect(vector* L, vector* N, vector* R) {
    float dotLN = 2.0f * dotProduct(N, L);
    R->x = dotLN * N->x - L->x;
    R->y = dotLN * N->y - L->y;
    R->z = dotLN * N->z - L->z;
}

/* LIGHTING CALCULATIONS */

/* shade */
/* color of point p with normal vector n and material m returned in c */

// diffuse와 specular는 이 함수에서 구현(step 1)
// shadow ray는 여기서(step 3)

void shader::shade(point* p, vector* n, material* m, color* c) {
    // 전역 ambient 조명 강도 높임
    float globalAmbient = 0.7f;

    // 전역 조명 계산
    c->r = globalAmbient * m->c.r;
    c->g = globalAmbient * m->c.g;
    c->b = globalAmbient * m->c.b;

    // 광원 위치를 높이고 강도도 증가시킴
    vector lightDir = { 0.0f, -2.0f, 1.0f, 0.0f };
    float lightIntensity = 1.5f;

    vector viewDir = { -p->x, -p->y, -p->z, 0.0f };
    normalize(&lightDir);
    normalize(n);
    normalize(&viewDir);

    // Diffuse 조명 계산 (강도 증가)
    float dotNL = max(0.0f, dotProduct(n, &lightDir));
    c->r += lightIntensity * m->dif * m->c.r * dotNL;
    c->g += lightIntensity * m->dif * m->c.g * dotNL;
    c->b += lightIntensity * m->dif * m->c.b * dotNL;

    // Specular 조명 계산 (강도 증가)
    vector reflectDir;
    reflect(&lightDir, n, &reflectDir);
    float spec = pow(max(0.0f, dotProduct(&reflectDir, &viewDir)), 32);
    c->r += lightIntensity * m->spec * spec;
    c->g += lightIntensity * m->spec * spec;
    c->b += lightIntensity * m->spec * spec;

    // 색상 범위 제한
    c->r = min(1.0f, c->r);
    c->g = min(1.0f, c->g);
    c->b = min(1.0f, c->b);
}
