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
#ifndef POINT_CPP
#define POINT_CPP

#include "point.hpp"

Point::Point( long double iX, long double iY ) :
	Entity( iX, iY, 0 ), //{{{
	radius( 1 ),
	noZoom( false )
{
	this->position.x = iX;
	this->position.y = iY;
	Color( 1.0f, 1.0f, 1.0f, 1.0f );
} //}}}

Point::Point( long double iX, long double iY, long double iRadius ) :
	Entity( iX, iY, 0 ), //{{{
	radius( iRadius ),
	noZoom( false )
{
	this->position.x = iX;
	this->position.y = iY;
	Color( 1.0f, 1.0f, 1.0f, 1.0f );
} //}}}

Point::Point( long double iX, long double iY, long double iRadius, long double iRed, long double iGreen, long double iBlue ) :
	Entity( iX, iY, 0 ), //{{{
	radius( iRadius ),
	noZoom( false )
{
	this->position.x = iX;
	this->position.y = iY;
	Color( iRed, iGreen, iBlue, 1.0f );
} //}}}

Point::Point( long double iX, long double iY, long double iRadius, long double iRed, long double iGreen, long double iBlue, long double iAlpha ) :
	Entity( iX, iY, 0 ), //{{{
	radius( iRadius ),
	noZoom( false )
{
	this->position.x = iX;
	this->position.y = iY;
	Color( iRed, iGreen, iBlue, iAlpha );
} //}}}

void Point::Draw( long double zoom )
{ //{{{
	// glPointSize takes a diameter
	if( !noZoom )
	{
		glPointSize( this->radius * 2 * zoom );
	}
	else
	{
		glPointSize( this->radius * 2 );
	}
	glColor4f( Red(), Green(), Blue(), Alpha() );
	glBegin( GL_POINTS );
	glVertex2f( this->position.x, this->position.y );
	glEnd();
} //}}}

void Point::Color( long double nRed, long double nGreen, long double nBlue, long double nAlpha )
{ //{{{
	m_Color[ 0 ] = nRed;
	m_Color[ 1 ] = nGreen;
	m_Color[ 2 ] = nBlue;
	m_Color[ 3 ] = nAlpha;
} //}}}

void Point::Color( long double nRed, long double nGreen, long double nBlue )
{ //{{{
	m_Color[ 0 ] = nRed;
	m_Color[ 1 ] = nGreen;
	m_Color[ 2 ] = nBlue;
} //}}}

// {G,S} for m_Color[ 0 ]
long double Point::Red() //{{{
{
	return m_Color[ 0 ];
}
void Point::Red( long double nRed )
{
	m_Color[ 0 ] = nRed;
} //}}}

// {G,S} for m_Color[ 1 ]
long double Point::Green() //{{{
{
	return m_Color[ 1 ];
}
void Point::Green( long double nGreen )
{
	m_Color[ 1 ] = nGreen;
} //}}}

// {G,S} for m_Color[ 2 ]
long double Point::Blue() //{{{
{
	return m_Color[ 2 ];
}
void Point::Blue( long double nBlue )
{
	m_Color[ 2 ] = nBlue;
} //}}}

// {G,S} for m_Color[ 3 ]
long double Point::Alpha() //{{{
{
	return m_Color[ 3 ];
}
void Point::Alpha( long double nAlpha )
{
	m_Color[ 3 ] = nAlpha;
} //}}}

#endif // POINT_CPP
