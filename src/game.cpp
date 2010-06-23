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
#include <vector>

#include "game.hpp"

static char PROGRAM_NAME[ 15 ] = "Universum Meum";

Game* Game::Instance()
{ //{{{
	if( !m_Instance )
	{
		m_Instance = new Game;
	}
	return m_Instance;
} //}}}

Game* Game::Instance( unsigned int iWidth, unsigned int iHeight, unsigned int iBPP )
{ //{{{
	// TODO not well
	if( !m_Instance )
	{
		m_Instance = new Game( iWidth, iHeight, iBPP );
	}
	return m_Instance;
	/*
	if( m_Instance == 0 )
	{
		// TODO Error handling C++ style
			m_Instance = new Game( iWidth, iHeight, iBPP );
	}
	return m_Instance;
	*/
} //}}}

void Game::InitSGL( unsigned int iWidth, unsigned int iHeight, unsigned int iBPP )
{ //{{{
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
		// TODO used to throw exception
	}
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_SetVideoMode( iWidth, iHeight, iBPP, SDL_OPENGL );

	Width( iWidth );
	Height( iHeight );
	BPP( iBPP );
	ResizeViewport( iWidth, iHeight );

	SDL_WM_SetCaption( PROGRAM_NAME, 0 );

	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glEnable( GL_POINT_SMOOTH );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_POINT_SMOOTH );
	glEnable( GL_DEPTH_TEST );
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
} //}}}

void Game::DeinitSGL()
{ //{{{
	SDL_Quit();
} //}}}

void Game::ResizeViewport( long double nWidth, long double nHeight )
{ //{{{
	m_ViewWidth = nWidth;
	m_ViewHeight = nHeight;
	ResizeViewport();
} //}}}

void Game::ResizeViewport()
{ //{{{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, ViewWidth(), 0, ViewHeight(), -10, 10 );
	glMatrixMode( GL_MODELVIEW );
	Zoom( Width() / ViewWidth() );
} //}}}

void Game::Draw( long double magZoom )
{ //{{{
	glPushMatrix();
	glTranslatef( -this->position.x, -this->position.y, 0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	for( std::vector< Entity* >::iterator i = m_Entities.begin(); i != m_Entities.end(); i++ )
	{
		// TODO null i?
			(*i)->Draw( Zoom() * magZoom );
	}
	glPopMatrix();
	SDL_GL_SwapBuffers();
} //}}}

void Game::ProcessInput()
{ //{{{
	/// Ditch old mousewheel events
	/// TODO look into a better way to do this, as currently we're throwing away potentially
	/// valid data. This is because each mouse wheel "click" is actually a press and release
	/// at the same time.
	for( std::vector< Click >::iterator i = this->m_Clicks.begin(); i != this->m_Clicks.end(); i++ ) //{{{
	{
		if( ( i->button == SDL_BUTTON_WHEELUP ) || ( i->button == SDL_BUTTON_WHEELDOWN ) )
		{
			m_Clicks.erase( i );
			break;
		}
	} //}}}
	// handle all SDL events that we might've received in this loop
	// iteration TODO can this SDL_Poll... error?
	while( SDL_PollEvent( &this->m_Event ) )
	{
		switch( this->m_Event.type )
		{
			// user has clicked on the window's close button
			case SDL_QUIT:
			{ //{{{
				// set the done flag
				this->isDone = true;
				return;
			} //}}}

			// window has gained/lost attention
			case SDL_ACTIVEEVENT:
			{ //{{{
				if( this->m_Event.active.gain == 0 )
				{
					// lost focus
					this->isActive = false;
				}
				else
				{
					// gained focus
					this->isActive = true;
				}
				break;
			} //}}}

			// A key was pressed
			case SDL_KEYDOWN:
			{ //{{{
				this->m_Keypresses.push_back( Keypress( m_Event.key.keysym.sym, GetTicks() ) );
				break;
			} //}}}

			// A key was released
			case SDL_KEYUP:
			{ //{{{
				for( std::vector< Keypress >::iterator i = this->m_Keypresses.begin();
						i != this->m_Keypresses.end(); ++i )
				{
					if( i->SymCode() == this->m_Event.key.keysym.sym )
					{
						this->m_Keypresses.erase( i );
						break;
					}
				}
				break;
			} //}}}

			case SDL_MOUSEMOTION:
			{ //{{{
				this->m_Cursor.x = m_Event.motion.x;
				this->m_Cursor.y = m_Event.motion.y;
				break;
			} //}}}

			case SDL_MOUSEBUTTONDOWN:
			{ //{{{
				this->m_Clicks.push_back( Click( m_Event.button.x, m_Event.button.y,
												 m_Event.button.button, GetTicks() ) );
				break;
			} //}}}

			case SDL_MOUSEBUTTONUP:
			{ //{{{
				if( ( this->m_Event.button.button == SDL_BUTTON_WHEELUP ) ||
					( this->m_Event.button.button == SDL_BUTTON_WHEELDOWN ) )
				{
					break;
				}
				for( std::vector< Click >::iterator i = this->m_Clicks.begin();
						i != this->m_Clicks.end(); i++ )
				{
					if( i->button == this->m_Event.button.button )
					{
						this->m_Clicks.erase( i );
						break;
					}
				}
				break;
			} //}}}

			// by default, we do nothing => break from the switch
			default:
			{ //{{{
				break;
			} //}}}
		}
	}

	return;
} //}}}

bool Game::isClicked( unsigned int toCheckFor )
{ //{{{
	for( std::vector< Click >::iterator i = m_Clicks.begin(); i != m_Clicks.end(); i++ )
	{
		if( i->button == toCheckFor )
		{
			return true;
		}
	}
	return false;
} //}}}

unsigned int Game::ClickX( unsigned int button )
{ //{{{
	for( std::vector< Click >::iterator i = m_Clicks.begin(); i != m_Clicks.end(); i++ )
	{
		if( i->button == button )
		{
			return i->position.x;
		}
	}
	return -1;
	// TODO throw something
} //}}}

unsigned int Game::ClickY( unsigned int button )
{ //{{{
	for( std::vector< Click >::iterator i = m_Clicks.begin(); i != m_Clicks.end(); i++ )
	{
		if( i->button == button )
		{
			return i->position.x;
		}
	}
	return -1;
	// TODO throw something
} //}}}

unsigned int Game::ClickCreateTime( unsigned int button )
{ //{{{
	for( std::vector< Click >::iterator i = m_Clicks.begin(); i != m_Clicks.end(); i++ )
	{
		if( i->button == button )
		{
			return i->createTime;
		}
	}
	return -1;
	// TODO throw something
} //}}}

void Game::WarpMouse( unsigned int nX, unsigned int nY )
{ //{{{
	m_Cursor.x = nX;
	m_Cursor.y = nY;
	SDL_WarpMouse( nX, nY);
} //}}}

bool Game::isPressed( unsigned int toCheckFor )
{ //{{{
	for( std::vector< Keypress >::iterator i = m_Keypresses.begin(); i != m_Keypresses.end(); i++ )
	{
		if( i->SymCode() == toCheckFor )
		{
			return true;
		}
	}
	return false;
} //}}}

unsigned int Game::PressCreateTime( unsigned int button )
{ //{{{
	for( std::vector< Keypress >::iterator i = m_Keypresses.begin(); i != m_Keypresses.end(); i++ )
	{
		if( i->SymCode() == button )
		{
			return i->CreateTime();
		}
	}
	return -1;
	// TODO throw something
} //}}}

void Game::Width( unsigned int nWidth ) //{{{
{
	m_Width = nWidth;
}
unsigned int Game::Width()
{
	return m_Width;
} //}}}

void Game::Height( unsigned int nHeight ) //{{{
{
	m_Height = nHeight;
}
unsigned int Game::Height()
{
	return m_Height;
} //}}}

void Game::BPP( unsigned int nBPP ) //{{{
{
	m_BPP = nBPP;
}
unsigned int Game::BPP()
{
	return m_BPP;
} //}}}

void Game::AddEntity( Entity *nEntity )
{ //{{{
	if( nEntity != 0 )
	{
		m_Entities.push_back( nEntity );
	}
	else
	{
		// TODO Error
	}
} //}}}

void Game::RemoveEntity( Entity *toRemove )
{ //{{{
	if( toRemove == NULL )
	{
		return;
	}
	for( std::vector< Entity* >::iterator i = m_Entities.begin(); i != m_Entities.end(); ++i )
	{
		if( (*i) == toRemove )
		{
			m_Entities.erase( i );
			break;
		}
	}
} //}}}

unsigned int Game::GetTicks()
{ //{{{
	return SDL_GetTicks();
} //}}}

void Game::WaitFor()
{ //{{{
	static unsigned int now;
	now = this->GetTicks();

	if( this->nextTime > now )
	{
		SDL_Delay( this->nextTime - now );
	}
	else
	{
		/*
		char[] tlog = "Behind: " ~
			Integer.toString( cast( int )( m_NextTime - now ) );
		log.info( tlog );
		*/
	}
	this->nextTime += this->tickInterval;
} //}}}

void Game::sleep( unsigned int microSeconds )
{ //{{{
	SDL_Delay( microSeconds );
} //}}}

/*void Game::ViewWidth( long double nViewWidth ) //{{{
{
	m_ViewWidth = nViewWidth;
}*/
long double Game::ViewWidth()
{
	return m_ViewWidth;
} //}}}

/*void Game::ViewHeight( long double nViewHeight ) //{{{
{
	m_ViewHeight = nViewHeight;
}*/
long double Game::ViewHeight()
{
	return m_ViewHeight;
} //}}}

void Game::Centers( long double nXC, long double nYC ) //{{{
{
	this->position.x = nXC - ViewWidth() / 2;
	this->position.y = nYC - ViewHeight() / 2;
} //}}}

long double Game::XCenter() //{{{
{
	return ViewWidth() / 2 + this->position.x;
}
void Game::XCenter( long double nXC )
{
	this->position.x = nXC - ViewWidth() / 2;
} //}}}

long double Game::YCenter() //{{{
{
	return ViewHeight() / 2 + this->position.y;
}
void Game::YCenter( long double nYC )
{
	this->position.y = nYC - ViewHeight() / 2;
} //}}}

unsigned int Game::CursorX() //{{{
{
	return m_Cursor.x;
}
void Game::CursorX( unsigned int nCX )
{
	WarpMouse( nCX, m_Cursor.y );
} //}}}

unsigned int Game::CursorY() //{{{
{
	return m_Cursor.y;
}
void Game::CursorY( unsigned int nCY )
{
	WarpMouse( m_Cursor.x, nCY );
} //}}}

void Game::Zoom( long double nZoom ) //{{{
{
	m_Zoom = nZoom;
}
long double Game::Zoom()
{
	return m_Zoom;
} //}}}

Game::Game() : //{{{
	tickInterval( 0 ),
	nextTime( 0 ),
	isDone( false ),
	isActive( true ),
	m_Width( 0 ),
	m_Height( 0 ),
	m_BPP( 0 ),
	m_ViewWidth( 0 ),
	m_ViewHeight( 0 ),
	m_Entities(),
	m_Event(),
	m_Keypresses(),
	m_Clicks(),
	m_Cursor(),
	m_Zoom( 0 )
{
} //}}}

Game::Game( unsigned int iWidth, unsigned int iHeight, unsigned int iBPP ) : //{{{
	tickInterval( 0 ),
	nextTime( 0 ),
	isDone( false ),
	isActive( true ),
	m_Width( iWidth ),
	m_Height( iHeight ),
	m_BPP( iBPP ),
	m_ViewWidth( iWidth ),
	m_ViewHeight( iHeight ),
	m_Entities(),
	m_Event(),
	m_Keypresses(),
	m_Clicks(),
	m_Cursor(),
	m_Zoom( 0 )
{
	InitSGL( iWidth, iHeight, iBPP );
} //}}}

Game::Game( Game const& r ) : //{{{
	Entity( r.position ),
	tickInterval( r.tickInterval ),
	nextTime( r.nextTime ),
	isDone( r.isDone ),
	isActive( r.isActive ),
	m_Width( r.m_Width ),
	m_Height( r.m_Height ),
	m_BPP( r.m_BPP ),
	m_ViewWidth( r.m_ViewWidth ),
	m_ViewHeight( r.m_ViewHeight ),
	m_Entities( r.m_Entities ),
	m_Event( r.m_Event ),
	m_Keypresses( r.m_Keypresses ),
	m_Clicks( r.m_Clicks ),
	m_Cursor( r.m_Cursor ),
	m_Zoom( r.m_Zoom )
{
} //}}}

Game& Game::operator=( Game const& ) //{{{
{
	return *this;
} //}}}

Game *Game::m_Instance = 0;
