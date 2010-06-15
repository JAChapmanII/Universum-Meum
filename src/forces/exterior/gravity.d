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
module gravity;

import tango.io.Stdout;

import tango.util.log.Log;
import tango.util.log.AppendConsole;
import tango.math.Math;

import force;
import particle;

Logger log;
static this()
{
	log = Log.lookup( "forces.gravity" );
	log.add( new AppendConsole() );
}

void Gravity( real gravConst )( Particle A, Particle B, ref real deltaTime )
{
	real xDist = B.XPosition - A.XPosition;
	real yDist = B.YPosition - A.YPosition;
	real dist2 = (xDist * xDist) + (yDist * yDist);

	if( dist2 > 0 )
	{
		real gravMass = gravConst * B.Mass;
		real dist  = sqrt( dist2 );

		A.XAcceleration = A.NextXAcceleration +
			( gravMass )*(xDist/dist) / ( dist2 );

		A.YAcceleration = A.NextYAcceleration +
			( gravMass )*(yDist/dist) / ( dist2 );
	}
}

Force DefaultGravity = &Gravity!( 0.0 );
