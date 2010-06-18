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
#ifndef POLYGON_CPP
#define POLYGON_CPP

#include "polygon.hpp"

Polygon::Polygon( long double iX, long double iY ) :
	Entity( iX, iY, 0 ), //{{{
	radius( 1 ),
	numSegments( 36 )
{
	this->position.x = iX;
	this->position.y = iY;
	Color( 1.0f, 1.0f, 1.0f, 1.0f );
} //}}}

Polygon::Polygon( long double iX, long double iY, long double iRadius ) :
	Entity( iX, iY, 0 ), //{{{
	radius( iRadius ),
	numSegments( 36 )
{
	this->position.x = iX;
	this->position.y = iY;
	Color( 1.0f, 1.0f, 1.0f, 1.0f );
} //}}}

Polygon::Polygon( long double iX, long double iY, long double iRadius, long double iRed, long double iGreen, long double iBlue ) :
	Entity( iX, iY, 0 ), //{{{
	radius( iRadius ),
	numSegments( 36 )
{
	this->position.x = iX;
	this->position.y = iY;
	Color( iRed, iGreen, iBlue, 1.0f );
} //}}}

Polygon::Polygon( long double iX, long double iY, long double iRadius, long double iRed, long double iGreen, long double iBlue, long double iAlpha ) :
	Entity( iX, iY, 0 ), //{{{
	radius( iRadius ),
	numSegments( 36 )
{
	this->position.x = iX;
	this->position.y = iY;
	Color( iRed, iGreen, iBlue, iAlpha );
} //}}}

void Polygon::Draw( long double zoom )
{ //{{{
	glColor4f( Red(), Green(), Blue(), Alpha() );
	glPolygonMode( GL_FRONT, GL_FILL );
	glBegin( GL_POLYGON );
		long double delTheta = 2 * M_PI / (long double)( numSegments );
		long double theta = 0;
		for( unsigned int segment = 0; segment < numSegments; ++segment )
		{
			theta = segment * delTheta;
			glVertex2f( radius * cos( theta ) + position.x,
						radius * sin( theta ) + position.y );
		}
	glEnd();
} //}}}

void Polygon::Color( long double nRed, long double nGreen, long double nBlue, long double nAlpha )
{ //{{{
	m_Color[ 0 ] = nRed;
	m_Color[ 1 ] = nGreen;
	m_Color[ 2 ] = nBlue;
	m_Color[ 3 ] = nAlpha;
} //}}}

void Polygon::Color( long double nRed, long double nGreen, long double nBlue )
{ //{{{
	m_Color[ 0 ] = nRed;
	m_Color[ 1 ] = nGreen;
	m_Color[ 2 ] = nBlue;
} //}}}

// {G,S} for m_Color[ 0 ]
long double Polygon::Red() //{{{
{
	return m_Color[ 0 ];
}
void Polygon::Red( long double nRed )
{
	m_Color[ 0 ] = nRed;
} //}}}

// {G,S} for m_Color[ 1 ]
long double Polygon::Green() //{{{
{
	return m_Color[ 1 ];
}
void Polygon::Green( long double nGreen )
{
	m_Color[ 1 ] = nGreen;
} //}}}

// {G,S} for m_Color[ 2 ]
long double Polygon::Blue() //{{{
{
	return m_Color[ 2 ];
}
void Polygon::Blue( long double nBlue )
{
	m_Color[ 2 ] = nBlue;
} //}}}

// {G,S} for m_Color[ 3 ]
long double Polygon::Alpha() //{{{
{
	return m_Color[ 3 ];
}
void Polygon::Alpha( long double nAlpha )
{
	m_Color[ 3 ] = nAlpha;
} //}}}

#endif // POLYGON_CPP
