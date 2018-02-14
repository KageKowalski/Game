#include "TileMap.h"

/********************************
    Tile Functions/Constructors
 ********************************/

TileMap::Tile::Tile() : tileID(-1) {}
TileMap::Tile::Tile(int ID, const sf::Vector2f& postition) : tileID(ID) {
	setPosition(postition);
}

int TileMap::Tile::getID()       { return tileID; }
void TileMap::Tile::setID(int ID){ tileID = ID;   }


/********************************
  TileMap Functions/Constructors
 ********************************/

TileMap::TileMap(const sf::Vector2f& scale)
{
	m_Verticies.setPrimitiveType(sf::PrimitiveType::Quads);
	setScale(scale);
}

bool TileMap::build(int* intMap, int width, int height, std::string tilesetFileName)
{
    if(!_tileset.loadFromFile(tilesetFileName)) return false;
    _width = width;
    _height = height;
    _map = new Tile*[_height];
    for(int i = 0; i<_height;i++) _map[i] = new Tile[_width];
    
    for(int i = 0; i < _height; i++)
    {
        for(int j = 0; j < _width; j++)
        {
            _map[i][j] = Tile(intMap[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)));

			vertexFill(i, j);
        }
    }
    return true;
}

TileMap::~TileMap()
{
    for(int i = 0; i < _height; i++)
    {
        delete[] _map[i];
    }
    delete[] _map;
}

void TileMap::vertexFill(int y, int x) {
	// Cache ID, y position, and x position
	int tileID = _map[y][x].getID();
	float i = _map[y][x].getPosition().x;
	float j = _map[y][x].getPosition().y;

	// Calculate position of tile graphic in tileset in tile units
	int tilePosX = tileID % (int)(_tileset.getSize().x / 16);
	int tilePosY = tileID % (int)(_tileset.getSize().y / 16);
	m_Verticies[(size_t)((i * _width + j) * 4)];

	// Get a pointer to tile's first top-left corner in vertex array
	sf::Vertex* quad = &m_Verticies[(size_t)((i * _width + j) * 4)];

	// Define top-left corner
	quad->position = sf::Vector2f(j * 16.0f, i * 16.0f);
	quad->texCoords = sf::Vector2f(tilePosX * 16.0f, tilePosY * 16.0f);

	// Define top-right corner
	quad++;
	quad->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
	quad->texCoords = sf::Vector2f((tilePosX + 1) * 16.0f, tilePosY * 16.0f);

	// Define bottom-right corner
	quad++;
	quad->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
	quad->texCoords = sf::Vector2f((tilePosX + 1) * 16.0f, (tilePosY + 1) * 16.0f);

	// Define bottom-left corner
	quad++;
	quad->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
	quad->texCoords = sf::Vector2f(tilePosX * 16.0f, (tilePosY + 1) * 16.0f);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &_tileset;
	target.draw(m_Verticies, states);
}
