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
module main;

import tango.util.log.Log;
import tango.util.log.AppendConsole;
import tango.math.Math;

import tango.io.Stdout;
import display;
import particle;
import particle_system;
import entities.point;
import forces.gravity;
import forces.repel;

Logger log;
static this()
{
	log = Log.lookup( "main" );
	log.add( new AppendConsole() );
}

int main( char[][] )
{
	Stdout.formatln( "Welcome to Universum Meum." );

	log.info( "Creating a Display" );
	Display m_Display = Display.Instance( 800, 600, 32 );
	m_Display.TickInterval = 1000 / 100;

	log.info( "Creating a gravity force" );
	Gravity m_Gravity = Gravity.Instance();

	log.info( "Creating a repel force" );
	Repel m_Repel = Repel.Instance();

	log.info( "Now a particle system and some particles" );
	ParticleSystem m_ParticleSystem = new ParticleSystem();
	Particle[ 5 ] m_Particles;

	log.info( "Now creating an array of points" );
	Point[ 5 ] m_Points;
	m_Points[ 0 ] = new Point( 200.0f, 150.0f, 10.0f, 1.0f, 0.0f, 0.0f );
	m_Points[ 1 ] = new Point( 600.0f, 150.0f, 10.0f, 0.0f, 1.0f, 0.0f );
	m_Points[ 2 ] = new Point( 200.0f, 450.0f, 10.0f, 0.0f, 0.0f, 1.0f );
	m_Points[ 3 ] = new Point( 600.0f, 450.0f, 10.0f, 0.0f, 0.0f, 0.0f );
	m_Points[ 4 ] = new Point( 500.0f, 300.0f, 10.0f, 1.0f, 0.0f, 1.0f );

	log.info( "Adding each point to display" );
	foreach( i; m_Points )
	{
		m_Display.AddEntity( i );
	}

	log.info( "Setting up each particle" );
	for( uint i = 0; i < 5; ++i )
	{
		m_Particles[ i ] = new Particle();
		m_Particles[ i ].AddEntity( m_Points[ i ] );
		m_Particles[ i ].Radius = 10.0f;
		m_Particles[ i ].AddForce( m_Gravity );
		m_Particles[ i ].AddForce( m_Repel );
		m_ParticleSystem.AddParticle( m_Particles[ i ] );
	}

	m_Particles[ 0 ].Position( 200.0f, 150.0f );
	m_Particles[ 1 ].Position( 600.0f, 150.0f );
	m_Particles[ 2 ].Position( 200.0f, 450.0f );
	m_Particles[ 3 ].Position( 600.0f, 450.0f );
	m_Particles[ 4 ].Position( 500.0f, 300.0f );

			for( uint i = 0; i < 4; ++i )
			{
				Stdout.formatln( "{}: < {}, {} >", i,
					m_Particles[ i ].XPosition, m_Particles[ i ].YPosition );
			}

	Point m_Point = new Point( 400, 300, 25, 1.0f, 1.0f, 1.0f );
	m_Display.AddEntity( m_Point );

	log.info( "Entering main game loop" );
	uint cnt = 0;
	float nX = 1.0f;
	float rad = 0.0f;
	while( !m_Display.isDone )
	{
		cnt++;
		if( cnt > 200 )
		{
			cnt=0;
			for( uint i = 0; i < 5; ++i )
			{
				Stdout.formatln( "{}: < {}, {} >", i,
					m_Particles[ i ].XPosition, m_Particles[ i ].YPosition );
			}
		}

		nX += 2.0f;
		if( nX > 600.0f )
		{
			nX = 2.0f;
		}
		m_Points[ 0 ].X = nX;

		m_Display.ProcessInput();

		if( !m_Display.isActive )
		{
			m_Particles[ 0 ].Position( 200.0f, 150.0f );
			m_Particles[ 1 ].Position( 600.0f, 150.0f );
			m_Particles[ 2 ].Position( 200.0f, 450.0f );
			m_Particles[ 3 ].Position( 600.0f, 450.0f );

			m_Particles[ 0 ].Velocity( 0.0f, 0.0f );
			m_Particles[ 1 ].Velocity( 0.0f, 0.0f );
			m_Particles[ 2 ].Velocity( 0.0f, 0.0f );
			m_Particles[ 3 ].Velocity( 0.0f, 0.0f );

			m_Particles[ 0 ].Acceleration( 0.0f, 0.0f );
			m_Particles[ 1 ].Acceleration( 0.0f, 0.0f );
			m_Particles[ 2 ].Acceleration( 0.0f, 0.0f );
			m_Particles[ 3 ].Acceleration( 0.0f, 0.0f );
		}

		m_ParticleSystem.Work();

		rad -= 0.01f;
		rad %= 2 * PI;

		m_Particles[ 4 ].Position( 100.0f * cos( rad ) + 400.0f, 100.0f * sin( rad ) + 300.0f );

		m_Display.Draw();
		m_Display.WaitFor();
	}

	Stdout.formatln( "Thanks for playing!" );
	return 0;
}
