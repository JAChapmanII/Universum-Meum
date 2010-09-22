#include <SFML/System/Vector2.hpp>
using sf::Vector2;

#include <cmath>

template< class T >
	T Magnitude( Vector2< T > v )
{
	return sqrt( v.x * v.x + v.y * v.y );
}
