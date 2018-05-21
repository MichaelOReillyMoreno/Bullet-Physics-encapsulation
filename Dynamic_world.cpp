#include "Dynamic_world.hpp"
#include "Rigid_body.hpp"
#include"GL_scene.hpp"

Bullet_project::Dynamic_world::Dynamic_world() : collisionDispatcher(&collisionConfiguration),
							   world(shared_ptr<btDiscreteDynamicsWorld>( new btDiscreteDynamicsWorld
																		(   &collisionDispatcher,
																			&overlappingPairCache,
																			&constraintSolver,
																			&collisionConfiguration)))
{
	world->setGravity(btVector3(0, -10, 0));
}

void Bullet_project::Dynamic_world::Add_rigid_body(shared_ptr< Rigid_body > rb)
{
		world->addRigidBody(rb->Get_body().get());
		rigid_bodies.push_back(rb);
}

void Bullet_project::Dynamic_world::Add_constraint(shared_ptr< btHingeConstraint > constraint)
{
	world->addConstraint(constraint.get());
	constraints.push_back(constraint);

}

void Bullet_project::Dynamic_world::Step()
{
	world->stepSimulation(1.f / 60.f);
}

void Bullet_project::Dynamic_world::Reset()
{
	world.reset();
}