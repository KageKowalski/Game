//Josh Seelye
#include "TileMap.h"

/********************************
    Tile Functions/Constructors
 ********************************/

TileMap::Tile::Tile() : tileID(-1), steps(-1) {}
TileMap::Tile::Tile(int ID, const sf::Vector2f& postition) : tileID(ID)
{
	setPosition(postition);
}

int  TileMap::Tile::getID()         { return tileID; }
void TileMap::Tile::setID(int ID)   { tileID = ID;   }
int  TileMap::Tile::getStepAmount(){ return steps; }

/********************************
  TileMap Functions/Constructors
 ********************************/

TileMap::TileMap(const sf::Vector2f& scale)
{
	m_groundVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
	setScale(scale);
}

bool TileMap::build(int* ground, int* layerOne, int* layerTwo, int width, int height, std::string tilesetFileName)
{
    if(!_tileset.loadFromFile(tilesetFileName)) return false;
    _width = width;
    _height = height;

	m_groundVerticies.resize(_width * _height * 4 * 3);

    _ground   = new Tile*[_height];
    _layerOne = new Tile*[_height];
    _layerTwo = new Tile*[_height];
    for(int i = 0; i<_height;i++)
    {
        _ground[i]   = new Tile[_width];
        _layerOne[i] = new Tile[_width];
        _layerTwo[i] = new Tile[_width];
    }
    for(int i = 0; i < _height; i++)
    {
        for(int j = 0; j < _width; j++)
        {
            _ground[i][j]   = Tile(ground[i*_width+j],   sf::Vector2f(static_cast<float>(i), static_cast<float>(j)));
            _layerOne[i][j] = Tile(layerOne[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)));
            _layerTwo[i][j] = Tile(layerTwo[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)));
			vertexFill(i, j);
        }
    }
    return true;
}

TileMap::~TileMap()
{
    for(int i = 0; i < _height; i++)
    {
        delete[] _ground[i];
        delete[] _layerOne[i];
        delete[] _layerTwo[i];
    }
    delete[] _ground;
    delete[] _layerOne;
    delete[] _layerTwo;
}

void TileMap::vertexFill(int y, int x)
{
	// Sets up random tile, Cache ID, y position, and x position
	int groundTileID = _ground[y][x].getID();
    int layerOneTileID = _layerOne[y][x].getID();
    int layerTwoTileID = _layerTwo[y][x].getID();
	float i = _ground[y][x].getPosition().x;
	float j = _ground[y][x].getPosition().y;

	// Calculate position of tile graphic in tileset in tile units
	int groundTilePosX = groundTileID % static_cast<int>(_tileset.getSize().x / 16);
    int groundTilePosY = (groundTileID / _tileset.getSize().x) * 16;
	m_groundVerticies[(size_t)((i * _width + j) * 4 * 3)];

	// Get a pointer to tile's top-left corner in vertex array
	sf::Vertex* quad = &m_groundVerticies[(size_t)((i * _width + j) * 4 * 3)];

    if(groundTileID != -1)
    {
        // Define top-left corner
        quad->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quad->texCoords = sf::Vector2f(groundTilePosX * 16.0f, (groundTilePosY) * 16.0f);

        // Define top-right corner
        quad++;
        quad->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quad->texCoords = sf::Vector2f((groundTilePosX + 1) * 16.0f, (groundTilePosY)* 16.0f);

        // Define bottom-right corner
        quad++;
        quad->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quad->texCoords = sf::Vector2f((groundTilePosX + 1) * 16.0f, (groundTilePosY + 1) * 16.0f);

        // Define bottom-left corner
        quad++;
        quad->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quad->texCoords = sf::Vector2f(groundTilePosX * 16.0f, (groundTilePosY + 1) * 16.0f);
        
        quad++;
    }
    if(layerOneTileID != -1)
    {
        int layOneTilePosX = layerOneTileID % static_cast<int>(_tileset.getSize().x / 16);
        int layOneTilePosY = (layerOneTileID / _tileset.getSize().x) * 16;

        quad->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quad->texCoords = sf::Vector2f(layOneTilePosX * 16.0f, (layOneTilePosY) * 16.0f);
        
        // Define top-right corner
        quad++;
        quad->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quad->texCoords = sf::Vector2f((layOneTilePosX + 1) * 16.0f, (layOneTilePosY)* 16.0f);
        
        // Define bottom-right corner
        quad++;
        quad->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quad->texCoords = sf::Vector2f((layOneTilePosX + 1) * 16.0f, (layOneTilePosY + 1) * 16.0f);
        
        // Define bottom-left corner
        quad++;
        quad->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quad->texCoords = sf::Vector2f(layOneTilePosX * 16.0f, (layOneTilePosY + 1) * 16.0f);
        
        quad++;
    }
    if(layerTwoTileID != -1)
    {
        int layTwoTilePosX = layerTwoTileID % static_cast<int>(_tileset.getSize().x / 16);
        int layTwoTilePosY = (layerTwoTileID / _tileset.getSize().x) * 16;
        
        quad->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quad->texCoords = sf::Vector2f(layTwoTilePosX * 16.0f, (layTwoTilePosY) * 16.0f);
        
        // Define top-right corner
        quad++;
        quad->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quad->texCoords = sf::Vector2f((layTwoTilePosX + 1) * 16.0f, (layTwoTilePosY)* 16.0f);
        
        // Define bottom-right corner
        quad++;
        quad->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quad->texCoords = sf::Vector2f((layTwoTilePosX + 1) * 16.0f, (layTwoTilePosY + 1) * 16.0f);
        
        // Define bottom-left corner
        quad++;
        quad->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quad->texCoords = sf::Vector2f(layTwoTilePosX * 16.0f, (layTwoTilePosY + 1) * 16.0f);
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &_tileset;
	target.draw(m_groundVerticies, states);
}
