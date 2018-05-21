#include "GL_scene.hpp"

#include "Game_object.hpp"

using namespace sf;

Bullet_project::GL_scene::GL_scene(int width, int height) 
:
	window
	(
		sf::VideoMode(width, height),
		"Bullet Rigid Bodies",
		sf::Style::Default,
		sf::ContextSettings(24, 0, 0, 3, 2, sf::ContextSettings::Core)
	)
{

	shared_ptr< Camera      > camera(new Camera(20.f, 1.f, 50.f, 1.f));
	camera->rotate_around_y(0.3f);

	shared_ptr< Light       > light(new Light);
	game_scene.add("camera", camera);
	game_scene.add("light", light);


	// Se determinan las características de OpenGL disponibles en la máquina:

	if (!glt::initialize_opengl_extensions())
	{
		exit(-1);
	}

	// Se activa la sincronización vertical:

	window.setVerticalSyncEnabled(true);
	running = true;
}

void Bullet_project::GL_scene::Configure_scene(glt::Vector3 camera_pos, glt::Vector3 light_pos)
{
	Render_Node & scene = game_scene;

	scene["light"]->translate(light_pos);
	scene["camera"]->translate(camera_pos);
}




void Bullet_project::GL_scene::Reset_viewport()
{
	GLsizei width = GLsizei(window.getSize().x);
	GLsizei height = GLsizei(window.getSize().y);

	game_scene.get_active_camera()->set_aspect_ratio(float(width) / height);

	glViewport(0, 0, width, height);
}

void Bullet_project::GL_scene::Update(/*FLOAT TIME*/)
{
	dynamic_world.Step(/*TIME*/);

	for (auto & game_object : game_objects)
	{
		game_object.second->Update();
	}
}

void Bullet_project::GL_scene::Render()
{
	game_scene.render();
	window.display();
}

void Bullet_project::GL_scene::Events_listener()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			running = false;
			break;
		}

		case sf::Event::Resized:
		{
			Reset_viewport();
			break;
		}
		}
	}
}
