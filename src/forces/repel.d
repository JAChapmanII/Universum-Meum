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

				/*
				void collision2Ds(double m1, double m2, double R,
						double x1, double y1, double x2, double y2,
						double& vx1, double& vy1, double& vx2, double& vy2)
						*/

				//double  m21, dvx2, a, x21, y21, vx21, vy21, fy21, sign, vx_cm, vy_cm;

				float m21  = B.Mass / A.Mass;
				float x21  = B.XPosition - A.XPosition;
				float y21  = B.YPosition - A.YPosition;
				float vx21 = B.XVelocity - A.XVelocity;
				float vy21 = B.YVelocity - A.YVelocity;

				float sumMass = A.Mass + B.Mass;

				float vx_cm = ( A.Mass*A.XVelocity + B.Mass*B.XVelocity ) / sumMass;
				float vy_cm = ( A.Mass*A.YVelocity + B.Mass*B.YVelocity ) / sumMass;

// *** return old velocities if balls are not approaching ***
				/*
				if ( (vx21*x21 + vy21*y21) >= 0)
				{
					return;
				}
				*/

// *** I have inserted the following statements to avoid a zero divide;
//     (for single precision calculations, 1.0E-12 should be replaced by a larger value)

				float fy21 = 1.0E-12 * abs( y21 );
				float sign;
				if( abs( x21 ) < fy21 )
				{
					if( x21 < 0 )
					{
						sign = -1;
					}
					else
					{
						sign = 1;
					}
					x21 = fy21 * sign;
				}

//     ***  update velocities ***
				float a = y21 / x21;
				float dvx2 = -2 * ( vx21 + a * vy21 ) / ( ( 1 + a*a ) * ( 1 + m21 ) );
				//vx2=vx2+dvx2;
				//vy2=vy2+a*dvx2;
				A.XVelocity = A.XVelocity - m21*dvx2;
				A.YVelocity = A.YVelocity - a*m21*dvx2;

//     ***  velocity correction for inelastic collisions ***
		/*
       vx1=(vx1-vx_cm)*R + vx_cm;
       vy1=(vy1-vy_cm)*R + vy_cm;
       vx2=(vx2-vx_cm)*R + vx_cm;
       vy2=(vy2-vy_cm)*R + vy_cm;
	   */

		/*
				A.XVelocity = (A.Mass - B.Mass)/(A.Mass + B.Mass)*A.XVelocity +
							  ( 2 * B.Mass )/( A.Mass + B.Mass)*B.XVelocity;
				A.YVelocity = (A.Mass - B.Mass)/(A.Mass + B.Mass)*A.YVelocity +
							  ( 2 * B.Mass )/( A.Mass + B.Mass)*B.YVelocity;
							  */
			}
		}

	protected:
		this()
		{
		}

		static Repel m_Instance;

	private:

}
