#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Character.h"
#include "Player.h"
#include "Tile.h"
#include "Utility.h"

// forward declarations
class MapBuilder;

class Map : public EventListener
{

	// friends
	friend MapBuilder;

public:

	//
	//			PUBLIC VARIABLES
	//

	struct LayeredTile
	{
		Tile* ground;
		Tile* layerTwo;
		Tile* layerThree;
		Tile* layerSix;
		Tile* canopy;
	};

private:

	//
	//			PRIVATE VARIABLES
	//

	// this Map's TileSet
	TileSet _tileset;

	// the structure of this Map
	LayeredTile** _map;

	// width and height of this Map
	int _width;
	int _height;

	// vertex positions of textures
	sf::VertexArray _groundVerticies;
	sf::VertexArray _layerTwoVerticies;
	sf::VertexArray _layerThreeVerticies;
	sf::VertexArray _layerSixVerticies;
	sf::VertexArray _canopyVerticies;

	// unique identifier of this Map and unique identifiers of all Maps connected to this Map
	int _mapIdentifier;
	int* _mapLinks;

	// background music for this Map
	std::string _music;
    
    //True if you are under a roof
    bool _underRoof;

	// name of this Map
	std::string _name;

	// sprite sheets of this Map
	sf::Texture _universalSpriteSheet;
	sf::Texture _localSpriteSheet;

	// sprite verticies of this Map
	sf::VertexArray _universalSpriteVerticies;
	sf::VertexArray _localSpriteVerticies;

	// characters of this Map
	std::vector<Character*> _characters;

public:

	//
	//			CONSTRUCTION FUNCTIONS
	//

	Map();
	virtual ~Map();
    
    void update();

	//
	//			GETTER FUNCTIONS
	//

	// gets VertexArray of designated layer
	const sf::VertexArray& getGroundVertices() const;
	const sf::VertexArray& getLayerTwoVertices() const;
	const sf::VertexArray& getLayerThreeVertices() const;
	const sf::VertexArray& getLayerSixVertices() const;
	const sf::VertexArray& getCanopyVertices() const;

	// gets TileSet
	const sf::Texture& getTileSet() const;

	// gets layered tile map
	const LayeredTile* const * const getLayeredMaps() const;

	// gets dimensions
	int getWidth() const;
	int getHeight() const;

	// gets music
	const std::string& getMusic();

	// gets name
	const std::string& getName();

	// gets id
	int getMapID();

	// gets sprite sheets
	const sf::Texture& getUniversalSpriteSheet() const;
	const sf::Texture& getLocalSpriteSheet() const;

	// gets sprite vertices
	const sf::VertexArray& getUniversalSpriteVerticies() const;
	const sf::VertexArray& getLocalSpriteVerticies() const;

	// gets character information
	const std::vector<Character*>& getCharacters() const;
	std::vector<Character*> getReachableCharacters() const;
	bool isTouching(Character const * const curr, Direction facing) const;

private:

	//
	//			HELPER FUNCTIONS
	//

	// converts the tiles and sprites to vertices
	void tileVertexFill(int x, int y);
	void spriteVertexFill(const Character* const character, size_t offset);

	// handles events
	virtual void handleEvent(Event* const e);

};

#endif
