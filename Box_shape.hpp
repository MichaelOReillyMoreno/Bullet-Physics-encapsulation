
#pragma once
#ifndef BOX_SHAPE
#define BOX_SHAPE

#include "Shape.hpp"

using namespace std;

namespace Bullet_project
{
	//representa una shape de forma rectangular 
	class Box_Shape : public Shape
	{
	public:

		Box_Shape(float width, float height, float lenght):Shape(shared_ptr< btCollisionShape >(new btBoxShape(btVector3(width, height, lenght)))){}
	};
}
#endif