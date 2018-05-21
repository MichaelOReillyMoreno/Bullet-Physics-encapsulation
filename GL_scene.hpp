#pragma once
#ifndef SCENE
#define SCENE

#include <map>
#include <memory>
#include <OpenGL.hpp>
#include <Light.hpp>
#include <Model.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>
#include <iostream>
#include <SFML/Window.hpp>

#include"Rigid_body.hpp"

#include"Box_shape.hpp"
#include"Cilindre_shape.hpp"
#include"Sphere_shape.hpp"

using namespace std;
using namespace glt;


namespace Bullet_project
{

	class Game_object;

	//Representa la escena del juego contiene todo lo necesario para su funcionamiento, mundo fisico, ventana, renderizador 3d...
	class GL_scene
	{

	private:
	
		//mundo dinamicos
		Dynamic_world dynamic_world;

		//renderizador de modelos 3d
		Render_Node   game_scene;

		//ventana del programa en sfml
		sf::Window    window;

		//gmae objects de la escena
		map< string, shared_ptr< Game_object > > game_objects;

		//mientras no se cierre la ventana esta corriendo
		bool running;

	public:

		GL_scene(int width, int height);

		//configurador de la escena 
		void Configure_scene(glt::Vector3 camera_pos, glt::Vector3 light_pos);

		//añade un game object a la escena
		void Add_game_object(const string & name, shared_ptr< Game_object > & game_object)
		{
			game_objects[name] = game_object;
		}

		//añade un modelo 3d a la escena para renderizarlo
		void Add_model_obj_to_game_scene(const string & name, const shared_ptr< Model_Obj > & model_obj)
		{
			game_scene.add (name, model_obj);
		}

		//añade un rigid body al mundo dinamico, necesario para que le afecten las fisicas
		void Add_rigid_body_to_dynamic_world(shared_ptr< Rigid_body > rb)
		{
			dynamic_world.Add_rigid_body(rb);
		}

		//añade una constraint al mundo dinamico
		void Add_constraint_to_dynamic_world(shared_ptr< btHingeConstraint > constraint)
		{
			dynamic_world.Add_constraint(constraint);
		}

		//devuelve una referencia a un game object de la escena. Lo busca por si nombre en el mapa de game objects
		Game_object * Get_game_object(const string & name)
		{
			if (game_objects.count(name) > 0)
			{
				return game_objects[name].get();
			}

			return nullptr;
		}

		//resetea el viewport
		void Reset_viewport();

		void Update();
		void Render();
		void Reset() { dynamic_world.Reset(); }
		void Events_listener();

		//devuelve true si el juego siguie corriendo, es decir, no se ha cerrado la ventana
		bool Is_running() { return running; }

	};
}
#endif