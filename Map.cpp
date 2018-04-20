#include "Map.h"

//
//
//			CONSTRUCTION FUNCTIONS
//
//

// get unique id, set primitive types, and register listeners
Map::Map(const std::string& name) : _name(name)
{
    static int mapCounter = Utility::unique_id();

	_groundVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
    _layerTwoVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
    _layerThreeVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
    _layerSixVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
    _canopyVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
	_universalSpriteVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
	_localSpriteVerticies.setPrimitiveType(sf::PrimitiveType::Quads);

    EventBus::get().registerListener(Event::EventType::EV_INTERACTABLECONNECTOR, this);
	EventBus::get().registerListener(Event::EventType::EV_RUNDOWN, this);
	EventBus::get().registerListener(Event::EventType::EV_RUNUP, this);
	EventBus::get().registerListener(Event::EventType::EV_RUNLEFT, this);
	EventBus::get().registerListener(Event::EventType::EV_RUNRIGHT, this);
	EventBus::get().registerListener(Event::EventType::EV_WALKDOWN, this);
	EventBus::get().registerListener(Event::EventType::EV_WALKUP, this);
	EventBus::get().registerListener(Event::EventType::EV_WALKLEFT, this);
	EventBus::get().registerListener(Event::EventType::EV_WALKRIGHT, this);
}

// delete map and remove listeners
Map::~Map()
{
    for(auto it = _map.begin(); it != _map.end(); it++)
    {
        delete it->second->ground;
        delete it->second->layerTwo;
        delete it->second->layerThree;
        delete it->second->layerSix;
        delete it->second->canopy;
        _map.erase(it);
    }

    EventBus::get().removeListener(Event::EventType::EV_INTERACTABLECONNECTOR, this);
	EventBus::get().removeListener(Event::EventType::EV_RUNDOWN, this);
	EventBus::get().removeListener(Event::EventType::EV_RUNUP, this);
	EventBus::get().removeListener(Event::EventType::EV_RUNLEFT, this);
	EventBus::get().removeListener(Event::EventType::EV_RUNRIGHT, this);
	EventBus::get().removeListener(Event::EventType::EV_WALKDOWN, this);
	EventBus::get().removeListener(Event::EventType::EV_WALKUP, this);
	EventBus::get().removeListener(Event::EventType::EV_WALKLEFT, this);
	EventBus::get().removeListener(Event::EventType::EV_WALKRIGHT, this);
}

//
//
//			GETTER FUNCTIONS
//
//

// gets VertexArray of designated layer
const sf::VertexArray& Map::getGroundVertices() const {return _groundVerticies;}
const sf::VertexArray& Map::getLayerTwoVertices() const {return _layerTwoVerticies;}
const sf::VertexArray& Map::getLayerThreeVertices() const {return _layerThreeVerticies;}
const sf::VertexArray& Map::getLayerSixVertices() const {return _layerSixVerticies;}
const sf::VertexArray& Map::getCanopyVertices() const {return _canopyVerticies;}

// gets TileSet
const sf::Texture& Map::getTileSet() const {return _tileset.getTexture();}

// gets dimensions
int Map::getWidth() const {return _width;}
int Map::getHeight() const {return _height;}

// gets music
const std::string& Map::getMusic() {return _music;}

// gets name
const std::string& Map::getName() {return _name;}

// gets ID
int Map::getMapID() {return _mapIdentifier;}

// handles events
void Map::handleEvent(Event* const e)
{
    switch (e->getType()) {
        case Event::EV_INTERACTABLECONNECTOR:
            switch(dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().first)
            {
                case 92:
                    _map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-_width-1]->canopy->setGrowID(_map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-_width-1]->canopy->getID());
                    _map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-_width-1]->canopy->setID(-3);
                    _map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-_width]->canopy->setGrowID(_map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-_width]->canopy->getID());
                    _map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-_width]->canopy->setID(-3);
                    _map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-_width+1]->canopy->setGrowID(_map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-_width+1]->canopy->getID());
                    _map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-_width+1]->canopy->setID(-3);
                    break;
            }
            break;
    }
}

// gets sprite sheets
const sf::Texture& Map::getUniversalSpriteSheet() const {return _universalSpriteSheet;}
const sf::Texture& Map::getLocalSpriteSheet() const {return _localSpriteSheet;}

// gets sprite vertices
const sf::VertexArray& Map::getUniversalSpriteVerticies() const {return _universalSpriteVerticies;}
const sf::VertexArray& Map::getLocalSpriteVerticies() const {return _localSpriteVerticies;}

// gets characters
const std::vector<Character*>& Map::getCharacters() const {return _characters;}

// gets reachable characters
std::vector<Character*> Map::getReachableCharacters() const {
	std::vector<Character*> reachables;

	Player const * const player = &Player::get();

	for (Character* character : _characters)
		if (sqrt(pow(character->getCenterPosition().x - player->getCenterPosition().x, 2)
			+ pow(character->getCenterPosition().y - player->getCenterPosition().y, 2)) <= 24.0f
			&& character != &Player::get())
			reachables.push_back(character);

	return reachables;
}

// gets whether player is touching a character
bool Map::isTouching(Character const * const curr, Direction facing) const {
	for (Character* character : _characters)
		if (sqrt(pow(curr->getCenterPosition().x - character->getCenterPosition().x, 2)
			+ pow(curr->getCenterPosition().y - character->getCenterPosition().y, 2)) <= 16.0f
			&& curr != character)
			return true;

	return false;
}

//
//
//			HELPER FUNCTIONS
//
//

// fills the tile VertexArray
void Map::tileVertexFill(std::map<int, LayeredTile*>::iterator it)
{
    // Sets up random tile, Cache ID, y position, and x position
    int groundTileID = it->second->ground->getID();
    int layerTwoTileID = it->second->layerTwo->getID();
    int layerThreeTileID = it->second->layerThree->getID();
    int layerSixTileID = it->second->layerSix->getID();
    int canopyTileID = it->second->canopy->getID();
    float i = it->second->ground->getPosition().y;
    float j = it->second->ground->getPosition().x;
    
    int groundTilePosX = groundTileID % static_cast<int>(_tileset.getWidth() / 16);
    int groundTilePosY = (groundTileID / (_tileset.getWidth() / 16));
    int layTwoTilePosX = layerTwoTileID % static_cast<int>(_tileset.getWidth() / 16);
    int layTwoTilePosY = (layerTwoTileID / (_tileset.getWidth() / 16));
    int layThreeTilePosX = layerThreeTileID % static_cast<int>(_tileset.getWidth() / 16);
    int layThreeTilePosY = (layerThreeTileID / (_tileset.getWidth() / 16));
    int laySixTilePosX = layerSixTileID % static_cast<int>(_tileset.getWidth() / 16);
    int laySixTilePosY = (layerSixTileID / (_tileset.getWidth() / 16));
    int canopyTilePosX = canopyTileID % static_cast<int>(_tileset.getWidth() / 16);
    int canopyTilePosY = (canopyTileID / (_tileset.getWidth() / 16));
    
    // Get a pointer to tile's top-left corner in vertex array
    sf::Vertex* quadGro = &_groundVerticies[(size_t)  ((i * _width + j) * 4 )];
    sf::Vertex* quadTwo = &_layerTwoVerticies[(size_t)((i * _width + j) * 4 )];
    sf::Vertex* quadThree = &_layerThreeVerticies[(size_t)((i * _width + j) * 4 )];
    sf::Vertex* quadSix = &_layerSixVerticies[(size_t)((i * _width + j) * 4 )];
    sf::Vertex* quadCanopy = &_canopyVerticies[(size_t)((i * _width + j) * 4 )];
    
    if(groundTileID != -1)
    {
        quadGro->position  = sf::Vector2f(j * 16.0f,i * 16.0f);
        quadGro->texCoords = sf::Vector2f(groundTilePosX * 16.0f, (groundTilePosY + it->second->ground->getAnimStep()) * 16.0f);
        
        quadGro++;
        quadGro->position  = sf::Vector2f((j + 1) *16.0f, i * 16.0f);
        quadGro->texCoords = sf::Vector2f((groundTilePosX + 1) * 16.0f, (groundTilePosY + it->second->ground->getAnimStep())* 16.0f);
        
        quadGro++;
        quadGro->position  = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadGro->texCoords = sf::Vector2f((groundTilePosX + 1) * 16.0f, (groundTilePosY + 1 + it->second->ground->getAnimStep()) * 16.0f);
        
        quadGro++;
        quadGro->position  = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadGro->texCoords = sf::Vector2f(groundTilePosX * 16.0f, (groundTilePosY + 1 + it->second->ground->getAnimStep()) * 16.0f);
    }
    if(layerTwoTileID != -1)
    {
        quadTwo->position  = sf::Vector2f(j * 16.0f,i * 16.0f);
        quadTwo->texCoords = sf::Vector2f(layTwoTilePosX * 16.0f, (layTwoTilePosY + it->second->layerTwo->getAnimStep()) * 16.0f);
        
        quadTwo++;
        quadTwo->position  = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadTwo->texCoords = sf::Vector2f((layTwoTilePosX + 1) * 16.0f, (layTwoTilePosY + it->second->layerTwo->getAnimStep())* 16.0f);
        
        quadTwo++;
        quadTwo->position  = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadTwo->texCoords = sf::Vector2f((layTwoTilePosX + 1) * 16.0f, (layTwoTilePosY + 1 + it->second->layerTwo->getAnimStep()) * 16.0f);
        
        quadTwo++;
        quadTwo->position  = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadTwo->texCoords = sf::Vector2f(layTwoTilePosX * 16.0f, (layTwoTilePosY + 1 + it->second->layerTwo->getAnimStep()) * 16.0f);
    }
    if(layerThreeTileID != -1)
    {
        quadThree->position  = sf::Vector2f(j * 16.0f,i * 16.0f);
        quadThree->texCoords = sf::Vector2f(layThreeTilePosX * 16.0f, (layThreeTilePosY + it->second->layerThree->getAnimStep()) * 16.0f);
        
        quadThree++;
        quadThree->position  = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadThree->texCoords = sf::Vector2f((layThreeTilePosX + 1) * 16.0f, (layThreeTilePosY + it->second->layerThree->getAnimStep())* 16.0f);
        
        quadThree++;
        quadThree->position  = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadThree->texCoords = sf::Vector2f((layThreeTilePosX + 1) * 16.0f, (layThreeTilePosY + 1 + it->second->layerThree->getAnimStep()) * 16.0f);
        
        quadThree++;
        quadThree->position  = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadThree->texCoords = sf::Vector2f(layThreeTilePosX * 16.0f, (layThreeTilePosY + 1 + it->second->layerThree->getAnimStep()) * 16.0f);
    }
    if(layerSixTileID != -1)
    {
        quadSix->position  = sf::Vector2f(j * 16.0f,i * 16.0f);
        quadSix->texCoords = sf::Vector2f(laySixTilePosX * 16.0f, (laySixTilePosY + it->second->layerSix->getAnimStep()) * 16.0f);
        
        quadSix++;
        quadSix->position  = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadSix->texCoords = sf::Vector2f((laySixTilePosX + 1) * 16.0f, (laySixTilePosY + it->second->layerSix->getAnimStep())* 16.0f);
        
        quadSix++;
        quadSix->position  = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadSix->texCoords = sf::Vector2f((laySixTilePosX + 1) * 16.0f, (laySixTilePosY + 1 + it->second->layerSix->getAnimStep()) * 16.0f);
        
        quadSix++;
        quadSix->position  = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadSix->texCoords = sf::Vector2f(laySixTilePosX * 16.0f, (laySixTilePosY + 1 + it->second->layerSix->getAnimStep()) * 16.0f);
    }
    if(canopyTileID != -1)
    {
        quadCanopy->position  = sf::Vector2f(j * 16.0f,i * 16.0f);
        quadCanopy->texCoords = sf::Vector2f(canopyTilePosX * 16.0f, (canopyTilePosY + it->second->canopy->getAnimStep()) * 16.0f);
        
        quadCanopy++;
        quadCanopy->position  = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadCanopy->texCoords = sf::Vector2f((canopyTilePosX + 1) * 16.0f, (canopyTilePosY + it->second->canopy->getAnimStep())* 16.0f);
        
        quadCanopy++;
        quadCanopy->position  = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadCanopy->texCoords = sf::Vector2f((canopyTilePosX + 1) * 16.0f, (canopyTilePosY + 1 + it->second->canopy->getAnimStep()) * 16.0f);
        
        quadCanopy++;
        quadCanopy->position  = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadCanopy->texCoords = sf::Vector2f(canopyTilePosX * 16.0f, (canopyTilePosY + 1 + it->second->canopy->getAnimStep()) * 16.0f);
    }
}

// fills the sprite VertexArray
void Map::spriteVertexFill(const Character* const character, size_t offset) {
	float i = character->getPosition().y;
	float j = character->getPosition().x;
	unsigned int width = character->getFrameWidth();
	unsigned int height = character->getFrameHeight();
	sf::Vector2f texCoords = character->getTextureCoords();
	unsigned int animStep = character->getCurrAnimStep();

	sf::Vertex* quad = character->isUniversal() ? &_universalSpriteVerticies[offset] : &_localSpriteVerticies[offset];

	quad->position = sf::Vector2f(j, i);
	quad->texCoords = sf::Vector2f(texCoords.x, texCoords.y + (animStep * height));

	quad++;
	quad->position = sf::Vector2f(j + width, i);
	quad->texCoords = sf::Vector2f(texCoords.x + width, texCoords.y + (animStep * height));

	quad++;
	quad->position = sf::Vector2f(j + width, i + height);
	quad->texCoords = sf::Vector2f(texCoords.x + width, texCoords.y + height + (animStep * height));

	quad++;
	quad->position = sf::Vector2f(j, i + height);
	quad->texCoords = sf::Vector2f(texCoords.x, texCoords.y + height + (animStep * height));
}

