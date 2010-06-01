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
module repel;

import tango.util.log.Log;
import tango.util.log.AppendConsole;
import Integer = tango.text.convert.Integer;

import tango.math.Math;

import force;
import particle;

Logger log;
static this()
{
	log = Log.lookup( "forces.repel" );
	log.add( new AppendConsole() );
}

class Repel : Force
{
	public:
		static Repel Instance()
		{ //{{{
			if( m_Instance is null )
			{
				try
				{
					m_Instance = new Repel();
				}
				catch( Exception e )
				{
					log.fatal( "Repel could not be instantiated." );
					throw e;
				}
			}
			return m_Instance;
		} //}}}

		alias Instance opCall;

		override void Work( Particle A, Particle B, float deltaTime )
		{
			//log.info( "Repel has done work" );
			float distX = B.XPosition - A.XPosition;
			float distY = B.YPosition - A.YPosition;
			float dist =  sqrt( (distX*distX) + (distY*distY) );
			if( (dist <= (A.Radius + B.Radius)) && (dist > 0.0f) )
			{
				A.XVelocity = (A.XVelocity*A.Mass + B.XVelocity*B.Mass)/(500000*A.Mass);
				A.YVelocity = (A.YVelocity*A.Mass + B.YVelocity*B.Mass)/(500000*A.Mass);
			}
		}

	protected:
		this()
		{
		}

		static Repel m_Instance;

	private:

}
