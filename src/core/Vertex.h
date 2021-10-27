#ifndef ELECTRONICENGINEERS_VERTEX_H
#define ELECTRONICENGINEERS_VERTEX_H

#include "Vector2.h"
#include "Vector3.h"

class Vertex {
public:
	Vector2<float> pos = Vector2<float>(0);
	Vector3<float> color = Vector3<float>(0);
	Vertex(Vector2<float> pos, Vector3<float> color);
};


#endif