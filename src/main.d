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
import tango.math.random.Twister;

import integer = tango.text.convert.Integer;

import tango.io.Stdout;
import game;
import particle;
import particle_system;
import entities.point;
import forces.gravity;
import forces.repel;

// Set up the logger, and the Key associative array
Logger log; //{{{
uint[ char[] ] Key;
static this()
{
	log = Log.lookup( "main" );
	log.add( new AppendConsole() );
	// Sets up the Key uint <-> char map
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
	Key[ "Last" ] = 323; Key.rehash; //}}}
} //}}}

int main( char[][] args )
{
	Stdout.formatln( "Welcome to Universum Meum." );

	log.info( "Creating random number generator" );
	auto rand = new Twister();
	rand.seed();

	log.info( "Creating a Game" );
	Game m_Game = Game.Instance( 800, 600, 32 ); //{{{
	m_Game.XPosition = 0;
	m_Game.YPosition = 0;

	log.info( "Setting framerate to 100" );
	m_Game.TickInterval = 1000 / 100;
	//}}}

	/// Create Gravity/Repel forces
	const real rgConstant = 1024.0; //{{{
	Stdout.formatln( "\trgConstant: {} [so:{}]", rgConstant, real.sizeof );

	log.info( "Creating a gravity force" );
	Gravity m_Gravity = Gravity.Instance();
	m_Gravity.GravityConstant = rgConstant;

	log.info( "Creating a repel force" );
	Repel m_Repel = Repel.Instance();
	m_Repel.RepelConstant = rgConstant;

	Stdout.formatln( "\tGrav: {}\t\tRep: {}", m_Gravity.GravityConstant, m_Repel.RepelConstant );
	//}}}

	log.info( "Now a particle system" );
	ParticleSystem m_ParticleSystem = new ParticleSystem( 1.0, 10000.0 );

	/// Process ars
	uint numObjects = 0; //{{{
	uint initVel = 0;
	if( args.length > 1 )
	{
		numObjects = integer.parse( args[ 1 ] );
		numObjects %= 255;
		if( numObjects < 1 )
		{
			numObjects = 1;
		}
		Stdout.formatln( "Creating {} point(s)", numObjects );
		if( args.length > 2 )
		{
			initVel = integer.parse( args[ 2 ] );
			if( initVel < 0 )
			{
				initVel = 0;
			}
			initVel %= 4;
			Stdout.formatln( "initVel method set to {}", initVel );
		}
	} //}}}

	log.info( "Creating particles/points" );
	Particle[] m_Particles;
	Point[] m_Points;
	m_Particles.length = numObjects;
	m_Points.length = numObjects;

	/// Create particles
	for( uint i = 0; i < numObjects; i++ ) //{{{
	{
		m_Points[ i ] = new Point( 0, 0, 10, sin( i ), cos( i ), tan( i ) );
		m_Game.AddEntity( m_Points[ i ] );

		m_Particles[ i ] = new Particle();
		m_Particles[ i ].AddEntity( m_Points[ i ] );
		m_Particles[ i ].Radius = 10.0;

		m_Particles[ i ].CurrentPositions( 400 + 100*cos( i * 2 * PI / numObjects ),
										   300 + 100*sin( i * 2 * PI / numObjects ) );

		switch( initVel ) /// Determine appropriate init velocities
		{ //{{{
			case 0: /// Nothing
			{
				break;
			}
			case 1: /// Random
			{
				real ranX = rand.fraction() * 16.0 - 8.0;
				real ranY = rand.fraction() * 16.0 - 8.0;
				Stdout.formatln( "Seeded particle {} with < {}, {} >", i, ranX, ranY );
				m_Particles[ i ].Velocities( ranX, ranY  );
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

		m_Particles[ i ].AddForce( m_Gravity );
		m_Particles[ i ].AddForce( m_Repel );

		m_ParticleSystem.AddParticle( m_Particles[ i ] );
	} //}}}

	log.info( "Setting up the sun" );
	Point m_SunPoint = new Point( 400.0f, 300.0f, 25.0f, 1.0f, 1.0f, 0.0f ); //{{{
	Particle m_Sun = new Particle();

	m_Sun.AddEntity( m_SunPoint );
	m_Sun.Positions( 400.0f, 300.0f );
	m_Sun.Radius( 25.0f );
	m_Sun.Mass( 62.5f );
	m_Game.AddEntity( m_SunPoint );
	m_ParticleSystem.AddParticle( m_Sun );

	m_Sun.AddForce( m_Gravity );
	m_Sun.AddForce( m_Repel );

	//log.info( "Giving the Sun some velocity" );
	//m_Sun.CurrentVelocities( -4, 0 );
	//m_Sun.Velocities( -4, 0 );
	//}}}

	log.info( "Entering main game loop" );
	while( !m_Game.isDone )
	{ //{{{
		if( m_Game.isPressed( Key[ "Escape" ] ) )
		{
			m_Game.isDone = true;
			continue;
		}

		if( m_Game.isClicked ) /// Print informortive messages
		{ //{{{
			foreach( uint num, i; m_Particles )
			{
				Stdout.formatln( "{}: ( {}, {} ) < {}, {} > [ {}, {} ]", num,
					i.XPosition, i.YPosition,
					i.XVelocity, i.YVelocity,
					i.XAcceleration, i.YAcceleration );
			}
			Stdout.formatln( "Sun: ( {}, {} ) < {}, {} > [ {}, {} ]",
				m_Sun.XPosition, m_Sun.YPosition,
				m_Sun.XVelocity, m_Sun.YVelocity,
				m_Sun.XAcceleration, m_Sun.YAcceleration );
		} //}}}

		m_Game.ProcessInput();

		m_ParticleSystem.Work( .02 );

		if( args[ $-1 ] == "lock" )
		{
			m_Game.XPosition = m_Sun.XPosition - 400;
			m_Game.YPosition = m_Sun.YPosition - 300;
		}
		else /// Use arrows to move camera
		{ //{{{
			if( m_Game.isPressed( Key[ "Right" ] ) )
			{
				m_Game.XPosition = m_Game.XPosition + 5;
			} else if( m_Game.isPressed( Key[ "Left" ] ) )
			{
				m_Game.XPosition = m_Game.XPosition - 5;
			}
			if( m_Game.isPressed( Key[ "Up" ] ) )
			{
				m_Game.YPosition = m_Game.YPosition - 5;
			} else if( m_Game.isPressed( Key[ "Down" ] ) )
			{
				m_Game.YPosition = m_Game.YPosition + 5;
			}
		} //}}}

		m_Game.Draw();
		m_Game.WaitFor();
	} //}}}

	Stdout.formatln( "Thanks for playing!" );
	return 0;
}
