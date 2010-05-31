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
import force;

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

	log.info( "Now a force and particle" );
	Force m_Force = new Force();
	Particle m_Particle = new Particle();

	log.info( "Sleeping a little" );
	m_Display.sleep( 5000 );

	log.info( "5 secs passed" );
	m_Display.sleep( 5000 );

	Stdout.formatln( "Thanks for playing!" );
	return 0;
}
