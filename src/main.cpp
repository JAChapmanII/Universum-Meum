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
#include <vector>
#include <cstdlib>
#include <string>
#include <map>
#include <limits>
#include <cmath>

#include <SFML/Graphics.hpp>
// Using declarations for SFML {{{
using sf::RenderWindow;
using sf::VideoMode;
using sf::Shape;
using sf::Color;
using sf::Event;
using sf::Input;
// }}}

#include "particle.hpp"
#include "particle_system.hpp"
#include "forces/exterior/gravity.cpp"
#include "forces/exterior/collapse.cpp"
#include "forces/interior/repel.cpp"
#include "forces/colliding/elastic_collision.cpp"

using namespace std;

const unsigned int MAX_PARTICLES = 1000;

Vector2< long double > detVelocity( unsigned int type = 0 );
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

int main( int argc, const char* argv[] )
{
	map< string, int > Key;
	// Sets up the Key unsigned int <-> char map
	Key[ "None" ] = -1; Key[ "First" ] = 1; Key[ "Backspace" ] = 8; //{{{
	Key[ "Tab" ] = 9; Key[ "	" ] = 9; Key[ "Clear" ] = 12; Key[ "Enter" ] = 13;
	Key[ "Return" ] = 13; Key[ "Pause" ] = 19; Key[ "Escape" ] = 27;
	Key[ "Space" ] = 32; Key[ " " ] = 32; Key[ "Exclamation Mark" ] = 33;
	Key[ "!" ] = 33; Key[ "Double Quotes" ] = 34;Key[ "\"" ] = 34;
	Key[ "Octothorpe" ] = 35; Key[ "#" ] = 35; Key[ "Dollar Sign" ] = 36;
	Key[ "$" ] = 36;Key[ "Ampersand" ] = 38; Key[ "&" ] = 38;
	Key[ "Single Quote" ] = 39; Key[ "'" ] = 39;
	Key[ "Open Parenthesis" ] = 40;Key[ "(" ] = 40;
	Key[ "Close Parenthesis" ] = 41; Key[ ")" ] = 41; Key[ "Asterik" ] = 42;
	Key[ "*" ] = 42; Key[ "Plus Sign" ] = 43; Key[ "+" ] = 43;
	Key[ "Comma" ] = 44; Key[ "," ] = 44; Key[ "Minus Sign" ] = 45;
	Key[ "-" ] = 45; Key[ "Period" ] = 46; Key[ "." ] = 46;
	Key[ "Forward Slash" ] = 47; Key[ "/" ] = 47; Key[ "Zero" ] = 48;
	Key[ "0" ] = 48; Key[ "One" ] = 49; Key[ "1" ] = 49; Key[ "Two" ] = 50;
	Key[ "2" ] = 50; Key[ "Three" ] = 51; Key[ "3" ] = 51; Key[ "Four" ] = 52;
	Key[ "4" ] = 52; Key[ "Five" ] = 53; Key[ "5" ] = 53; Key[ "Six" ] = 54;
	Key[ "6" ] = 54; Key[ "Seven" ] = 55; Key[ "7" ] = 55; Key[ "Eight" ] = 56;
	Key[ "8" ] = 56; Key[ "Nine" ] = 57; Key[ "9" ] = 57; Key[ "Colon" ] = 58;
	Key[ ":" ] = 58; Key[ "Semicolon" ] = 59; Key[ ";" ] = 59;
	Key[ "Open Angle Bracket" ] = 60; Key[ "<" ] = 60; Key[ "Equals" ] = 61;
	Key[ "=" ] = 61; Key[ "Close Angle Bracket" ] = 62; Key[ ">" ] = 62;
	Key[ "Question Mark" ] = 63; Key[ "?" ] = 63; Key[ "At" ] = 64;
	Key[ "@" ] = 64; Key[ "Open Bracket" ] = 91; Key[ "[" ] = 91;
	Key[ "Backslash" ] = 92; Key[ "\\" ] = 92; Key[ "Close Bracket" ] = 93;
	Key[ "]" ] = 93; Key[ "Caret" ] = 94; Key[ "^" ] = 94;
	Key[ "Underscore" ] = 95; Key[ "_" ] = 95; Key[ "Grave" ] = 96;
	Key[ "`" ] = 96; Key[ "a" ] = 97; Key[ "b" ] = 98; Key[ "c" ] = 99;
	Key[ "d" ] = 100; Key[ "e" ] = 101; Key[ "f" ] = 102; Key[ "g" ] = 103;
	Key[ "h" ] = 104; Key[ "i" ] = 105; Key[ "j" ] = 106; Key[ "k" ] = 107;
	Key[ "l" ] = 108; Key[ "m" ] = 109; Key[ "n" ] = 110; Key[ "o" ] = 111;
	Key[ "p" ] = 112; Key[ "q" ] = 113; Key[ "r" ] = 114; Key[ "s" ] = 115;
	Key[ "t" ] = 116; Key[ "u" ] = 117; Key[ "v" ] = 118; Key[ "w" ] = 119;
	Key[ "x" ] = 120; Key[ "y" ] = 121; Key[ "z" ] = 122;
	Key[ "Delete" ] = 123; Key[ "Key Pad Zero" ] = 256;
	Key[ "Key Pad 0" ] = 256; Key[ "Key Pad One" ] = 257;
	Key[ "Key Pad 1" ] = 257; Key[ "Key Pad Two" ] = 258;
	Key[ "Key Pad 2" ] = 258; Key[ "Key Pad Three" ] = 259;
	Key[ "Key Pad 3" ] = 259; Key[ "Key Pad Four" ] = 260;
	Key[ "Key Pad 4" ] = 260; Key[ "Key Pad Five" ] = 261;
	Key[ "Key Pad 5" ] = 261; Key[ "Key Pad Six" ] = 262;
	Key[ "Key Pad 6" ] = 262; Key[ "Key Pad Seven" ] = 263;
	Key[ "Key Pad 7" ] = 263; Key[ "Key Pad Eight" ] = 264;
	Key[ "Key Pad 8" ] = 264; Key[ "Key Pad Nine" ] = 265;
	Key[ "Key Pad 9" ] = 265; Key[ "Key Pad Period" ] = 266;
	Key[ "Key Pad ." ] = 266; Key[ "Key Pad Divide" ] = 267;
	Key[ "Key Pad /" ] = 267; Key[ "Key Pad Multiply" ] = 268;
	Key[ "Key Pad *" ] = 268; Key[ "Key Pad Minus" ] = 269;
	Key[ "Key Pad -" ] = 269; Key[ "Key Pad Plus" ] = 270;
	Key[ "Key Pad +" ] = 270; Key[ "Key Pad Enter" ] = 271;
	Key[ "Key Pad Equals" ] = 272; Key[ "Key Pad =" ] = 272;
	Key[ "Up" ] = 273; Key[ "Down" ] = 274; Key[ "Right" ] = 275;
	Key[ "Left" ] = 276; Key[ "Insert" ] = 277; Key[ "Home" ] = 278;
	Key[ "End" ] = 279; Key[ "Page Up" ] = 280; Key[ "Page Down" ] = 281;
	Key[ "F1" ] = 282; Key[ "F2" ] = 283; Key[ "F3" ] = 284; Key[ "F4" ] = 285;
	Key[ "F5" ] = 286; Key[ "F6" ] = 287; Key[ "F7" ] = 288; Key[ "F8" ] = 289;
	Key[ "F9" ] = 290; Key[ "F10" ] = 291; Key[ "F11" ] = 292;
	Key[ "F12" ] = 293; Key[ "F13" ] = 294; Key[ "F14" ] = 295;
	Key[ "F15" ] = 296; Key[ "Number Lock" ] = 300;
	Key[ "Capitals Lock" ] = 301; Key[ "Scroll Lock" ] = 302;
	Key[ "Right Shift" ] = 303; Key[ "Left Shift" ] = 304;
	Key[ "Right Control" ] = 305; Key[ "Left Control" ] = 306;
	Key[ "Right Alternative" ] = 307; Key[ "Left Alternative" ] = 308;
	Key[ "Right Meta" ] = 309; Key[ "Left Meta" ] = 310;
	Key[ "Left Super" ] = 311; Key[ "Right Super" ] = 312; Key[ "Mode" ] = 313;
	Key[ "Compose" ] = 314; Key[ "Help" ] = 315; Key[ "Print" ] = 316;
	Key[ "System Request" ] = 317; Key[ "Break" ] = 318; Key[ "Menu" ] = 319;
	Key[ "Power" ] = 320; Key[ "Euro" ] = 321; Key[ "Undo" ] = 322;
	Key[ "Last" ] = 323;  //}}}

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
	RenderWindow *m_Game =
		new RenderWindow( VideoMode( gWidth, gHeight, 32 ), "Universum-Meum" ); //{{{
	const Input &m_Input = m_Game->GetInput();

	cout << "Setting framerate to 100\n";
	unsigned int frameRate = 100;
	m_Game->SetFramerateLimit( frameRate );
	//}}}

	float floatArray[ 2 ];
	glGetFloatv( GL_SMOOTH_POINT_SIZE_RANGE, floatArray );
	cout << floatArray[0] << " | "  << floatArray[1];

	/// Create Gravity/Repel forces
	const int rgConstant = 1024; //{{{
	cout << "\trgConstant: " << rgConstant << "\n";

	cout << "Creating a gravity force\n";
	Particle::Force m_GravityFunc = &( Gravity< rgConstant > );
	Particle::Force* m_Gravity = &m_GravityFunc;

	//cout << "Creating a collapse force\n";
	//Particle::Force m_CollapseFunc = &( Collapse< rgConstant * 20 > );
	//Particle::Force* m_Collapse = &m_CollapseFunc;

	cout <<  "Creating a elastic_collision force\n";
	Particle::Force* m_ElasticCollision = &DefaultElasticCollision;

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

	/// Create particles
	for( unsigned int i = 0; i < numObjects; i++ ) //{{{
	{
		cout << "Number: " << i << "\n";
		Shape* nShape = new Shape(
			Shape::Circle( 0, 0, 10, Color( sin( i ), cos( i ), tan( i ) ) ) );
		m_Shapes.push_back( nShape );
		// TODO m_Game->AddEntity( nShape );

		Particle *nParticle = new Particle();
		m_Particles.push_back( nParticle );
		nParticle->AddDrawable( nShape );
		nParticle->radius = 10.0;

		nParticle->position.x = m_Game->GetWidth() / 2 + 100*cos( i * 2 * M_PI / numObjects );
		nParticle->position.y = m_Game->GetHeight() / 2 + 100*sin( i * 2 * M_PI / numObjects );

		nParticle->velocity = detVelocity( initVel );
		nParticle->AddForce( m_Gravity );
		nParticle->AddForce( m_ElasticCollision );

		m_ParticleSystem->AddParticle( nParticle );
	} //}}}

	cout << "Setting up the sun\n";
	Shape* m_SunShape = new Shape(
		Shape::Circle( m_Game->GetWidth() / 2, m_Game->GetHeight() / 2, 25.0f,
			Color( 1.0f, 1.0f, 0.0f ) ) ); //{{{
	Particle* m_Sun = new Particle();

	m_Sun->AddDrawable( m_SunShape );
	m_Sun->position.x = gWidth / 2;
	m_Sun->position.y = gHeight / 2;
	m_Sun->radius = 25.0f;
	m_Sun->mass = 62.5f;
	// TODO m_Game->AddEntity( m_SunShape );
	m_ParticleSystem->AddParticle( m_Sun );

	m_Sun->AddForce( m_Gravity );
	m_Sun->AddForce( m_ElasticCollision );

	//log.info( "Giving the Sun some velocity" );
	//m_Sun.CurrentVelocities( -4, 0 );
	//m_Sun.Velocities( -4, 0 );
	//}}}

	cout << "Setting up the cursor\n" ;
	Shape* m_CursorShape = new Shape(
		Shape::Circle( 400.0f, 300.0f, 3.0f, Color( 0.0f, 0.0f, 0.0f ) ) ); //{{{
	m_Game->SetCursorPosition( 400, 300 );
	Particle* m_Cursor = new Particle();

	m_Cursor->AddDrawable( m_CursorShape );
	m_Cursor->position.x = 400.0f;
	m_Cursor->position.y = 300.0f;
	m_Cursor->radius = 0.0f;
	m_Cursor->mass = 0.0f;
	// TODO m_Game->AddEntity( m_CursorShape );

	//m_ParticleSystem.AddParticle( m_Cursor );

	//m_Cursor.AddForce( m_Gravity );
	//m_Cursor.AddForce( m_Repel );
	//}}}

	unsigned int lastSpawn = 0;
	unsigned int lastKill = 0;
	long double maxMomSeen = 0;
	long double xCenter, yCenter;
	Particle* pMin;
	Particle* pMax;
	cout << "Entering main game loop\n";
	while( !m_Game->IsOpened() )
	{ //{{{
		if( m_Input.IsKeyDown( sf::Key::Escape ) )
		{
			m_Game->Close();
			continue;
		}

		xCenter = m_Game->XCenter();
		yCenter = m_Game->YCenter();

		pMin = NULL; pMax = NULL;
		// Find particle nearest and furthest to cursor
		long double minDist = numeric_limits< long double >::max();
		long double maxDist = 0;
		for( vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); i++ )
		{ //{{{
			Vector< long double > cDistance = m_CursorPolygon->position - (*i)->position;
			long double cDist = cDistance.Magnitude();
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
		if( ( ( m_Game->isClicked( SDL_BUTTON_RIGHT ) ) || ( m_Input.IsKeyDown( sf::Key::D ) ) )
				&& ( m_Particles.size() > 0 ) && ( m_Game->GetTicks() > lastKill + 100 ) )
		{ //{{{
			lastKill = m_Game->GetTicks();

			bool kill = true;
			if( m_Game->isClicked( SDL_BUTTON_RIGHT ) )
			{
				kill = ( minDist <= 10 );
			}

			if( kill )
			{
				cout << "Deleted a particle -- (↓) to " << m_Particles.size() -1 << '\n';
				Polygon* eMin = ( Polygon* )( pMin->GetEntity() );

				m_ParticleSystem->RemoveParticle( pMin );
				for( std::vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); ++i )
				{
					if( (*i) == pMin )
					{
						m_Particles.erase( i );
						break;
					}
				}
				for( std::vector< Polygon* >::iterator i = m_Polygons.begin(); i != m_Polygons.end(); ++i )
				{
					if( (*i) == eMin )
					{
						m_Polygons.erase( i );
						break;
					}
				}
				m_Game->RemoveEntity( eMin );
				delete pMin;
				delete eMin;
			}
		} //}}}

		// Maybe delete a particle based on 'i'
		if( ( m_Input.IsKeyDown( sf::Key::I ) ) && ( m_Particles.size() > 0 )
				&& ( m_Game->GetTicks() > lastKill + 100 ) )
		{ //{{{
			lastKill = m_Game->GetTicks();

			cout << "Deleted a particle -- (↓) to " << m_Particles.size() -1 << '\n';
			Polygon* eMax = ( Polygon* )( pMax->GetEntity() );

			m_ParticleSystem->RemoveParticle( pMax );
			for( std::vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); ++i )
			{
				if( (*i) == pMax )
				{
					m_Particles.erase( i );
					break;
				}
			}
			for( std::vector< Polygon* >::iterator i = m_Polygons.begin(); i != m_Polygons.end(); ++i )
			{
				if( (*i) == eMax )
				{
					m_Polygons.erase( i );
					break;
				}
			}
			m_Game->RemoveEntity( eMax );
			delete pMax;
			delete eMax;
		} //}}}

		// Maybe create new particle
		if( ( m_Input->IsKeyDown( sf::Key::Left ) ) && ( minDist > 10 )
				&& ( m_Game->ClickCreateTime( SDL_BUTTON_LEFT ) > lastSpawn )
				&& ( m_Particles.size() < MAX_PARTICLES ) )
		{ //{{{
			lastSpawn = m_Game->ClickCreateTime( SDL_BUTTON_LEFT );

			unsigned int pNum = m_Polygons.size() + 1;
			cout << "Created a new particle -- (↑) to " << pNum << "\n";
			Polygon* nPolygon = new Polygon( 0, 0, 10, sin( pNum ), cos( pNum ), tan( pNum ) );
			m_Polygons.push_back( nPolygon );
			m_Game->AddEntity( nPolygon );

			Particle* nParticle = new Particle();
			m_Particles.push_back( nParticle );
			nParticle->AddEntity( nPolygon );
			nParticle->radius = 10.0;

			nParticle->position.Set( m_CursorPolygon->position );

			nParticle->velocity.Set( detVelocity( initVel ) );
			nParticle->AddForce( m_Gravity );
			nParticle->AddForce( m_ElasticCollision );

			m_ParticleSystem->AddParticle( nParticle );
		} //}}}

		if( m_Game->isClicked( SDL_BUTTON_WHEELUP ) ) /// Zoomin
		{ //{{{
			if( m_Game->Zoom() < 24 )
			{
				m_Game->ResizeViewport( m_Game->ViewWidth() - (long double)( m_Game->Width() ) / 24.0f,
										m_Game->ViewHeight() - (long double)( m_Game->Height() ) / 24.0f );
				m_Game->Centers( xCenter, yCenter );
			}
		} //}}}
		else if( m_Game->isClicked( SDL_BUTTON_WHEELDOWN ) ) /// Zoomout
		{ //{{{
			m_Game->ResizeViewport( m_Game->ViewWidth() + (long double)( m_Game->Width() ) / 24.0f,
									m_Game->ViewHeight() + (long double)( m_Game->Height() ) / 24.0f );
			m_Game->Centers( xCenter, yCenter );
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
			Entity* cEnt = (*i)->GetEntity();
			(*static_cast< Polygon* >( cEnt )).Color( logmom, 0, 1.0 - logmom, 1.0 );
		}

		if( doLock )
		{
			m_Game->Centers( m_Sun->position.x, m_Sun->position.y );
		}
		else /// Use arrows to move camera
		{ //{{{
			if( m_Input.IsKeyDown( sf::Key::Right ) )
			{
				m_Game->position.x += 5;
			} else if( m_Input.IsKeyDown( sf::Key::Left ) )
			{
				m_Game->position.x -= 5;
			}
			if( m_Input.IsKeyDown( sf::Key::Up ) )
			{
				m_Game->position.y += 5;
			} else if( m_Input.IsKeyDown( sf::Key::Down ) )
			{
				m_Game->position.y -= 5;
			}
		} //}}}

		if( m_Input.IsKeyDown( sf::Key::Add ) ) /// Increase framerate
		{ //{{{
			if( frameRate <= 995 )
			{
				frameRate += 5;
				cout << "New framerate: " << frameRate << "\n";
				m_Game->tickInterval = 1000 / frameRate;
			}
		} //}}}
		else if( m_Input.IsKeyDown( sf::Key::Subtract ) ) /// Decrease framerate
		{ //{{{
			if( frameRate >= 10 )
			{
				frameRate -= 5;
				cout << "New framerate: " << frameRate << "\n";
				m_Game->tickInterval = 1000 / frameRate;
			}
		} //}}}

		m_Cursor->position.Set(
		(int)(
			(long double)(m_Game->CursorX()) / m_Game->Width() * m_Game->ViewWidth() + m_Game->position.x ),
		(int)(
			(1.0 - ((long double)(m_Game->CursorY()) / m_Game->Height())) * m_Game->ViewHeight() + m_Game->position.y),
			0 );
		m_Cursor->Update( 1 );

		quitButton->position.Set( 40.0 * m_Game->ViewWidth()/m_Game->Width() + m_Game->position.x,
				(1.0 - 40.0/m_Game->Height()) * m_Game->ViewHeight() + m_Game->position.y, 0 );

		if( m_Game->isClicked( SDL_BUTTON_LEFT ) )
		{
			long double xDist = m_Cursor->position.x - quitButton->position.x;
			long double yDist = m_Cursor->position.y - quitButton->position.y;
			long double dist = sqrt( xDist*xDist + yDist*yDist );
			if( dist < (10* m_Game->ViewWidth()/m_Game->Width()) )
			{
				m_Game->isDone = true;
			}
		}

		m_Game->Draw();
		m_Game->WaitFor();
	} //}}}

	m_Game->DeinitSGL();

	cout << "\n---------------------------------\nThanks for playing!\n";
	return 0;
}
