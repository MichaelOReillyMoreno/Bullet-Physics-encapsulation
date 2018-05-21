
#pragma once
#ifndef SHAPE
#define SHAPE

#include "Dynamic_world.hpp"

using namespace std;

namespace Bullet_project
{
	//clase base para las distintas shapes de la escena 
	class Shape
	{

	public:

		shared_ptr< btCollisionShape > bt_shape;

	public:

		virtual ~Shape() = default;

		Shape(std::shared_ptr< btCollisionShape > & shape) : bt_shape(shape){}

		//devuelve un puntero a la shape propia de bullet
		btCollisionShape * Get()
		{
			return bt_shape.get();
		}

	};
}
#endif