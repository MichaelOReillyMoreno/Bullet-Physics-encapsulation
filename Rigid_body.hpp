#pragma once
#ifndef RIGID_BODY
#define RIGID_BODY

#include <memory>

#include "Shape.hpp"

using namespace std;

namespace Bullet_project
{
	class Rigid_body
	{
	private:

		std::shared_ptr< btRigidBody 		  > body;
		std::shared_ptr< btDefaultMotionState > state;
		std::shared_ptr< Shape   			  > shape;

	public:

		Rigid_body(const std::shared_ptr< Shape > & shape, btVector3 position, float mass, float restitution);

		void Get_world_transform(btTransform & transform)
		{
			body->getMotionState()->getWorldTransform(transform);
		}

		virtual ~Rigid_body() = default;

		void Rotate(float yaw, float pitch, float roll)
		{
			//btTransform tr;

			btQuaternion quat;

			quat.setEuler(yaw, pitch, roll);
			//tr.setRotation(quat);
			body->getWorldTransform().setRotation(quat);
			//body->setCenterOfMassTransform(tr);
		}

		void Disable_deactivation()
		{
			body->setActivationState(DISABLE_DEACTIVATION);
		}

		std::shared_ptr< btRigidBody > Get_body()
		{
			return body;
		}
	};

}
#endif