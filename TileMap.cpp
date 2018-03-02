//Josh Seelye
#include "TileMap.h"

/********************************
    Tile Functions/Constructors
 ********************************/

TileMap::Tile::Tile() : tileID(-1), step(0), animate(AutoAnimation(0,0,0,0,sf::seconds(.3f)))
{}
TileMap::Tile::Tile(int ID, const sf::Vector2f& postition) : tileID(ID), step(0), animate(getTileAnimation(ID))
{
	setPosition(postition);
}
//Moves the animation step forward one if the the time exceeds that last 
void TileMap::Tile::updateAnimStep(sf::Time deltaTime)
{
    //arbitrary value until i consult Klayton
    animate.update(deltaTime);
    step = animate.getCurrAnimStep();
}

int  TileMap::Tile::getID()         { return tileID; }
void TileMap::Tile::setID(int ID)   { tileID = ID;   }
int  TileMap::Tile::getAnimStep()       { return step;   }

/********************************
  TileMap Functions/Constructors
 ********************************/

TileMap::TileMap(const sf::Vector2f& scale, std::string music) : _music(music)
{
	_groundVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
	setScale(scale);
}

bool TileMap::build(int* ground, int* layerOne, int* layerTwo, int width, int height, std::string tilesetFileName)
{
    if(!_tileset.load(tilesetFileName)) return false;
    _width = width;
    _height = height;

	_groundVerticies.resize(_width * _height * 4 * 3);

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

std::string TileMap::getMusic()
{
    return _music;
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
	int groundTilePosX = groundTileID % static_cast<int>(_tileset.getWidth() / 16);
    int groundTilePosY = (groundTileID / _tileset.getWidth()) * 16;
	_groundVerticies[(size_t)((i * _width + j) * 4 * 3)];

	// Get a pointer to tile's top-left corner in vertex array
	sf::Vertex* quad = &_groundVerticies[(size_t)((i * _width + j) * 4 * 3)];

    if(groundTileID != -1)
    {
        // Define top-left corner
        quad->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quad->texCoords = sf::Vector2f(groundTilePosX * 16.0f, (groundTilePosY + _ground[y][x].getAnimStep()) * 16.0f);

        // Define top-right corner
        quad++;
        quad->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quad->texCoords = sf::Vector2f((groundTilePosX + 1) * 16.0f, (groundTilePosY + _ground[y][x].getAnimStep())* 16.0f);

        // Define bottom-right corner
        quad++;
        quad->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quad->texCoords = sf::Vector2f((groundTilePosX + 1) * 16.0f, (groundTilePosY + 1 + _ground[y][x].getAnimStep()) * 16.0f);

        // Define bottom-left corner
        quad++;
        quad->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quad->texCoords = sf::Vector2f(groundTilePosX * 16.0f, (groundTilePosY + 1 + _ground[y][x].getAnimStep()) * 16.0f);
        
        quad++;
    }
    if(layerOneTileID != -1)
    {
        int layOneTilePosX = layerOneTileID % static_cast<int>(_tileset.getWidth() / 16);
        int layOneTilePosY = (layerOneTileID / _tileset.getWidth()) * 16;

        quad->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quad->texCoords = sf::Vector2f(layOneTilePosX * 16.0f, (layOneTilePosY + _layerOne[y][x].getAnimStep()) * 16.0f);
        
        // Define top-right corner
        quad++;
        quad->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quad->texCoords = sf::Vector2f((layOneTilePosX + 1) * 16.0f, (layOneTilePosY + _layerOne[y][x].getAnimStep())* 16.0f);
        
        // Define bottom-right corner
        quad++;
        quad->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quad->texCoords = sf::Vector2f((layOneTilePosX + 1) * 16.0f, (layOneTilePosY + 1 + _layerOne[y][x].getAnimStep()) * 16.0f);
        
        // Define bottom-left corner
        quad++;
        quad->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quad->texCoords = sf::Vector2f(layOneTilePosX * 16.0f, (layOneTilePosY + 1 + _layerOne[y][x].getAnimStep()) * 16.0f);
        
        quad++;
    }
    if(layerTwoTileID != -1)
    {
        int layTwoTilePosX = layerTwoTileID % static_cast<int>(_tileset.getWidth() / 16);
        int layTwoTilePosY = (layerTwoTileID / _tileset.getWidth()) * 16;
        
        quad->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quad->texCoords = sf::Vector2f(layTwoTilePosX * 16.0f, (layTwoTilePosY + _layerTwo[y][x].getAnimStep()) * 16.0f);
        
        // Define top-right corner
        quad++;
        quad->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quad->texCoords = sf::Vector2f((layTwoTilePosX + 1) * 16.0f, (layTwoTilePosY + _layerTwo[y][x].getAnimStep())* 16.0f);
        
        // Define bottom-right corner
        quad++;
        quad->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quad->texCoords = sf::Vector2f((layTwoTilePosX + 1) * 16.0f, (layTwoTilePosY + 1 + _layerTwo[y][x].getAnimStep()) * 16.0f);
        
        // Define bottom-left corner
        quad++;
        quad->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quad->texCoords = sf::Vector2f(layTwoTilePosX * 16.0f, (layTwoTilePosY + 1 + _layerTwo[y][x].getAnimStep()) * 16.0f);
    }
}

void TileMap::updateMap(sf::Time deltaTime)
{
    for(int i = 0; i < _height; i++)
    {
        for(int j = 0; j < _width; j++)
        {
            _ground[i][j].updateAnimStep(deltaTime);
            _layerOne[i][j].updateAnimStep(deltaTime);
            _layerTwo[i][j].updateAnimStep(deltaTime);
            vertexFill(i, j);
        }
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &_tileset.getTexture();
	target.draw(_groundVerticies, states);
}

AutoAnimation TileMap::Tile::getTileAnimation(int ID)
{
    switch(ID)
    {
        case  0:
        case  1:
        case  2:
        case  3:
        case  4:
        case  5:
        case  6:
        case  7:
        case  8:
            return AutoAnimation(0,8,16,16,sf::seconds(.2f));
            break;
        //case  :
          //  return AutoAnimation(0,3,16,16,sf::seconds(1.0f));
            //break;
        default:
            return AutoAnimation(0,1,16,16,sf::seconds(1.0f));
            break;
    }
}
