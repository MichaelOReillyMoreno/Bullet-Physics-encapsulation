#include "Rigid_body.hpp"

Bullet_project::Rigid_body::Rigid_body(const std::shared_ptr<Shape>& shape, btVector3 position, float mass, float restitution) : shape(shape)
{
	btTransform transform;

	transform.setIdentity();
	transform.setOrigin(position);

	state.reset(new btDefaultMotionState(transform));

	if (mass > 0)
	{
		btVector3 localInertia(0, 0, 0);
		shape->Get()->calculateLocalInertia(mass, localInertia);
		btRigidBody::btRigidBodyConstructionInfo info(mass, state.get(), shape.get()->Get(), localInertia);
		body.reset(new btRigidBody(info));
	}
	else
	{
		btRigidBody::btRigidBodyConstructionInfo info(0, state.get(), shape.get()->Get());
		body.reset(new btRigidBody(info));
	}

	body->setRestitution(restitution);
}