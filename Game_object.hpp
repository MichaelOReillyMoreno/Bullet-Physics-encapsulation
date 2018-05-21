
// COMENTARIO DE CABECERA

#pragma once

#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <Model_Obj.hpp>

#include "Rigid_body.hpp"

using namespace std;

namespace Bullet_project
{
	//estructura que contiene todos los parametros que componen un cuerpo de un game object
	struct Body
	{
		shared_ptr< glt::Model_Obj > graphics_model;
		shared_ptr< Rigid_body     > rigid_body;
		btVector3 graphics_scale;
	};

	class GL_scene;

	//clase que representa un game object de la escena, es decir un conjunto de bodies y constrains
	class Game_object
	{

	protected:

		//referencia a la escena
		GL_scene & scene;
		
		//conjunto de bodies del  game object 
		vector< Body > bodies;

		//conjunto de constrains del  game object 
		vector< shared_ptr< btHingeConstraint > > constrains;

	public:

		Game_object(GL_scene & scene);
		virtual ~Game_object() {}

		//actuliza los componentes del game object
		void Update();

		//añade un nuevo cuerpo al game object
		void Add_body(const string & name, const string & model_obj, const shared_ptr< Shape > & shape, btVector3 position, float restitution, float mass, btVector3 scale);
		
		//rota un cuerpo determinado del game object
		void rotate_body(size_t num_body, float yaw, float pitch, float roll);

		//añade una nueva constraint al game object
		void Add_constraint(Rigid_body & rb_1, Rigid_body & rb_2, float min, float max);

		//desactiva que este game object se pueda "desactivar" al quedarse quiero
		void Disable_deactivation();

	};
}
#endif