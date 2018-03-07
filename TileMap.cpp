//Josh Seelye
#include "TileMap.h"

/********************************
    Tile Functions/Constructors
 ********************************/

TileMap::Tile::Tile() : _tileID(-1), _step(0), _animate(AutoAnimation(0,0,0,0,sf::seconds(.3f)))
{}
TileMap::Tile::Tile(int ID, const sf::Vector2f& postition, const float &volume, char properties, std::string soundFilename) : _tileID(ID), _step(0), _animate(getTileAnimation(ID)), _position(postition), _properties(properties), _soundFilename(soundFilename)
{
    _volume = volume;
    _centerPosition.x = _position.x + 8;
    _centerPosition.y = _position.y + 8;
    if(properties&0x02) _tileSound = new Sound(soundFilename, sf::seconds(0.0f));
    else if(properties&0x04) _tileSound = new Sound(soundFilename, sf::seconds(0.0f));
	else _tileSound = nullptr;
}
TileMap::Tile::~Tile()
{}

//Moves the animation step forward one if the the time exceeds that last and deals with the sound
void TileMap::Tile::update(sf::Time deltaTime, const sf::Vector2f& pposition)
{
    if((_animate.getTotalAnimSteps() > 1) && (256 - sqrt(pow(_centerPosition.x-pposition.x,2)+pow(_centerPosition.y-pposition.y,2)) > 0))
    {
        _animate.update(deltaTime);
        _step = _animate.getCurrAnimStep();
    }
    if(_properties&0x02)
    {
        
    }
    if(_properties&0x04)
    {
        _tileSound->setVolume(_volume - .5*sqrt(pow(_centerPosition.x-pposition.x,2)+pow(_centerPosition.y-pposition.y,2)));
        _tileSound->playSound(deltaTime);
    }
}
void TileMap::Tile::setAnimStep(unsigned int step)
{
    if(step <= _animate.getTotalAnimSteps())
    {
        _animate.setCurrAnimStep(step);
        _step = step;
    }
}
int  TileMap::Tile::getID()        { return _tileID; }
void TileMap::Tile::setID(int ID)  { _tileID = ID;   }
int  TileMap::Tile::getAnimStep()  { return _step;   }
const sf::Vector2f& TileMap::Tile::getPosition()       const
{
    return _position;
}
const sf::Vector2f& TileMap::Tile::getCenterPosition() const
{
    return _centerPosition;
}
const char TileMap::Tile::getProperties() const
{
    return _properties;
}


/********************************
  TileMap Functions/Constructors
 ********************************/

TileMap::TileMap(std::string name) : _name(name)
{
    static int mapCounter = 0;
    _mapIdentifier = mapCounter;
    mapCounter++;
	_groundVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
    _layerTwoVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
    _layerThreeVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
    _layerSixVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
    _canopyVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
}

bool TileMap::build(int* ground, int* layerTwo, int* layerThree, int* layerSix, int* canopy, int width, int height, const float &volume, std::string Music, std::string tilesetFileName)
{
    if(!_tileset.load(tilesetFileName)) return false;
    _width = width;
    _height = height;

	_groundVerticies.resize(_width * _height * 4    );
    _layerTwoVerticies.resize(_width * _height * 4  );
    _layerThreeVerticies.resize(_width * _height * 4);
    _layerSixVerticies.resize(_width * _height * 4  );
    _canopyVerticies.resize(_width * _height * 4    );

    _ground     = new Tile*[_height];
    _layerTwo   = new Tile*[_height];
    _layerThree = new Tile*[_height];
    _layerSix   = new Tile*[_height];
    _canopy     = new Tile*[_height];
    for(int i = 0; i<_height;i++)
    {
        _ground[i]     = new Tile[_width];
        _layerTwo[i]   = new Tile[_width];
        _layerThree[i] = new Tile[_width];
        _layerSix[i]   = new Tile[_width];
        _canopy[i]     = new Tile[_width];
    }
    for(int i = 0; i < _height; i++)
    {
        for(int j = 0; j < _width; j++)
        {
            if(ground[0]!=-2)
            {
                switch(ground[i*_width+j])
                {
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                        _ground[i][j] = Tile(ground[i*_width+j],sf::Vector2f(static_cast<float>(i),static_cast<float>(j)), volume, 0x05, "waves.wav");
                        break;
                    case 0:
                    case 2:
                    case 4:
                    case 6:
                    case 8:
                        _ground[i][j] = Tile(ground[i*_width+j],sf::Vector2f(static_cast<float>(i),static_cast<float>(j)), volume, 0x01);
                        break;
                    default:
                        _ground[i][j] = Tile(ground[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), volume);
                }
            }
            if(layerTwo[0]!=-2)
            {
                _layerTwo[i][j] = Tile(layerTwo[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), volume);
            }
            if(layerThree[0]!=-2)
            {
                _layerThree[i][j] = Tile(layerThree[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), volume);
            }
            if(layerSix[0]!=-2)
            {
                _layerSix[i][j] = Tile(layerSix[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), volume);
            }
            if(canopy[0]!=-2)
            {
                _canopy[i][j] = Tile(canopy[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), volume);
            }
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
        delete[] _layerTwo[i];
        delete[] _layerThree[i];
        delete[] _layerSix[i];
        delete[] _canopy[i];
    }
    delete[] _ground;
    delete[] _layerTwo;
    delete[] _layerThree;
    delete[] _layerSix;
    delete[] _canopy;
}

void TileMap::vertexFill(int y, int x)
{
	// Sets up random tile, Cache ID, y position, and x position
	int groundTileID = _ground[y][x].getID();
    int layerTwoTileID = _layerTwo[y][x].getID();
    int layerThreeTileID = _layerThree[y][x].getID();
    int layerSixTileID = _layerSix[y][x].getID();
    int canopyTileID = _canopy[y][x].getID();
	float i = _ground[y][x].getPosition().x;
	float j = _ground[y][x].getPosition().y;

	// Calculate position of tile graphic in tileset in tile units
	int groundTilePosX = groundTileID % static_cast<int>(_tileset.getWidth() / 16);
    int groundTilePosY = (groundTileID / _tileset.getWidth()) * 16;
	_groundVerticies[(size_t)((i * _width + j) * 4 )];

	// Get a pointer to tile's top-left corner in vertex array
	sf::Vertex* quadGro = &_groundVerticies[(size_t)  ((i * _width + j) * 4 )];
    sf::Vertex* quadTwo = &_layerTwoVerticies[(size_t)((i * _width + j) * 4 )];
    sf::Vertex* quadThree = &_layerThreeVerticies[(size_t)((i * _width + j) * 4 )];
    sf::Vertex* quadSix = &_layerSixVerticies[(size_t)((i * _width + j) * 4 )];
    sf::Vertex* quadCanopy = &_canopyVerticies[(size_t)((i * _width + j) * 4 )];

    if(groundTileID != -1)
    {
        // Define top-left corner
        quadGro->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quadGro->texCoords = sf::Vector2f(groundTilePosX * 16.0f, (groundTilePosY + _ground[y][x].getAnimStep()) * 16.0f);

        // Define top-right corner
        quadGro++;
        quadGro->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadGro->texCoords = sf::Vector2f((groundTilePosX + 1) * 16.0f, (groundTilePosY + _ground[y][x].getAnimStep())* 16.0f);

        // Define bottom-right corner
        quadGro++;
        quadGro->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadGro->texCoords = sf::Vector2f((groundTilePosX + 1) * 16.0f, (groundTilePosY + 1 + _ground[y][x].getAnimStep()) * 16.0f);

        // Define bottom-left corner
        quadGro++;
        quadGro->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadGro->texCoords = sf::Vector2f(groundTilePosX * 16.0f, (groundTilePosY + 1 + _ground[y][x].getAnimStep()) * 16.0f);
        
    }
    if(layerTwoTileID != -1)
    {
        int layTwoTilePosX = layerTwoTileID % static_cast<int>(_tileset.getWidth() / 16);
        int layTwoTilePosY = (layerTwoTileID / _tileset.getWidth()) * 16;

        quadTwo->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quadTwo->texCoords = sf::Vector2f(layTwoTilePosX * 16.0f, (layTwoTilePosY + _layerTwo[y][x].getAnimStep()) * 16.0f);
        
        // Define top-right corner
        quadTwo++;
        quadTwo->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadTwo->texCoords = sf::Vector2f((layTwoTilePosX + 1) * 16.0f, (layTwoTilePosY + _layerTwo[y][x].getAnimStep())* 16.0f);
        
        // Define bottom-right corner
        quadTwo++;
        quadTwo->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadTwo->texCoords = sf::Vector2f((layTwoTilePosX + 1) * 16.0f, (layTwoTilePosY + 1 + _layerTwo[y][x].getAnimStep()) * 16.0f);
        
        // Define bottom-left corner
        quadTwo++;
        quadTwo->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadTwo->texCoords = sf::Vector2f(layTwoTilePosX * 16.0f, (layTwoTilePosY + 1 + _layerTwo[y][x].getAnimStep()) * 16.0f);
    }
    if(layerThreeTileID != -1)
    {
        int layThreeTilePosX = layerThreeTileID % static_cast<int>(_tileset.getWidth() / 16);
        int layThreeTilePosY = (layerThreeTileID / _tileset.getWidth()) * 16;
        
        quadThree->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quadThree->texCoords = sf::Vector2f(layThreeTilePosX * 16.0f, (layThreeTilePosY + _layerThree[y][x].getAnimStep()) * 16.0f);
        
        // Define top-right corner
        quadThree++;
        quadThree->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadThree->texCoords = sf::Vector2f((layThreeTilePosX + 1) * 16.0f, (layThreeTilePosY + _layerThree[y][x].getAnimStep())* 16.0f);
        
        // Define bottom-right corner
        quadThree++;
        quadThree->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadThree->texCoords = sf::Vector2f((layThreeTilePosX + 1) * 16.0f, (layThreeTilePosY + 1 + _layerThree[y][x].getAnimStep()) * 16.0f);
        
        // Define bottom-left corner
        quadThree++;
        quadThree->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadThree->texCoords = sf::Vector2f(layThreeTilePosX * 16.0f, (layThreeTilePosY + 1 + _layerThree[y][x].getAnimStep()) * 16.0f);
    }
    if(layerSixTileID != -1)
    {
        int laySixTilePosX = layerSixTileID % static_cast<int>(_tileset.getWidth() / 16);
        int laySixTilePosY = (layerSixTileID / _tileset.getWidth()) * 16;
        
        quadSix->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quadSix->texCoords = sf::Vector2f(laySixTilePosX * 16.0f, (laySixTilePosY + _layerSix[y][x].getAnimStep()) * 16.0f);
        
        // Define top-right corner
        quadSix++;
        quadSix->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadSix->texCoords = sf::Vector2f((laySixTilePosX + 1) * 16.0f, (laySixTilePosY + _layerSix[y][x].getAnimStep())* 16.0f);
        
        // Define bottom-right corner
        quadSix++;
        quadSix->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadSix->texCoords = sf::Vector2f((laySixTilePosX + 1) * 16.0f, (laySixTilePosY + 1 + _layerSix[y][x].getAnimStep()) * 16.0f);
        
        // Define bottom-left corner
        quadSix++;
        quadSix->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadSix->texCoords = sf::Vector2f(laySixTilePosX * 16.0f, (laySixTilePosY + 1 + _layerSix[y][x].getAnimStep()) * 16.0f);
    }
    if(canopyTileID != -1)
    {
        int canopyTilePosX = canopyTileID % static_cast<int>(_tileset.getWidth() / 16);
        int canopyTilePosY = (canopyTileID / _tileset.getWidth()) * 16;
        
        quadCanopy->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quadCanopy->texCoords = sf::Vector2f(canopyTilePosX * 16.0f, (canopyTilePosY + _canopy[y][x].getAnimStep()) * 16.0f);
        
        // Define top-right corner
        quadCanopy++;
        quadCanopy->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadCanopy->texCoords = sf::Vector2f((canopyTilePosX + 1) * 16.0f, (canopyTilePosY + _canopy[y][x].getAnimStep())* 16.0f);
        
        // Define bottom-right corner
        quadCanopy++;
        quadCanopy->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadCanopy->texCoords = sf::Vector2f((canopyTilePosX + 1) * 16.0f, (canopyTilePosY + 1 + _canopy[y][x].getAnimStep()) * 16.0f);
        
        // Define bottom-left corner
        quadCanopy++;
        quadCanopy->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadCanopy->texCoords = sf::Vector2f(canopyTilePosX * 16.0f, (canopyTilePosY + 1 + _canopy[y][x].getAnimStep()) * 16.0f);
    }
}

void TileMap::updateMap(sf::Time deltaTime, const sf::Vector2f& pposition)
{
    for(int i = 0; i < _height; i++)
    {
        for(int j = 0; j < _width; j++)
        {
            _ground[i][j].update(deltaTime, pposition);
            _layerTwo[i][j].update(deltaTime, pposition);
            _layerTwo[i][j].update(deltaTime, pposition);
            vertexFill(i, j);
        }
    }
}

const sf::VertexArray& TileMap::getGroundVertices()   const
{
    return _groundVerticies;
}
const sf::VertexArray& TileMap::getLayerTwoVertices() const
{
    return _layerTwoVerticies;
}
const sf::VertexArray& TileMap::getLayerThreeVertices() const
{
    return _layerThreeVerticies;
}
const sf::VertexArray& TileMap::getLayerSixVertices() const
{
    return _layerSixVerticies;
}
const sf::VertexArray& TileMap::getCanopyVertices() const
{
    return _canopyVerticies;
}

const sf::Texture& TileMap::getTileSet() const
{
    return _tileset.getTexture();
}

std::string TileMap::getMusic()
{
    return _music;
}

std::string TileMap::getName()
{
    return _name;
}

int TileMap::getMapID()
{
    return _mapIdentifier;
}

/************************
  Tile Animation Handler
 ************************/

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
            return AutoAnimation(0,8,16,16,sf::seconds(.4f));
            break;
        case 13:
            return AutoAnimation(0,5,16,16,sf::seconds(1.0f));
            break;
        //case  :
          //  return AutoAnimation(0,3,16,16,sf::seconds(1.0f));
            //break;
        default:
            return AutoAnimation(0,1,16,16,sf::seconds(1.0f));
            break;
    }
}
