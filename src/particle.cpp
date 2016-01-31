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
	m_Shapes(),
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
	for( std::vector< Vector2< long double > >::iterator i = this->movers.begin();
			i != this->movers.end(); i++ )
	{
		this->position += (*i);
	}
	this->movers.clear();

	for( std::vector< Vector2< long double > >::iterator i = this->impulses.begin();
			i != this->impulses.end(); i++ )
	{
		this->velocity += (*i) * deltaTime;
	}
	this->impulses.clear();

	this->position += this->velocity * deltaTime;

	this->speed = sqrt( this->velocity.x * this->velocity.x
		+ this->velocity.y * this->velocity.y );
	this->momentum = this->mass * this->speed;

	for( std::vector< Shape* >::iterator i = this->m_Shapes.begin();
			i != this->m_Shapes.end(); ++i )
	{
		(*i)->setPosition(
				(float)this->position.x - this->radius,
				(float)this->position.y - this->radius );
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

void Particle::AddShape( Shape *nShape )
{ //{{{
	if( nShape != 0 )
	{
		m_Shapes.push_back( nShape );
	}
	else
	{
		// TODO error
	}
} //}}}

Shape* Particle::GetShape()
{ //{{{
	if( m_Shapes.size() > 0 )
	{
		return m_Shapes.front();
	}
	return NULL;
	// TODO Error
} //}}}

