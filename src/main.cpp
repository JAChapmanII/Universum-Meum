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

#include <iostream>
using std::cout;
using std::cin;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <limits>
using std::numeric_limits;

#include <cstdlib>
#include <cmath>

#include <SFML/Graphics.hpp>
// Using declarations for SFML {{{
using sf::RenderWindow;
using sf::VideoMode;
using sf::Shape;
using sf::Color;
using sf::Event;
using sf::Input;
using sf::View;
using sf::Vector2f;
using sf::Clock;
// }}}

#include "particle.hpp"
#include "particle_system.hpp"
#include "forces/exterior/gravity.cpp"
#include "forces/exterior/collapse.cpp"
#include "forces/interior/repel.cpp"
#include "forces/colliding/elastic_collision.cpp"

const unsigned int MAX_PARTICLES = 1000;

void CreateParticle( vector< Shape* > *m_Shapes, vector< Particle* > *m_Particles,
		ParticleSystem *m_ParticleSystem, vector< Particle::Force* > *m_Forces,
		RenderWindow *m_Game, int initVel, Vector2< long double > iPosition );

void CreateParticles( vector< Shape* > *m_Shapes, vector< Particle* > *m_Particles,
		ParticleSystem *m_ParticleSystem, vector< Particle::Force* > *m_Forces,
		RenderWindow *m_Game, int initVel, int numObjects );

Vector2< long double > detVelocity( unsigned int type = 0 );

int main( int argc, const char* argv[] )
{
	cout << "Welcome to Universum Meum.\n";

	/* TODO This doesn't exactly happen anymore...
	cout << "Creating random number generator\n" ;
	//auto rand = new Twister();
	//rand.seed();
	*/

	unsigned int gWidth = 0, gHeight = 0;
	while( ( gWidth <= 0 ) || ( gWidth > 2560 ) )
	{
		cout << "\nPlease enter a (0<) width (<=2560): ";
			cin >> gWidth;
	}
	while( ( gHeight <= 0 ) || ( gHeight > 1600 ) )
	{
		cout << "\nPlease enter a (0<) height (<=1600): ";
			cin >> gHeight;
	}

	cout << "Creating a window\n" ;
	cout << "W: " << gWidth << "\tH: " << gHeight << "\n";
	RenderWindow *m_Game = new RenderWindow(
			VideoMode( gWidth, gHeight ), "Universum-Meum", sf::Style::Close ); //{{{
	View *m_View = &m_Game->GetDefaultView();
	m_Game->SetView( *m_View );
	Clock *m_Clock = new Clock();
	const Input &m_Input = m_Game->GetInput();

	cout << "Setting framerate to 60\n";
	unsigned int frameRate = 60;
	m_Game->SetFramerateLimit( frameRate );
	//}}}

	float floatArray[ 2 ];
	glGetFloatv( GL_SMOOTH_POINT_SIZE_RANGE, floatArray );
	cout << floatArray[0] << " | "  << floatArray[1];

	/// Create Gravity/Repel forces
	const int rgConstant = 1024; //{{{
	cout << "\trgConstant: " << rgConstant << "\n";
	vector< Particle::Force* > *m_Forces = new vector< Particle::Force* >;

	cout << "Creating a gravity force\n";
	Particle::Force m_GravityFunc = &( Gravity< rgConstant > );
	Particle::Force* m_Gravity = &m_GravityFunc;
	m_Forces->push_back( m_Gravity );

	//cout << "Creating a collapse force\n";
	//Particle::Force m_CollapseFunc = &( Collapse< rgConstant * 20 > );
	//Particle::Force* m_Collapse = &m_CollapseFunc;

	cout <<  "Creating a elastic_collision force\n";
	Particle::Force* m_ElasticCollision = &DefaultElasticCollision;
	m_Forces->push_back( m_ElasticCollision );

	//}}}

	cout << "Now a particle system\n";
	ParticleSystem *m_ParticleSystem = new ParticleSystem( 1.0, 10000.0 );

	//cout << "Adding global collpase function\n";
	//m_ParticleSystem->AddForce( m_Collapse );

	unsigned int numObjects = 3; //{{{
	unsigned int initVel = 0;
	bool doLock = false;
	if( argc > 1 )
	{
		numObjects = atoi( argv[ 1 ] );
		numObjects %= 1000;
		if( numObjects < 1 )
		{
			numObjects = 1;
		}
		cout << "Creating " << numObjects << " point(s)\n";
		if( argc > 2 )
		{
			initVel = atoi( argv[ 2 ] );
			initVel %= 4;
			cout << "initVel method set to " << initVel << "\n";
		}
		string lastArgument = argv[ argc - 1 ];
		if( lastArgument == "lock" )
		{
			doLock = true;
		}
		else
		{
			cout << "last arg: " << lastArgument << "\n";
		}
	} //}}}

	cout <<  "Creating particles/points\n" ;
	vector< Particle* > m_Particles;
	vector< Shape* > m_Shapes;

	CreateParticles( &m_Shapes, &m_Particles, m_ParticleSystem, m_Forces, m_Game, initVel, numObjects );

	cout << "Setting up the sun\n";
	Shape* m_SunShape = new Shape(
		Shape::Circle( 0.0f, 0.0f, 25.0f,
			Color( 255, 255, 0 ) ) ); //{{{
	Particle* m_Sun = new Particle();

	m_Sun->AddDrawable( m_SunShape );
	m_Sun->position.x = gWidth / 2;
	m_Sun->position.y = gHeight / 2;
	m_Sun->radius = 25.0f;
	m_Sun->mass = 62.5f;
	// TODO m_Game->AddEntity( m_SunShape );
	m_Shapes.push_back( m_SunShape );
	m_ParticleSystem->AddParticle( m_Sun );

	m_Sun->AddForce( m_Gravity );
	m_Sun->AddForce( m_ElasticCollision );

	//log.info( "Giving the Sun some velocity" );
	//m_Sun.CurrentVelocities( -4, 0 );
	//m_Sun.Velocities( -4, 0 );
	//}}}

	cout << "Setting up the cursor\n" ;
	Shape* m_CursorShape = new Shape(
		Shape::Circle( 0.0f, 0.0f, 3.0f, Color( 0, 0, 0 ) ) ); //{{{
	m_Game->SetCursorPosition( 400, 300 );
	Particle* m_Cursor = new Particle();

	m_Cursor->AddDrawable( m_CursorShape );
	m_Cursor->position.x = 400.0f;
	m_Cursor->position.y = 300.0f;
	m_Cursor->radius = 0.0f;
	m_Cursor->mass = 0.0f;
	// TODO m_Game->AddEntity( m_CursorShape );
	m_Shapes.push_back( m_CursorShape );

	//m_ParticleSystem.AddParticle( m_Cursor );

	//m_Cursor.AddForce( m_Gravity );
	//m_Cursor.AddForce( m_Repel );
	//}}}

	unsigned int lastSpawn = 0;
	unsigned int lastKill = m_Clock->GetElapsedTime();
	long double maxMomSeen = 0;
	long double xCenter, yCenter;
	Particle* pMin;
	Particle* pMax;
	Event m_Event;
	cout << "Entering main game loop\n";
	while( m_Game->IsOpened() )
	{ //{{{
		while( m_Game->GetEvent( m_Event ) )
		{
			if( m_Event.Type == sf::Event::Closed )
			{
				m_Game->Close();
				break;
			}
		}
		if( m_Input.IsKeyDown( sf::Key::Escape ) )
		{
			cout << "Escape was pressed\n";
			m_Game->Close();
			break;
		}

		xCenter = m_View->GetCenter().x;
		yCenter = m_View->GetCenter().y;

		pMin = NULL; pMax = NULL;
		// Find particle nearest and furthest to cursor
		long double minDist = numeric_limits< long double >::max();
		long double maxDist = 0;
		for( vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); i++ )
		{ //{{{
			Vector2< long double > cDistance;
			cDistance.x = m_CursorShape->GetPosition().x - (*i)->position.x;
			cDistance.y = m_CursorShape->GetPosition().y - (*i)->position.y;
			long double cDist = Magnitude( cDistance );
			if( cDist < minDist )
			{
				minDist = cDist;
				pMin = (*i);
			}
			if( cDist > maxDist )
			{
				maxDist = cDist;
				pMax = (*i);
			}
		} //}}}

		// Maybe delete a particle based on 'd' or RMB
		if( ( ( m_Input.IsMouseButtonDown( sf::Mouse::Right ) )
			|| ( m_Input.IsKeyDown( sf::Key::D ) ) )
			&& ( m_Particles.size() > 0 )
			&& ( m_Clock->GetElapsedTime() > lastKill + 0.1 ) )
		{ //{{{
			lastKill = m_Clock->GetElapsedTime();

			bool kill = true;
			if( m_Input.IsMouseButtonDown( sf::Mouse::Right ) )
			{
				kill = ( minDist <= 10 );
			}

			if( kill )
			{
				cout << "Deleted a particle -- (↓) to " << m_Particles.size() -1 << '\n';
				Shape* eMin = ( Shape* )( pMin->GetDrawable() );

				m_ParticleSystem->RemoveParticle( pMin );
				for( std::vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); ++i )
				{
					if( (*i) == pMin )
					{
						m_Particles.erase( i );
						break;
					}
				}
				for( std::vector< Shape* >::iterator i = m_Shapes.begin(); i != m_Shapes.end(); ++i )
				{
					if( (*i) == eMin )
					{
						m_Shapes.erase( i );
						break;
					}
				}
				// TODO m_Game->RemoveDrawable( eMin );
				delete pMin;
				delete eMin;
			}
		} //}}}

		// Maybe delete a particle based on 'i'
		if( ( m_Input.IsKeyDown( sf::Key::I ) ) && ( m_Particles.size() > 0 )
			&& ( m_Clock->GetElapsedTime() > lastKill + 0.1f ) )
		{ //{{{
			lastKill = m_Clock->GetElapsedTime();

			cout << "Deleted a particle -- (↓) to " << m_Particles.size() -1 << '\n';
			Shape* eMax = ( Shape* )( pMax->GetDrawable() );

			m_ParticleSystem->RemoveParticle( pMax );
			for( std::vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); ++i )
			{
				if( (*i) == pMax )
				{
					m_Particles.erase( i );
					break;
				}
			}
			for( std::vector< Shape* >::iterator i = m_Shapes.begin(); i != m_Shapes.end(); ++i )
			{
				if( (*i) == eMax )
				{
					m_Shapes.erase( i );
					break;
				}
			}
			// TODO m_Game->RemoveDrawable( eMax );
			delete pMax;
			delete eMax;
		} //}}}

		// Maybe create new particle
		if( ( m_Input.IsMouseButtonDown( sf::Mouse::Left ) ) && ( minDist > 10 )
			&& ( m_Clock->GetElapsedTime() > lastSpawn + 0.1f )
			&& ( m_Particles.size() < MAX_PARTICLES ) )
		{ //{{{
			lastSpawn = m_Clock->GetElapsedTime();

			CreateParticle( &m_Shapes, &m_Particles, m_ParticleSystem, m_Forces, m_Game, initVel,
					m_Cursor->position );

		} //}}}

		if( m_Input.IsKeyDown( sf::Key::PageUp ) ) /// Zoomin
		{ //{{{
			m_View->Zoom( 0.90f );
		} //}}}
		else if( m_Input.IsKeyDown( sf::Key::PageDown ) ) /// Zoomout
		{ //{{{
			m_View->Zoom( 1.10f );
		} //}}}

		for( unsigned int i = 0; i < 10; ++i )
		{
			m_ParticleSystem->WorkAll( .001 );
			m_ParticleSystem->UpdateAll( .001 );
		}
		//m_ParticleSystem->Work( .02 );

		if( m_ParticleSystem->maxSpeed() > maxMomSeen )
		{
			maxMomSeen = m_ParticleSystem->maxSpeed();
		}
		for( vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); i++ )
		{
			long double logmom = (*i)->speed / maxMomSeen;
			Drawable* cEnt = (*i)->GetDrawable();
			cEnt->SetColor( Color(
						(int)( logmom * 255.0f ), 0, (int)( (1.0 - logmom) * 255.0f ), 255 ) );
		}

		if( doLock )
		{
			m_View->SetCenter( m_Sun->position.x, m_Sun->position.y );
		}
		else /// Use arrows to move camera
		{ //{{{
			if( m_Input.IsKeyDown( sf::Key::Right ) )
			{
				m_View->Move( 5.0f, 0.0f );
			} else if( m_Input.IsKeyDown( sf::Key::Left ) )
			{
				m_View->Move( -5.0f, 0.0f );
			}
			if( m_Input.IsKeyDown( sf::Key::Up ) )
			{
				m_View->Move( 0.0f, -5.0f );
			} else if( m_Input.IsKeyDown( sf::Key::Down ) )
			{
				m_View->Move( 0.0f, 5.0f );
			}
		} //}}}

		if( m_Input.IsKeyDown( sf::Key::Add ) ) /// Increase framerate
		{ //{{{
			if( frameRate <= 995 )
			{
				frameRate += 5;
				cout << "New framerate: " << frameRate << "\n";
				m_Game->SetFramerateLimit( frameRate );
			}
		} //}}}
		else if( m_Input.IsKeyDown( sf::Key::Subtract ) ) /// Decrease framerate
		{ //{{{
			if( frameRate >= 10 )
			{
				frameRate -= 5;
				cout << "New framerate: " << frameRate << "\n";
				m_Game->SetFramerateLimit( frameRate );
			}
		} //}}}

		m_Cursor->position.x = m_Game->ConvertCoords( m_Input.GetMouseX(), m_Input.GetMouseY() ).x;
		m_Cursor->position.y = m_Game->ConvertCoords( m_Input.GetMouseX(), m_Input.GetMouseY() ).y;
		m_Cursor->Update( 1 );

		m_Game->Clear();
		Shape mW = sf::Shape::Rectangle( m_View->GetRect().Left, m_View->GetRect().Top,
				m_View->GetRect().Right, m_View->GetRect().Bottom, sf::Color::White );
		m_Game->Draw( mW );
		for( vector< Shape* >::iterator i = m_Shapes.begin(); i != m_Shapes.end(); i++ )
		{
			// (*i)->SetColor( sf::Color::Blue );
			m_Game->Draw( *(*i) );
		}

		m_Game->Display();
	} //}}}

	cout << "\n---------------------------------\nThanks for playing!\n";
	return 0;
}

void CreateParticle( vector< Shape* > *m_Shapes, vector< Particle* > *m_Particles,
		ParticleSystem *m_ParticleSystem, vector< Particle::Force* > *m_Forces,
		RenderWindow *m_Game, int initVel, Vector2< long double > iPosition )
{ //{{{
	int num = m_Shapes->size();
	cout << "Created a new particle -- (↑) to " << num << "\n";
	Shape* nShape = new Shape(
			Shape::Circle( 0, 0, 10, sf::Color::White // Color(
					/*
					(int)( sin( num ) * 255.0f ),
					(int)( cos( num ) * 255.0f ),
					(int)( tan( num ) * 255.0f ), 255

				)*/, 1 ) );
	nShape->EnableFill( true );
	m_Shapes->push_back( nShape );
	// TODO m_Game->AddEntity( nShape );

	Particle *nParticle = new Particle();
	m_Particles->push_back( nParticle );
	nParticle->AddDrawable( nShape );
	nParticle->radius = 10.0;

	nParticle->position = iPosition;

	nParticle->velocity = detVelocity( initVel );
	for( vector< Particle::Force* >::iterator i = m_Forces->begin();
			i != m_Forces->end(); i++ )
	{
		nParticle->AddForce( (*i) );
	}

	m_ParticleSystem->AddParticle( nParticle );
} //}}}

void CreateParticles( vector< Shape* > *m_Shapes, vector< Particle* > *m_Particles,
		ParticleSystem *m_ParticleSystem, vector< Particle::Force* > *m_Forces,
		RenderWindow *m_Game, int initVel, int numObjects )
{ //{{{
	for( int i = 0; i < numObjects; i++ )
	{
		CreateParticle( m_Shapes, m_Particles, m_ParticleSystem, m_Forces, m_Game, initVel,
				Vector2< long double >(
					m_Game->GetWidth() / 2 + 100*cos( i * 2 * M_PI / numObjects ),
					m_Game->GetHeight() / 2 + 100*sin( i * 2 * M_PI / numObjects ) ) );
	}
} //}}}

Vector2< long double > detVelocity( unsigned int type )
{
	Vector2< long double >* rVec = new Vector2< long double >;
	switch( type ) /// Determine appropriate init velocities
	{ // {{{
		case 0: /// Nothing
		{
			break;
		}
		case 1: /// Random
		{
			// TODO get random number generation
			long double ranX = 0;//rand.fraction() * 16.0 - 8.0;
			long double ranY = 0;//rand.fraction() * 16.0 - 8.0;
			rVec->x = ranX;
			rVec->y = ranY;
			break;
		}
		case 2: /// Clockwise spiral
		{
		}
		case 3: /// Counter-clockwise spiral
		{
		}
		default:
		{
			break;
		}
	} //}}}
	return *rVec;
}

