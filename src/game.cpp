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
	this->loadModules();

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
	unloadModules();
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

/// Iterates through each actor that has been registered and calls its Draw function
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
	for( std::vector< Click >::iterator i = m_Clicks.begin(); i != m_Clicks.end(); i++ ) //{{{
	{
		if( ( i->button == SDL_BUTTON_WHEELUP ) || ( i->button == SDL_BUTTON_WHEELDOWN ) )
		{
			m_Clicks.erase( i );
			break;
		}
	} //}}}
	// handle all SDL events that we might've received in this loop
	// iteration TODO can this SDL_Poll... error?
	while( SDL_PollEvent( &m_Event ) )
	{
		switch( m_Event.type )
		{
			// user has clicked on the window's close button
			case SDL_QUIT:
			{ //{{{
				// set the done flag
				isDone( true );
				return;
			} //}}}

			// window has gained/lost attention
			case SDL_ACTIVEEVENT:
			{ //{{{
				if( m_Event.active.gain == 0 )
				{
					// lost focus
					isActive( false );
				}
				else
				{
					// gained focus
					isActive( true );
				}
				break;
			} //}}}

			// A key was pressed
			case SDL_KEYDOWN:
			{ //{{{
				m_Keypresses.push_back( Keypress( m_Event.key.keysym.sym, GetTicks() ) );
				break;
			} //}}}

			// A key was released
			case SDL_KEYUP:
			{ //{{{
				for( std::vector< Keypress >::iterator i = m_Keypresses.begin();
						i != m_Keypresses.end(); ++i )
				{
					if( i->SymCode() == m_Event.key.keysym.sym )
					{
						m_Keypresses.erase( i );
						break;
					}
				}
				break;
			} //}}}

			case SDL_MOUSEMOTION:
			{ //{{{
				m_Cursor.x = m_Event.motion.x;
				m_Cursor.y = m_Event.motion.y;
				break;
			} //}}}

			case SDL_MOUSEBUTTONDOWN:
			{ //{{{
				m_Clicks.push_back( Click( m_Event.button.x, m_Event.button.y,
									m_Event.button.button, GetTicks() ) );
				break;
			} //}}}

			case SDL_MOUSEBUTTONUP:
			{ //{{{
				if( ( m_Event.button.button == SDL_BUTTON_WHEELUP ) ||
					( m_Event.button.button == SDL_BUTTON_WHEELDOWN ) )
				{
					break;
				}
				for( std::vector< Click >::iterator i = m_Clicks.begin();
						i != m_Clicks.end(); i++ )
				{
					if( i->button == m_Event.button.button )
					{
						m_Clicks.erase( i );
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

/// {G,S}etter for m_Width
void Game::Width( unsigned int nWidth ) //{{{
{
	m_Width = nWidth;
}
unsigned int Game::Width()
{
	return m_Width;
} //}}}

/// {G,S}etter for m_Height
void Game::Height( unsigned int nHeight ) //{{{
{
	m_Height = nHeight;
}
unsigned int Game::Height()
{
	return m_Height;
} //}}}

/// {G,S}etter for m_BPP
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
	now = GetTicks();

	if( m_NextTime > now )
	{
		SDL_Delay( m_NextTime - now );
	}
	else
	{
		/*
		char[] tlog = "Behind: " ~
			Integer.toString( cast( int )( m_NextTime - now ) );
		log.info( tlog );
		*/
	}
	m_NextTime += m_TickInterval;
} //}}}

void Game::sleep( unsigned int microSeconds )
{ //{{{
	SDL_Delay( microSeconds );
} //}}}

/// {G,S}etter for m_TickInterval
void Game::TickInterval( unsigned int nTickInterval ) //{{{
{
	m_TickInterval = nTickInterval;
}
unsigned int Game::TickInterval()
{
	return m_TickInterval;
} //}}}

/// {G,S}etter for m_isDone
void Game::isDone( bool nState ) //{{{
{
	m_isDone = nState;
}
bool Game::isDone()
{
	return m_isDone;
} //}}}

/// {G,S}etter for m_isActive
void Game::isActive( bool nState ) //{{{
{
	m_isActive = nState;
}
bool Game::isActive()
{
	return m_isActive;
} //}}}

/// Getter for m_ViewWidth
/*void Game::ViewWidth( long double nViewWidth ) //{{{
{
	m_ViewWidth = nViewWidth;
}*/
long double Game::ViewWidth()
{
	return m_ViewWidth;
} //}}}

/// Getter for m_ViewHeight
/*void Game::ViewHeight( long double nViewHeight ) //{{{
{
	m_ViewHeight = nViewHeight;
}*/
long double Game::ViewHeight()
{
	return m_ViewHeight;
} //}}}

/// Setter for both X/Y centers
void Game::Centers( long double nXC, long double nYC ) //{{{
{
	this->position.x = nXC - ViewWidth() / 2;
	this->position.y = nYC - ViewHeight() / 2;
} //}}}

/// {G,S}etter for the X center
long double Game::XCenter() //{{{
{
	return ViewWidth() / 2 + this->position.x;
}
void Game::XCenter( long double nXC )
{
	this->position.x = nXC - ViewWidth() / 2;
} //}}}

/// {G,S}etter for the Y center
long double Game::YCenter() //{{{
{
	return ViewHeight() / 2 + this->position.y;
}
void Game::YCenter( long double nYC )
{
	this->position.y = nYC - ViewHeight() / 2;
} //}}}

/// {G,S}etter for the Cursor X
unsigned int Game::CursorX() //{{{
{
	return m_Cursor.x;
}
void Game::CursorX( unsigned int nCX )
{
	WarpMouse( nCX, m_Cursor.y );
} //}}}

/// {G,S}etter for the Cursor Y
unsigned int Game::CursorY() //{{{
{
	return m_Cursor.y;
}
void Game::CursorY( unsigned int nCY )
{
	WarpMouse( m_Cursor.x, nCY );
} //}}}

/// {G,S}etter for the Zoom
void Game::Zoom( long double nZoom ) //{{{
{
	m_Zoom = nZoom;
}
long double Game::Zoom()
{
	return m_Zoom;
} //}}}

Game::Game()
{
}

Game::Game( unsigned int iWidth, unsigned int iHeight, unsigned int iBPP )
{
	InitSGL( iWidth, iHeight, iBPP );
}

Game::Game( Game const& )
{
}

Game& Game::operator=( Game const& )
{
	return *this;
}

// load modules needed to interface with C libs SDL, GL, IL
void Game::loadModules()
{ //{{{
	if( ! m_ModulesLoaded )
	{
		// TODO Uhh......
		m_ModulesLoaded = true;
	}
	else
	{
		// TODO Error
	}
} //}}}

// unload modules needed to interface with C libs SDL, GL, IL
void Game::unloadModules()
{ //{{{
	if( m_ModulesLoaded )
	{
		// TODO Uhm???
		m_ModulesLoaded = false;
	}
	else
	{
		// TODO something...
	}
} //}}}

// toggle {un}loaded state of modules
void Game::toggleModules()
{ //{{{
	if( m_ModulesLoaded )
	{
		unloadModules();
	}
	else
	{
		loadModules();
	}
} //}}}

Game *Game::m_Instance = 0;
