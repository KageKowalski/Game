#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include "Map.h"

// MapBuilder contains the build process of a Map.
// This class is analogous to a typical machine--give it a list of arguments
// and it produces a product, which in this case is a populated Map.
class MapBuilder {

public:

	// Stores the required components to build a map:
	// 1) Integer array of ground tiles
	// 2) Integer array of layer two tiles
	// 3) Integer array of layer three tiles
	// 4) Integer array of layer six tiles
	// 5) Integer array of canopy tiles
	// 6) Width of integer arrays
	// 7) Height of integer arrays
	// 8) String containing tileset image file name, including file extension
	// 9) String containing universal sprite sheet file name, including file extension
	// 10) String containing local sprite sheet file name, including file extension
	// 11) Vector of pointers to valid Characters
	// 12) String containing background music file name, including file extension
	// 13) String containing name of the map
	struct Componets {
		int const * _groundLayer = nullptr;
		int const * _layerTwo = nullptr;
		int const * _layerThree = nullptr;
		int const * _layerSix = nullptr;
		int const * _canopyLayer = nullptr;
		int _width = 0;
		int _height = 0;
		std::string const * _tilesetFileName = nullptr;
		std::string const * _universalSpriteSheetFileName = nullptr;
		std::string const * _localSpriteSheetFileName = nullptr;
		std::vector<Character*> const * _characters = nullptr;
		std::string const * _musicFileName = nullptr;
		std::string const * _mapName = nullptr;

		// Verifies all components have been provided.
		// Does not check for component legitimacy.
		// If components are not legit, build() will fail.
		bool ready() const;
	};

public:

	// Constructor takes nothing--initializes next map's values.
	MapBuilder();
	~MapBuilder();

	// Builds a map and stores it for future production.
	bool build(const MapBuilder::Componets& components);

	// Produces the constructed map, returning it to the client.
	Map* produce();

private:

	// The current map being constructed for the client.
	Map* _currMap;

};

#endif