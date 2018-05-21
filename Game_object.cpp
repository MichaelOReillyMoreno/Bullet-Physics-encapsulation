
// COMENTARIO DE CABECERA

#include "Game_object.hpp"
#include "GL_scene.hpp"
#include "Shape.hpp"

Bullet_project::Game_object::Game_object(GL_scene & scene) : scene(scene)
{
}

void Bullet_project::Game_object::Update()
{
	btTransform physics_transform;

	for (auto & body : bodies)
	{
		body.rigid_body->Get_world_transform(physics_transform);

		glm::mat4 graphics_transform;

		physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));

		body.graphics_model->set_transformation(graphics_transform);
		body.graphics_model->scale(body.graphics_scale.getX(), body.graphics_scale.getY(), body.graphics_scale.getZ());
	}
}

void Bullet_project::Game_object::Add_body(const string & name, const string & model_obj, const shared_ptr< Shape > & shape, btVector3 position, float restitution, float mass, btVector3 scale)
{
	shared_ptr< glt::Model_Obj > graphics_model(new glt::Model_Obj{ model_obj });
	scene.Add_model_obj_to_game_scene(name, graphics_model);

	shared_ptr< Rigid_body > rigid_body(new Rigid_body{ shape, position, mass, restitution });
	scene.Add_rigid_body_to_dynamic_world(rigid_body);

	bodies.push_back({ graphics_model, rigid_body, scale });

}

void Bullet_project::Game_object::rotate_body(size_t num_body, float yaw, float pitch, float roll)
{
	bodies[num_body].rigid_body->Rotate(yaw, pitch, roll);
	bodies[num_body].graphics_model->rotate_around_x(pitch);
	bodies[num_body].graphics_model->rotate_around_y(yaw);
	bodies[num_body].graphics_model->rotate_around_z(roll);
}

void Bullet_project::Game_object::Add_constraint(Rigid_body & rb_1, Rigid_body & rb_2, float min, float max)
{
	btTransform transform_rb_1 = rb_1.Get_body()->getCenterOfMassTransform();
	btTransform transform_rb_2 = rb_2.Get_body()->getCenterOfMassTransform();

	shared_ptr< btHingeConstraint > constrait(new btHingeConstraint( *rb_1.Get_body(), *rb_2.Get_body(), transform_rb_1, transform_rb_2 ));
	constrait->setLimit(min, max);

	constrains.push_back(constrait);
	scene.Add_constraint_to_dynamic_world(constrains.back());
}

void Bullet_project::Game_object::Disable_deactivation()
{
	for (auto & body : bodies)
		body.rigid_body->Disable_deactivation();
}