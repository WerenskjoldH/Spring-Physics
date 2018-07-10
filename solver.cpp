#include "solver.h"

void Solver::initialize()
{
	worldSize_width = 1.0f;
	worldSize_height = 1.0f;

	gravity.x = GRAVITY_X;
	gravity.y = GRAVITY_Y;
}

void Solver::update()
{
	attract();
	externalForces();
	integrate();
}

void Solver::attract()
{
	vector3f jointVec(0,0,0), force(0,0,0);
	float mag = 0.f;
	for (std::vector<Particle*>::iterator it1 = particles.begin(); it1 != particles.end(); it1++)
	{
		Particle* p1 = *it1;

		for (std::vector<int>::iterator it2 = p1->neighbors.begin(); it2 != p1->neighbors.end(); it2++)
		{
			Particle* p2 = particles[*it2];

			// Spring
			jointVec = p1->position - p2->position;

			mag = jointVec.magnitude();

			if (mag != 0)
				force += jointVec.unit() * -1.f * (mag - REST_LENGTH) * SPRING_CONSTANT;

			force += (p1->velocity - p2->velocity) * -1.f * FRICTION_CONSTANT;

			p1->acceleration += force;
			p2->acceleration += force * -1;

			force = 0.f;
			mag = 0.f;
		}
	}
}

void Solver::externalForces()
{
	for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); it++)
	{
		Particle* p = *it;

		p->acceleration.x += GRAVITY_X;
		p->acceleration.y += GRAVITY_Y;

		p->acceleration += p->velocity * -1.f * AIR_FRICTION;
	}
}

void Solver::integrate()
{
	for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); it++)
	{
		Particle* p = *it;
		if (p->identifier == 0)
			continue;

		p->velocity += (p->acceleration / p->mass) * DT;
		p->position += p->velocity * DT;

		if (p->position.x < 0.f)
		{
			p->velocity.x *= BOUNDARY_DAMPENING;
			p->position.x = 0;
		}
		
		if (p->position.x >= worldSize_width)
		{
			p->velocity.x *= BOUNDARY_DAMPENING;
			p->position.x = worldSize_width;
		}

		if (p->position.y < 0.f)
		{
			p->velocity.y *= BOUNDARY_DAMPENING;
			p->position.y = 0;
		}

		if (p->position.y >= worldSize_height)
		{
			p->velocity.y *= BOUNDARY_DAMPENING;
			p->position.y = worldSize_height;
		}
		
		p->acceleration = 0.f;
	}
}

void Solver::addParticle(rn::vector3f pos)
{
	particles.push_back(new Particle(pos, numParticles));
	particles[numParticles]->mass = PARTICLE_MASS;
	if(numParticles-1 >= 0)
		particles[numParticles]->neighbors.push_back(particles[numParticles-1]->identifier);
	numParticles++;
}

void Solver::cleanup()
{
	particles.clear();
	numParticles = 0;
}