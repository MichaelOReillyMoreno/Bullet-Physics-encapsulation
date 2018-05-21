
#pragma once
#ifndef CILINDRE_SHAPE
#define CILINDRE_SHAPE

#include "Shape.hpp"

using namespace std;

namespace Bullet_project
{
	//representa una shape en forma de capsula 
	class Capsule_Shape : public Shape
	{
	public:

		Capsule_Shape(float radius, float height) :Shape(shared_ptr< btCollisionShape >(new btCapsuleShape(btScalar(radius), btScalar(height)))) {}
	};
}
#endif