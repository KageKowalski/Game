#ifndef DIRECTION_H
#define DIRECTION_H

// All cardinal directions.
// May be used for signaling which direction an object is moving, facing, etc.
enum class Direction {
	DOWN,
	UP,
	LEFT,
	RIGHT
};

// All diagonal directions.
// May be used to deal with that fact that multiple cardinal directions can be
// in play in a single instance.
enum class DiagonalDirection {
	DOWN_LEFT,
	DOWN_RIGHT,
	UP_LEFT,
	UP_RIGHT
};

#endif