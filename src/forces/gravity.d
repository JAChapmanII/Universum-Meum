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

class Gravity : Force
{
	public:
		static Gravity Instance()
		{ //{{{
			if( m_Instance is null )
			{
				try
				{
					m_Instance = new Gravity();
				}
				catch( Exception e )
				{
					log.fatal( "Gravity could not be instantiated." );
					throw e;
				}
			}
			return m_Instance;
		} //}}}

		alias Instance opCall;

		override void Work( Particle A, Particle B, float deltaTime )
		{
			//log.info( "Gravity has done work" );
			float distX = B.XPosition - A.XPosition;
			float distY = B.YPosition - A.YPosition;
			float dist = sqrt( distX*distX + distY*distY );
			if( dist > 0.001f )
			{
				float force = ( A.Mass * B.Mass ) / ( dist * dist );
				float delX = ( distX / dist ) * force / 100000.0f * deltaTime;
				float delY = ( distY / dist ) * force / 100000.0f * deltaTime;

				A.XAcceleration = A.XAcceleration + delX;// * 0.1f;
				A.YAcceleration = A.YAcceleration + delY;// * 0.1f;

				B.XAcceleration = B.XAcceleration - delX;// * 0.1f;
				B.XAcceleration = B.XAcceleration - delX;// * 0.1f;
			}

				/*
			if( dist < A.Mass )
			{
				float delX = 0.0f;
				float delY = 0.0f;

				if( abs( distX ) < ( A.Mass * 0.9f ) )
				{
					delX = sgn( distX ) * abs( distX ) * ( A.Mass - abs( distX ) );
				}
				if( abs( distY ) < ( A.Mass * 0.9f ) )
				{
					delY = sgn( distY ) * abs( distY ) * ( A.Mass - abs( distY ) );
				}
				delX *= 0.001f;
				delY *= 0.001f;

				if( ( abs( delX ) > 10 ) || ( abs( delY ) > 10 ) )
				{
					log.info( "Problems" );
				}

				A.XAcceleration = A.XAcceleration + delX;// * 0.1f;
				A.YAcceleration = A.YAcceleration + delY;// * 0.1f;

				B.XAcceleration = B.XAcceleration - delX;// * 0.1f;
				B.XAcceleration = B.XAcceleration - delX;// * 0.1f;
			}
			*/
		}

	protected:
		this()
		{
		}

		static Gravity m_Instance;

		float sgn( float a )
		{
			if( a < 0 )
			{
				return -1.0f;
			}
			else if( a > 0 )
			{
				return 1.0f;
			}
			else
			{
				return 0.0f;
			}
		}

		float abs( float a )
		{
			if( a < 0 )
			{
				return -a;
			}
			return a;
		}

	private:

}
