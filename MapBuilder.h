#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include "Map.h"

// MapBuilder contains the build process of a Map.
// This class is analogous to a typical machine--give it a list of arguments
// and it produces a product, which in this case is a populated Map.
class MapBuilder {

public:

	// Constructor takes nothing--initializes next map's values.
	MapBuilder();
	~MapBuilder();

	// Builds a map using the following arguments:
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
	// --- Optional arguments downward ---
	// 13) String containing name of the map
	bool build(int* groundLayer, int* layerTwo, int* layerThree, int* layerSix, int* canopyLayer,
		int width, int height, const std::string& tilesetFileName, const std::string& universalSpriteSheetFileName,
		const std::string& localSpriteSheetFileName, const std::vector<Character*>& characters,
		const std::string& musicFileName, const std::string& mapName = "DEFAULT");

	// Produces the constructed map, returning it to the client.
	Map* produce();

private:

	// The current map being constructed for the client.
	Map* _currMap;

};

#endif