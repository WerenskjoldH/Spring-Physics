#pragma once
#define DT 0.003

#define BOUNDARY_DAMPENING -0.8
#define BOUNDARY_PADDING 0.005

#define GRAVITY_X 0.0
#define GRAVITY_Y -9.8

#define REST_LENGTH 0.05
#define SPRING_CONSTANT 3000
#define AIR_FRICTION 0.5
#define FRICTION_CONSTANT 0.2
#define PARTICLE_MASS 0.05

#define NUMBER_OF_SEGMENTS 8

#include "Vector.h"
#include <vector>

using namespace rn;

struct Particle
{
	// Use for static 
	Particle(vector3f position, int id)
	{
		identifier = id;

		mass = PARTICLE_MASS;

		acceleration = 0.f;

		this->position = position;
		this->velocity = velocity;
	}

	unsigned int identifier;

	std::vector<int> neighbors;

	float mass;

	vector3f position;
	vector3f velocity;
	vector3f evelocity;
	vector3f acceleration;
};

class Solver
{
private:
	// Variables


	// Methods
	void attract();
	void externalForces();
	void integrate();

public:
	// Variables
	vector3f gravity;
	int numParticles = 0;
	int worldSize_height, worldSize_width;

	std::vector<Particle*> particles;

	// Methods
	void initialize();
	
	void cleanup();

	void update();

	
	void addParticle(rn::vector3f pos);


	// Functions

};