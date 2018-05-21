#pragma once
#ifndef DYNAMIC_WORLD
#define DYNAMIC_WORLD

#include <btBulletDynamicsCommon.h>
#include <vector>
#include <memory>

using namespace std;

namespace Bullet_project
{
	class Rigid_body;

	//representa el mundo fisico de bullet y sus distintas utilidades y configuracion
	class Dynamic_world
	{

	private:

		//configuracion de las colisiones
		btDefaultCollisionConfiguration collisionConfiguration;

		//gestor de las colisiones
		btCollisionDispatcher collisionDispatcher;

		btDbvtBroadphase overlappingPairCache;
		btSequentialImpulseConstraintSolver constraintSolver;

		//mundo fisico de bullet
		shared_ptr< btDiscreteDynamicsWorld > world;

		//rigid bodies de la escena
		vector< shared_ptr< Rigid_body > > rigid_bodies;

		//constraints de la escena
		vector< shared_ptr< btHingeConstraint > > constraints;
	public:

		Dynamic_world();

		//añade un cuerpo rigido a la escena
		void Add_rigid_body(shared_ptr< Rigid_body > rb);

		//añade una constraint a la escena
		void Add_constraint(shared_ptr< btHingeConstraint > constraint);

		//actualiza todos los cuerpos rigidos de la escena
		void Step();

		//resetea el mundo fisico
		void Reset();
	};
}
#endif