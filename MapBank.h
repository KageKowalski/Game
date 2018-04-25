#ifndef MAPBANK_H
#define MAPBANK_H

#include <vector>
#include <string>

#include "Player.h"
#include "NPC.h"
#include "MapBuilder.h"

// MapBank holds all map source data and performs no functions other than giving
// access to this map information. Only a single map is actually built and loaded
// at any time (build() call performed by MapDirector), but all map source data
// are available in MapBank on program startup.
class MapBank : public sf::Transformable {

public:

	// Initializes and stores all map source data.
	bool init();

	// Compiles the specified map's components into a Components structure
	// and returns the bundle. Useful for passing bundle into MapBuilder's build().
	const MapBuilder::Componets getMapComponents(unsigned int ID) const;

	// Retrives the universal tilemap and spritemap transform.
	const sf::Transform& getTransform() const;

private:

	// All ground layers ordered by map ID.
	std::vector<int*> _groundLayerCollection;

	// All second layers ordered by map ID.
	std::vector<int*> _layerTwoCollection;

	// All third layers ordered by map ID.
	std::vector<int*> _layerThreeCollection;

	// All sixth layers ordered by map ID.
	std::vector<int*> _layerSixCollection;

	// All canopy layers ordered by map ID.
	std::vector<int*> _canopyLayerCollection;

	// All map widths ordered by map ID.
	std::vector<int> _widthCollection;

	// All map heights ordered by map ID.
	std::vector<int> _heightCollection;

	// All tileset file names ordered by map ID.
	std::vector<std::string> _tilesetFileNameCollection;

	// Universal sprite sheet file name.
	std::string _universalSpriteSheetFileName;

	// All local sprite sheet file names ordered by map ID.
	std::vector<std::string> _localSpriteSheetFileNameCollection;

	// All characters ordered by map ID.
	std::vector<std::vector<Character*>> _charactersCollection;

	// All music file names ordered by map ID.
	std::vector<std::string> _musicFileNameCollection;

	// All map names ordered by map ID.
	std::vector<std::string> _mapNameCollection;

	// --- SINGLETON IMPLEMENTATION ---
public:

	MapBank(MapBank const&) = delete;
	void operator=(MapBank const&) = delete;

	static MapBank& get() {
		static MapBank instance;
		return        instance;
	}

private:

	MapBank();
	~MapBank();

};

#endif