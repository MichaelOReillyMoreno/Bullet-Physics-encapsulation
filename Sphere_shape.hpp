
#pragma once
#ifndef SHPERE_SHAPE
#define SHPERE_SHAPE

#include "Shape.hpp"

using namespace std;

namespace Bullet_project
{
	//shape de forma esferica
	class Sphere_Shape : public Shape
	{
	public:

		Sphere_Shape(float radius) :Shape(shared_ptr< btCollisionShape >(new btSphereShape(btScalar(radius)))) {}
	};
}
#endif