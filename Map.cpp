#include "Map.h"

//
//
//			CONSTRUCTION FUNCTIONS
//
//

// get unique id, set primitive types, and register listeners
Map::Map()
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
}

// delete map and remove listeners
Map::~Map()
{
    for(int i = 0; i < _width; i++)
    {
        for(int j = 0; j < _height; j++)
        {
            delete _map[i][j].ground;
            delete _map[i][j].layerTwo;
            delete _map[i][j].layerThree;
            delete _map[i][j].layerSix;
            delete _map[i][j].canopy;
        }
    }
    delete[] _map;

    EventBus::get().removeListener(Event::EventType::EV_INTERACTABLECONNECTOR, this);
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
                    //rewrite
//                    _map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second.x-1]->canopy->setGrowID(_map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-1]->canopy->getID());
//                    _map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-1]->canopy->setID(-3);
//                    _map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-]->canopy->setGrowID(_map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-_width]->canopy->getID());
//                    _map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-_width]->canopy->setID(-3);
//                    _map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-_width+1]->canopy->setGrowID(_map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-_width+1]->canopy->getID());
//                    _map[dynamic_cast<InteractableConnectorEvent*>(e)->getWorkingTile().second-_width+1]->canopy->setID(-3);
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
void Map::tileVertexFill(int x, int y)
{
    // Sets up random tile, Cache ID, y position, and x position
    int groundTileID = _map[x][y].ground->getID();
    int layerTwoTileID = _map[x][y].layerTwo->getID();
    int layerThreeTileID = _map[x][y].layerThree->getID();
    int layerSixTileID = _map[x][y].layerSix->getID();
    int canopyTileID = _map[x][y].canopy->getID();
    float i = x;
    float j = y;
    
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
        quadGro->texCoords = sf::Vector2f(groundTilePosX * 16.0f, (groundTilePosY + _map[x][y].ground->getAnimStep()) * 16.0f);
        
        quadGro++;
        quadGro->position  = sf::Vector2f((j + 1) *16.0f, i * 16.0f);
        quadGro->texCoords = sf::Vector2f((groundTilePosX + 1) * 16.0f, (groundTilePosY + _map[x][y].ground->getAnimStep())* 16.0f);
        
        quadGro++;
        quadGro->position  = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadGro->texCoords = sf::Vector2f((groundTilePosX + 1) * 16.0f, (groundTilePosY + 1 + _map[x][y].ground->getAnimStep()) * 16.0f);
        
        quadGro++;
        quadGro->position  = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadGro->texCoords = sf::Vector2f(groundTilePosX * 16.0f, (groundTilePosY + 1 + _map[x][y].ground->getAnimStep()) * 16.0f);
    }
    if(layerTwoTileID != -1)
    {
        quadTwo->position  = sf::Vector2f(j * 16.0f,i * 16.0f);
        quadTwo->texCoords = sf::Vector2f(layTwoTilePosX * 16.0f, (layTwoTilePosY + _map[x][y].layerTwo->getAnimStep()) * 16.0f);
        
        quadTwo++;
        quadTwo->position  = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadTwo->texCoords = sf::Vector2f((layTwoTilePosX + 1) * 16.0f, (layTwoTilePosY + _map[x][y].layerTwo->getAnimStep())* 16.0f);
        
        quadTwo++;
        quadTwo->position  = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadTwo->texCoords = sf::Vector2f((layTwoTilePosX + 1) * 16.0f, (layTwoTilePosY + 1 + _map[x][y].layerTwo->getAnimStep()) * 16.0f);
        
        quadTwo++;
        quadTwo->position  = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadTwo->texCoords = sf::Vector2f(layTwoTilePosX * 16.0f, (layTwoTilePosY + 1 + _map[x][y].layerTwo->getAnimStep()) * 16.0f);
    }
    if(layerThreeTileID != -1)
    {
        quadThree->position  = sf::Vector2f(j * 16.0f,i * 16.0f);
        quadThree->texCoords = sf::Vector2f(layThreeTilePosX * 16.0f, (layThreeTilePosY + _map[x][y].layerThree->getAnimStep()) * 16.0f);
        
        quadThree++;
        quadThree->position  = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadThree->texCoords = sf::Vector2f((layThreeTilePosX + 1) * 16.0f, (layThreeTilePosY + _map[x][y].layerThree->getAnimStep())* 16.0f);
        
        quadThree++;
        quadThree->position  = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadThree->texCoords = sf::Vector2f((layThreeTilePosX + 1) * 16.0f, (layThreeTilePosY + 1 + _map[x][y].layerThree->getAnimStep()) * 16.0f);
        
        quadThree++;
        quadThree->position  = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadThree->texCoords = sf::Vector2f(layThreeTilePosX * 16.0f, (layThreeTilePosY + 1 + _map[x][y].layerThree->getAnimStep()) * 16.0f);
    }
    if(layerSixTileID != -1)
    {
        quadSix->position  = sf::Vector2f(j * 16.0f,i * 16.0f);
        quadSix->texCoords = sf::Vector2f(laySixTilePosX * 16.0f, (laySixTilePosY + _map[x][y].layerSix->getAnimStep()) * 16.0f);
        if(_underRoof) quadSix->color.a = 75;
        else          quadSix->color.a = 255;
        
        quadSix++;
        quadSix->position  = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadSix->texCoords = sf::Vector2f((laySixTilePosX + 1) * 16.0f, (laySixTilePosY + _map[x][y].layerSix->getAnimStep())* 16.0f);
        if(_underRoof) quadSix->color.a = 75;
        else          quadSix->color.a = 255;
        
        quadSix++;
        quadSix->position  = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadSix->texCoords = sf::Vector2f((laySixTilePosX + 1) * 16.0f, (laySixTilePosY + 1 + _map[x][y].layerSix->getAnimStep()) * 16.0f);
        if(_underRoof) quadSix->color.a = 75;
        else          quadSix->color.a = 255;
        
        quadSix++;
        quadSix->position  = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadSix->texCoords = sf::Vector2f(laySixTilePosX * 16.0f, (laySixTilePosY + 1 + _map[x][y].layerSix->getAnimStep()) * 16.0f);
        if(_underRoof) quadSix->color.a = 75;
        else          quadSix->color.a = 255;
    }
    if(canopyTileID != -1)
    {
        quadCanopy->position  = sf::Vector2f(j * 16.0f,i * 16.0f);
        quadCanopy->texCoords = sf::Vector2f(canopyTilePosX * 16.0f, (canopyTilePosY + _map[x][y].canopy->getAnimStep()) * 16.0f);
        
        quadCanopy++;
        quadCanopy->position  = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadCanopy->texCoords = sf::Vector2f((canopyTilePosX + 1) * 16.0f, (canopyTilePosY + _map[x][y].canopy->getAnimStep())* 16.0f);
        
        quadCanopy++;
        quadCanopy->position  = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadCanopy->texCoords = sf::Vector2f((canopyTilePosX + 1) * 16.0f, (canopyTilePosY + 1 + _map[x][y].canopy->getAnimStep()) * 16.0f);
        
        quadCanopy++;
        quadCanopy->position  = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadCanopy->texCoords = sf::Vector2f(canopyTilePosX * 16.0f, (canopyTilePosY + 1 + _map[x][y].canopy->getAnimStep()) * 16.0f);
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

void Map::update() {
    for (size_t i = 0; i < _characters.size(); i++) {
        _characters.at(i)->update(Chrono::get().getDeltaTime());
        spriteVertexFill(_characters.at(i), i * 4);
    }
    bool roof = false;
    for(int i = 0 ; i < _width; i++)
    {
        for(int j = 0; j < _height; j++)
        {
            if(_map[i][j].layerSix->getGlobalBounds().contains(Player::get().getCenterPosition()) && _map[i][j].layerSix->getID() != -1)
            {
                roof = true;
            }
            if((_map[i][j].layerTwo->getGlobalBounds().intersects(Player::get().getGlobalBounds()) || _map[i][j].layerThree->getGlobalBounds().intersects(Player::get().getGlobalBounds())) && (_map[i][j].layerTwo->getID() != -1 || _map[i][j].layerThree->getID() != -1))
            {
                std::unique_ptr<Event> e = std::make_unique<CollisionEvent>();
                EventBus::get().postEvent(e);
            }
            _map[i][j].ground->update();
            _map[i][j].layerTwo->update();
            _map[i][j].layerThree->update();
            _map[i][j].layerSix->update();
            _map[i][j].canopy->update();
            tileVertexFill(i, j);
        }
    }
    if(roof) _underRoof = true;
    else     _underRoof = false;
}
