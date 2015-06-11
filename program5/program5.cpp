//Replace with your usernames!
#define printusers() printf("Program by Fryjc and Veatchje\n");

#define GLEW_STATIC
#include <stdio.h>
#include <stdlib.h>
#include "glew/glew.h"
#include <SFML/Window.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ShaderManager.h"
#include "GLHelper.h"
#include "RenderEngine.h"
#include "Maze.h"
#include "MazeModel.h"

#define RESOLUTION 1080
#define TARGET_FPS 30                // controls spin update rate
#define TIME_WINDOW 3                // number of frames motion is valid after release


class Program4
{
public:
	glm::vec3 location;

	float directionX;
	float directionY;

	bool out;
	glm::mat4 rotate;
	glm::mat4 translate;

	Program4(unsigned int const & w, unsigned int const & h)
	{
		App = new sf::Window(sf::VideoMode(RESOLUTION, RESOLUTION, 32), "program5");
		render.init(w, h);
		step = 2;
		location = glm::vec3(-5.0f*render.model.getUnitSize(), 0.5*render.h*render.model.getUnitSize(), 0.5*render.model.getUnitSize());
		directionX = 1.0f;
		directionY = 0.0f;
		out = false;
		rotate = glm::mat4(1);
		translate=glm::mat4(1);

		while (App->IsOpened())
		{			
			App->SetActive();
			float targetFrameTime = 1.0f/(float)TARGET_FPS;
			float sleepTime = targetFrameTime - App->GetFrameTime();
			if(sleepTime > 0)
				sf::Sleep(sleepTime);
			render.setTransform(glm::translate(glm::mat4(1), glm::vec3(0,0, -1.9)));
			render.display();
			App->Display();
			handleEvents();
		}
	}

	// *glm::rotate(translate*rotate*glm::mat4(1), (float)-90., glm::vec3(1, 0, 0))*glm::rotate(glm::mat4(1), (float)-90., glm::vec3(0, 1, 0))
	~Program4()
	{
	}
	void toggleView(){
		if (out){
			render.setView(glm::lookAt(location, glm::vec3(location.x + directionX, location.y+directionY,location.z), glm::vec3(0.0f, 0.0f, 1.0f)));
			render.setProjection(glm::perspective(120.0f, 1.0f, 0.1f*render.model.getUnitSize(), 2.0f*render.w*render.model.getUnitSize()));
		}
		else{
			render.setView(glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0)));
			render.setProjection(glm::ortho(-render.model.getUnitSize(), (render.w + 1)*render.model.getUnitSize(), -render.model.getUnitSize(), (render.h + 1)*render.model.getUnitSize()));
		}
		out = !out;
	}
	void turnLeft(){
		if (directionX ==0){
			if (directionY == 1){
				directionY = 0.0f;
				directionX = -1.0f;
			}
			else{
				directionY = 0.0f;
				directionX = 1.0f;
			}
		}
		else{
			if (directionX == 1){
				directionX = 0.0f;
				directionY = 1.0f;
			}
			else{
				directionX = 0.0f;
				directionY = -1.0f;
			}
		}
	}
	void turnRight(){
		if (directionX == 0){
			if (directionY == 1){
				directionY = 0.0f;
				directionX = 1.0f;
			}
			else{
				directionY = 0.0f;
				directionX = -1.0f;
			}
		}
		else{
			if (directionX == 1){
				directionX = 0.0f;
				directionY = -1.0f;
			}
			else{
				directionX = 0.0f;
				directionY = 1.0f;
			}
		}

	}
	void forward(){
		location = glm::vec3(location.x+directionX*render.model.getUnitSize()*0.5,location.y+ directionY*render.model.getUnitSize()*0.5,location.z);
	}
	
private:
	sf::Window *App;
	RenderEngine render;
	unsigned int step;

	void handleEvents()
	{
		const sf::Input& Input = App->GetInput();
		bool shiftDown = Input.IsKeyDown(sf::Key::LShift) || Input.IsKeyDown(sf::Key::RShift);
		sf::Event Event;
		while (App->GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed)
				App->Close();
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				App->Close();
			
			// This is for grading your code. DO NOT REMOVE
			if(Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Equal)
			{
				unsigned char *dest;
				unsigned int w = App->GetWidth();
				unsigned int h = App->GetHeight();
				glPixelStorei(GL_PACK_ALIGNMENT, 1);
				dest = (unsigned char *) malloc( sizeof(unsigned char)*w*h*3);
				glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, dest);
				
				FILE *file;
				file = fopen("_program1.ppm", "wb");
				fprintf(file, "P6\n%i %i\n%i\n", w, h, 255);
				for(int i=h-1; i>=0; i--)
					fwrite(&dest[i*w*3], sizeof(unsigned char), w*3, file);
				fclose(file);
				free(dest);
			}
			
			if (Event.Type == sf::Event::Resized)
			{ glViewport(0, 0, Event.Size.Width, Event.Size.Height); }
			if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Up)
			{
				this->forward();
				if (!out){
					render.setView(glm::lookAt(location, glm::vec3(location.x + directionX, location.y + directionY, location.z), glm::vec3(0.0f, 0.0f, 1.0f)));
				}
			}
			if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Left)
			{
				this->turnLeft();
				if (!out){
					render.setView(glm::lookAt(location, glm::vec3(location.x + directionX, location.y + directionY, location.z), glm::vec3(0.0f, 0.0f, 1.0f)));
				}
			}
			if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Right)
			{
				this->turnRight();
				if (!out){
					render.setView(glm::lookAt(location, glm::vec3(location.x + directionX, location.y + directionY, location.z), glm::vec3(0.0f, 0.0f, 1.0f)));
				}
			}
			if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::LControl)
			{
				this->toggleView();
			}
			if(Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Space)
			{
				render.generateMaze(step);
				step++;
				location = glm::vec3(-5.0f*render.model.getUnitSize(), 0.5*render.h*render.model.getUnitSize(), 0.5*render.model.getUnitSize());
			}

		}
	}
};

int main(int argc, char ** argv)
{
	printusers();
	
	/* check that there are sufficient arguments */
	unsigned int w;
	unsigned int h;
	if (argc < 3) {
		w = 6;
		h = 6;
		fprintf(stderr, "The width and height can be specified as command line arguments. Defaulting to %i %i\n", w, h);
	}
	else {
		w = atoi(argv[1]);
		h = atoi(argv[2]);
	}
	
	Program4 prog(w, h);
	
    return EXIT_SUCCESS;
}
