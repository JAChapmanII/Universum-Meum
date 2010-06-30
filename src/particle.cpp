/* {{{
	Copyright 2010 Jeff Chapman (and Nolan Brown)

	This file is a part of Universum Meum

	Universum Meum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Universum Meum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Universum Meum.  If not, see <http://www.gnu.org/licenses/>.

*/// }}}
#ifndef PARTICLE_CPP
#define PARTICLE_CPP

#include "particle.hpp"

typedef void( *Force )( Particle*, Particle*, long double );

Particle::Particle() :
	mass( 20.0 ), //{{{
	radius( 0.0 ),
	speed( 0.0 ),
	momentum( 0.0 ),
	position(),
	velocity(),
	movers(),
	impulses(),
	m_Entities(),
	m_Forces()
{
} //}}}

Particle::~Particle()
{
}

void Particle::Work( Particle* B, long double deltaTime )
{ //{{{
	for( std::vector< Force* >::iterator i = m_Forces.begin(); i != m_Forces.end(); i++ )
	{
		if( (*i) != 0 )
		{
			(*(*i))( this, B, deltaTime );
		}
	}
} //}}}

void Particle::Update( long double deltaTime )
{ //{{{
	for( std::vector< Vector< long double > >::iterator i = this->movers.begin();
			i != this->movers.end(); i++ )
	{
		this->position += (*i);
	}
	this->movers.clear();

	for( std::vector< Vector< long double > >::iterator i = this->impulses.begin();
			i != this->impulses.end(); i++ )
	{
		this->velocity += (*i) * deltaTime;
	}
	this->impulses.clear();

	this->position += this->velocity * deltaTime;

	this->speed = this->velocity.Magnitude();
	this->momentum = this->mass * this->speed;

	for( std::vector< Entity* >::iterator i = this->m_Entities.begin();
			i != this->m_Entities.end(); ++i )
	{
		(*i)->position = this->position;
	}

} //}}}

void Particle::AddForce( Force *nForce )
{ //{{{
	if( nForce != 0 )
	{
		m_Forces.push_back( nForce );
	}
	else
	{
		// TODO Error
	}
} //}}}

void Particle::AddEntity( Entity *nEntity )
{ //{{{
	if( nEntity != 0 )
	{
		m_Entities.push_back( nEntity );
	}
	else
	{
		// TODO error
	}
} //}}}

Entity* Particle::GetEntity()
{ //{{{
	if( m_Entities.size() > 0 )
	{
		return m_Entities.front();
	}
	return NULL;
	// TODO Error
} //}}}

#endif // "PARTICLE_CPP"
