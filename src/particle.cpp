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

Particle::Particle()
{ //{{{
	mass = 20.0f;
	radius = 0.0f;
	m_Acceleration.Zero();
	m_Velocity.Zero();
	m_Position.Zero();

	m_nextAcceleration.Zero();
	m_nextVelocity.Zero();
	m_nextPosition.Zero();
	speed = 0.0f;
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
	m_nextVelocity.x += m_nextAcceleration.x * deltaTime;
	m_nextVelocity.y += m_nextAcceleration.y * deltaTime;

	m_nextPosition.x += m_nextVelocity.x * deltaTime;
	m_nextPosition.y += m_nextVelocity.y * deltaTime;

	m_nextAcceleration.x = 0.0;
	m_nextAcceleration.y = 0.0;

	m_Acceleration.x = m_nextAcceleration.x;
	m_Acceleration.y = m_nextAcceleration.y;

	m_Velocity.x = m_nextVelocity.x;
	m_Velocity.y = m_nextVelocity.y;

	m_Position.x = m_nextPosition.x;
	m_Position.y = m_nextPosition.y;

	this->speed = sqrt( XVelocity()*XVelocity() + YVelocity()*YVelocity() );
	this->momentum = this->mass * this->speed;

	for( std::vector< Entity* >::iterator i = m_Entities.begin(); i != m_Entities.end(); ++i )
	{
		(*i)->position.x = XPosition();
		(*i)->position.y = YPosition();
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

/// Return first entity in m_Entities or null if there are none.
Entity* Particle::GetEntity()
{ //{{{
	if( m_Entities.size() > 0 )
	{
		return m_Entities.front();
	}
	// TODO Error
} //}}}

// Position stuff
//{{{
// {G,S}etter for current XPosition
long double Particle::XPosition() //{{{
{
	return m_Position.x;
}
void Particle::CurrentXPosition( long double nXPosition )
{
	m_Position.x = nXPosition;
	m_nextPosition.x = nXPosition;
	for( std::vector< Entity* >::iterator i = m_Entities.begin(); i != m_Entities.end(); ++i )
	{
		(*i)->position.x = nXPosition;
	}
} //}}}

// {G,S}etter for current YPosition
long double Particle::YPosition() //{{{
{
	return m_Position.y;
}
void Particle::CurrentYPosition( long double nYPosition )
{
	m_Position.y = nYPosition;
	m_nextPosition.y = nYPosition;
	for( std::vector< Entity* >::iterator i = m_Entities.begin(); i != m_Entities.end(); i++ )
	{
		(*i)->position.y = nYPosition;
	}
} //}}}

// Setter for both current Positions
void Particle::CurrentPositions( long double nXPosition, long double nYPosition) //{{{
{
	m_Position.x = nXPosition;
	m_Position.y = nYPosition;
	m_nextPosition.x = nXPosition;
	m_nextPosition.y = nYPosition;
	for( std::vector< Entity* >::iterator i = m_Entities.begin(); i != m_Entities.end(); i++ )
	{
		(*i)->position.x = nXPosition;
		(*i)->position.y = nYPosition;
	}
} //}}}


// {G,S}etter for next XPosition
long double Particle::NextXPosition() //{{{
{
	return m_nextPosition.x;
}
void Particle::XPosition( long double nXPosition )
{
	m_nextPosition.x = nXPosition;
} //}}}

// {G,S}etter for next YPosition
long double Particle::NextYPosition() //{{{
{
	return m_nextPosition.y;
}
void Particle::YPosition( long double nYPosition )
{
	m_nextPosition.y = nYPosition;
} //}}}

// Setter for both next Positions
void Particle::Positions( long double nXPosition, long double nYPosition ) //{{{
{
	XPosition( nXPosition );
	YPosition( nYPosition );
} //}}}
//}}}

// Velocity stuff
//{{{
// {G,S}etter for current XVelocity
long double Particle::XVelocity() //{{{
{
	return m_Velocity.x;
}
void Particle::CurrentXVelocity( long double nXVelocity )
{
	m_Velocity.x = nXVelocity;
	this->speed = sqrt( nXVelocity*nXVelocity + YVelocity()*YVelocity() );
} //}}}

// {G,S}etter for current YVelocity
long double Particle::YVelocity() //{{{
{
	return m_Velocity.y;
}
void Particle::CurrentYVelocity( long double nYVelocity )
{
	m_Velocity.y = nYVelocity;
	this->speed = sqrt( XVelocity()*XVelocity() + nYVelocity*nYVelocity );
} //}}}

// Setter for both current Velocitys
void Particle::CurrentVelocities( long double nXVelocity, long double nYVelocity) //{{{
{
	m_Velocity.x = nXVelocity;
	m_Velocity.y = nYVelocity;
	this->speed = sqrt( nXVelocity*nXVelocity + nYVelocity*nYVelocity );
} //}}}


// {G,S}etter for next XVelocity
long double Particle::NextXVelocity() //{{{
{
	return m_nextVelocity.x;
}
void Particle::XVelocity( long double nXVelocity )
{
	m_nextVelocity.x = nXVelocity;
} //}}}

// {G,S}etter for next YVelocity
long double Particle::NextYVelocity() //{{{
{
	return m_nextVelocity.y;
}
void Particle::YVelocity( long double nYVelocity )
{
	m_nextVelocity.y = nYVelocity;
} //}}}

// Setter for both next Velocitys
void Particle::Velocities( long double nXVelocity, long double nYVelocity ) //{{{
{
	XVelocity( nXVelocity );
	YVelocity( nYVelocity );
} //}}}

// Setter for both next Velocitys
void Particle::Velocities( Vector< long double > nVelocity ) //{{{
{
	XVelocity( nVelocity.x );
	YVelocity( nVelocity.y );
} //}}}
//}}}

// Acceleration stuff
//{{{
// {G,S}etter for current XAcceleration
long double Particle::XAcceleration() //{{{
{
	return m_Acceleration.x;
}
void Particle::CurrentXAcceleration( long double nXAcceleration )
{
	m_Acceleration.x = nXAcceleration;
} //}}}

// {G,S}etter for current YAcceleration
long double Particle::YAcceleration() //{{{
{
	return m_Acceleration.y;
}
void Particle::CurrentYAcceleration( long double nYAcceleration )
{
	m_Acceleration.y = nYAcceleration;
} //}}}

// Setter for both current Accelerations
void Particle::CurrentAccelerations( long double nXAcceleration, long double nYAcceleration) //{{{
{
	m_Acceleration.x = nXAcceleration;
	m_Acceleration.y = nYAcceleration;
} //}}}


// {G,S}etter for next XAcceleration
long double Particle::NextXAcceleration() //{{{
{
	return m_nextAcceleration.x;
}
void Particle::XAcceleration( long double nXAcceleration )
{
	m_nextAcceleration.x = nXAcceleration;
} //}}}

// {G,S}etter for next YAcceleration
long double Particle::NextYAcceleration() //{{{
{
	return m_nextAcceleration.y;
}
void Particle::YAcceleration( long double nYAcceleration )
{
	m_nextAcceleration.y = nYAcceleration;
} //}}}

// Setter for both next Accelerations
void Particle::Accelerations( long double nXAcceleration, long double nYAcceleration ) //{{{
{
	XAcceleration( nXAcceleration );
	YAcceleration( nYAcceleration );
} //}}}
//}}}

#endif // "PARTICLE_CPP"
