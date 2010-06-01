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

import tango.io.Stdout;
import display;
import particle;
import entities.point;
import forces.gravity;

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

	log.info( "Now a force and particle" );
	//Force m_Force = new Force();
	Particle m_Particle = new Particle();

	log.info( "Now creating an array of points" );
	Point[ 4 ] m_Points;
	m_Points[ 0 ] = new Point( 200, 150, 10, 1.0f, 0.0f, 0.0f );
	m_Points[ 1 ] = new Point( 600, 150, 10, 0.0f, 1.0f, 0.0f );
	m_Points[ 2 ] = new Point( 200, 450, 10, 0.0f, 0.0f, 1.0f );
	m_Points[ 3 ] = new Point( 600, 450, 10, 1.0f, 1.0f, 1.0f );

	foreach( i; m_Points )
	{
		m_Display.AddEntity( i );
	}

	/*
	m_Display.AddEntity( m_Points[ 0 ] );
	m_Display.AddEntity( m_Points[ 1 ] );
	m_Display.AddEntity( m_Points[ 2 ] );
	m_Display.AddEntity( m_Points[ 3 ] );
	*/

	Point m_Point = new Point( 400, 300, 25, 1.0f, 1.0f, 1.0f );
	m_Display.AddEntity( m_Point );

	log.info( "Entering main game loop" );
	while( !m_Display.isDone )
	{
		m_Display.ProcessInput();
		m_Display.Draw();
		m_Display.WaitFor();
	}

	Stdout.formatln( "Thanks for playing!" );
	return 0;
}
