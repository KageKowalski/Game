//Josh Seelye
#include "TileMap.h"

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
    
    int countOne = 0;
    int countZero = 0;

    _ground      = new Tile*[_height];
    _layerTwo    = new Tile*[_height];
    _layerThree  = new Tile*[_height];
    _layerSix    = new Tile*[_height];
    _canopy      = new Tile*[_height];
    _movementMap = new int* [_height];
    for(int i = 0; i<_height;i++)
    {
        _ground[i]      = new Tile[_width];
        _layerTwo[i]    = new Tile[_width];
        _layerThree[i]  = new Tile[_width];
        _layerSix[i]    = new Tile[_width];
        _canopy[i]      = new Tile[_width];
        _movementMap[i] = new int [_width];
    }
    for(int i = 0; i < _height; i++)
    {
        for(int j = 0; j < _width; j++)
        {
            if(ground[0]!=-2)
            {
                switch(ground[i*_width+j])
                {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                        _ground[i][j] = Tile(ground[i*_width+j],sf::Vector2f(static_cast<float>(i),static_cast<float>(j)), volume, 0x05, "waves.wav");
                        break;
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                        _ground[i][j] = Tile(ground[i*_width+j],sf::Vector2f(static_cast<float>(i),static_cast<float>(j)), volume, 0x02, "grass_foot.wav");
                        break;
                    default:
                        _ground[i][j] = Tile(ground[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), volume);
                        break;
                }
            }
            if(layerTwo[0]!=-2)
            {
                switch(layerTwo[i*_width+j])
                {
                    case 28:
                        _layerTwo[i][j] = Tile(layerTwo[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), volume, 0x01);
                        break;
                    default:
                        _layerTwo[i][j] = Tile(layerTwo[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), volume);
                }
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
            if((_ground[i][j].getProperties() & 0x01) || (_layerTwo[i][j].getProperties() & 0x01) || (_layerThree[i][j].getProperties() & 0x01) || (_layerSix[i][j].getProperties() & 0x01) || (_canopy[i][j].getProperties() & 0x01))
            {
                _movementMap[i][j] = 1;
                countOne++;
            }
            else
            {
                _movementMap[i][j] = 0;
                countZero++;
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
        // Define top-left corner
        quadGro->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quadGro->texCoords = sf::Vector2f(groundTilePosX * 16.0f, (groundTilePosY + _ground[y][x].getAnimStep()) * 16.0f);
        if(Sun::get().getHour() >= 10  && Sun::get().getHour() <= 35)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 255;
            quadGro->color.g = 255;
            quadGro->color.b = 255;
        }
        else if(Sun::get().getHour() >= 46 && Sun::get().getHour() <= 60)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 155;
            quadGro->color.g = 155;
            quadGro->color.b = 155;
        }
        else if(Sun::get().getHour() == 0 || Sun::get().getHour() == 45)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 165;
            quadGro->color.g = 165;
            quadGro->color.b = 165;
        }
        else if(Sun::get().getHour() == 1 || Sun::get().getHour() == 44)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 175;
            quadGro->color.g = 175;
            quadGro->color.b = 175;
        }
        else if(Sun::get().getHour() == 2 || Sun::get().getHour() == 43)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 185;
            quadGro->color.g = 185;
            quadGro->color.b = 185;
        }
        else if(Sun::get().getHour() == 3 || Sun::get().getHour() == 42)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 195;
            quadGro->color.g = 195;
            quadGro->color.b = 195;
        }
        else if(Sun::get().getHour() == 4 || Sun::get().getHour() == 41)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 205;
            quadGro->color.g = 205;
            quadGro->color.b = 205;
        }
        else if(Sun::get().getHour() == 5 || Sun::get().getHour() == 40)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 215;
            quadGro->color.g = 215;
            quadGro->color.b = 215;
        }
        else if(Sun::get().getHour() == 6 || Sun::get().getHour() == 39)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 225;
            quadGro->color.g = 225;
            quadGro->color.b = 225;
        }
        else if(Sun::get().getHour() == 7 || Sun::get().getHour() == 38)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 235;
            quadGro->color.g = 235;
            quadGro->color.b = 235;
        }
        else if(Sun::get().getHour() == 8 || Sun::get().getHour() == 37)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 245;
            quadGro->color.g = 245;
            quadGro->color.b = 245;
        }
        else if(Sun::get().getHour() == 9 || Sun::get().getHour() == 36)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 255;
            quadGro->color.g = 255;
            quadGro->color.b = 255;
        }

        // Define top-right corner
        quadGro++;
        quadGro->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadGro->texCoords = sf::Vector2f((groundTilePosX + 1) * 16.0f, (groundTilePosY + _ground[y][x].getAnimStep())* 16.0f);
        if(Sun::get().getHour() >= 10  && Sun::get().getHour() <= 35)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 255;
            quadGro->color.g = 255;
            quadGro->color.b = 255;
        }
        else if(Sun::get().getHour() >= 46 && Sun::get().getHour() <= 60)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 155;
            quadGro->color.g = 155;
            quadGro->color.b = 155;
        }
        else if(Sun::get().getHour() == 0 || Sun::get().getHour() == 45)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 165;
            quadGro->color.g = 165;
            quadGro->color.b = 165;
        }
        else if(Sun::get().getHour() == 1 || Sun::get().getHour() == 44)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 175;
            quadGro->color.g = 175;
            quadGro->color.b = 175;
        }
        else if(Sun::get().getHour() == 2 || Sun::get().getHour() == 43)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 185;
            quadGro->color.g = 185;
            quadGro->color.b = 185;
        }
        else if(Sun::get().getHour() == 3 || Sun::get().getHour() == 42)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 195;
            quadGro->color.g = 195;
            quadGro->color.b = 195;
        }
        else if(Sun::get().getHour() == 4 || Sun::get().getHour() == 41)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 205;
            quadGro->color.g = 205;
            quadGro->color.b = 205;
        }
        else if(Sun::get().getHour() == 5 || Sun::get().getHour() == 40)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 215;
            quadGro->color.g = 215;
            quadGro->color.b = 215;
        }
        else if(Sun::get().getHour() == 6 || Sun::get().getHour() == 39)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 225;
            quadGro->color.g = 225;
            quadGro->color.b = 225;
        }
        else if(Sun::get().getHour() == 7 || Sun::get().getHour() == 38)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 235;
            quadGro->color.g = 235;
            quadGro->color.b = 235;
        }
        else if(Sun::get().getHour() == 8 || Sun::get().getHour() == 37)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 245;
            quadGro->color.g = 245;
            quadGro->color.b = 245;
        }
        else if(Sun::get().getHour() == 9 || Sun::get().getHour() == 36)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 255;
            quadGro->color.g = 255;
            quadGro->color.b = 255;
        }

        // Define bottom-right corner
        quadGro++;
        quadGro->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadGro->texCoords = sf::Vector2f((groundTilePosX + 1) * 16.0f, (groundTilePosY + 1 + _ground[y][x].getAnimStep()) * 16.0f);
        if(Sun::get().getHour() >= 10  && Sun::get().getHour() <= 35)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 255;
            quadGro->color.g = 255;
            quadGro->color.b = 255;
        }
        else if(Sun::get().getHour() >= 46 && Sun::get().getHour() <= 60)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 155;
            quadGro->color.g = 155;
            quadGro->color.b = 155;
        }
        else if(Sun::get().getHour() == 0 || Sun::get().getHour() == 45)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 165;
            quadGro->color.g = 165;
            quadGro->color.b = 165;
        }
        else if(Sun::get().getHour() == 1 || Sun::get().getHour() == 44)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 175;
            quadGro->color.g = 175;
            quadGro->color.b = 175;
        }
        else if(Sun::get().getHour() == 2 || Sun::get().getHour() == 43)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 185;
            quadGro->color.g = 185;
            quadGro->color.b = 185;
        }
        else if(Sun::get().getHour() == 3 || Sun::get().getHour() == 42)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 195;
            quadGro->color.g = 195;
            quadGro->color.b = 195;
        }
        else if(Sun::get().getHour() == 4 || Sun::get().getHour() == 41)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 205;
            quadGro->color.g = 205;
            quadGro->color.b = 205;
        }
        else if(Sun::get().getHour() == 5 || Sun::get().getHour() == 40)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 215;
            quadGro->color.g = 215;
            quadGro->color.b = 215;
        }
        else if(Sun::get().getHour() == 6 || Sun::get().getHour() == 39)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 225;
            quadGro->color.g = 225;
            quadGro->color.b = 225;
        }
        else if(Sun::get().getHour() == 7 || Sun::get().getHour() == 38)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 235;
            quadGro->color.g = 235;
            quadGro->color.b = 235;
        }
        else if(Sun::get().getHour() == 8 || Sun::get().getHour() == 37)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 245;
            quadGro->color.g = 245;
            quadGro->color.b = 245;
        }
        else if(Sun::get().getHour() == 9 || Sun::get().getHour() == 36)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 255;
            quadGro->color.g = 255;
            quadGro->color.b = 255;
        }

        // Define bottom-left corner
        quadGro++;
        quadGro->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadGro->texCoords = sf::Vector2f(groundTilePosX * 16.0f, (groundTilePosY + 1 + _ground[y][x].getAnimStep()) * 16.0f);
        if(Sun::get().getHour() >= 10  && Sun::get().getHour() <= 35)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 255;
            quadGro->color.g = 255;
            quadGro->color.b = 255;
        }
        else if(Sun::get().getHour() >= 46 && Sun::get().getHour() <= 60)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 155;
            quadGro->color.g = 155;
            quadGro->color.b = 155;
        }
        else if(Sun::get().getHour() == 0 || Sun::get().getHour() == 45)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 165;
            quadGro->color.g = 165;
            quadGro->color.b = 165;
        }
        else if(Sun::get().getHour() == 1 || Sun::get().getHour() == 44)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 175;
            quadGro->color.g = 175;
            quadGro->color.b = 175;
        }
        else if(Sun::get().getHour() == 2 || Sun::get().getHour() == 43)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 185;
            quadGro->color.g = 185;
            quadGro->color.b = 185;
        }
        else if(Sun::get().getHour() == 3 || Sun::get().getHour() == 42)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 195;
            quadGro->color.g = 195;
            quadGro->color.b = 195;
        }
        else if(Sun::get().getHour() == 4 || Sun::get().getHour() == 41)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 205;
            quadGro->color.g = 205;
            quadGro->color.b = 205;
        }
        else if(Sun::get().getHour() == 5 || Sun::get().getHour() == 40)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 215;
            quadGro->color.g = 215;
            quadGro->color.b = 215;
        }
        else if(Sun::get().getHour() == 6 || Sun::get().getHour() == 39)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 225;
            quadGro->color.g = 225;
            quadGro->color.b = 225;
        }
        else if(Sun::get().getHour() == 7 || Sun::get().getHour() == 38)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 235;
            quadGro->color.g = 235;
            quadGro->color.b = 235;
        }
        else if(Sun::get().getHour() == 8 || Sun::get().getHour() == 37)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 245;
            quadGro->color.g = 245;
            quadGro->color.b = 245;
        }
        else if(Sun::get().getHour() == 9 || Sun::get().getHour() == 36)
        {
            quadGro->color.a = 255;
            quadGro->color.r = 255;
            quadGro->color.g = 255;
            quadGro->color.b = 255;
        }
    }
    if(layerTwoTileID != -1)
    {
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
            _layerThree[i][j].update(deltaTime, pposition);
            _layerSix[i][j].update(deltaTime, pposition);
            _canopy[i][j].update(deltaTime, pposition);
            vertexFill(i, j);
        }
    }
}

int** TileMap::getMovementMap() const
{
    return _movementMap;
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


const Tile* const * const TileMap::getGroundTiles()     const
{
    return _ground;
}
const Tile* const * const TileMap::getLayerTwoTiles()   const
{
    return _layerTwo;
}
const Tile* const * const TileMap::getLayerThreeTiles() const
{
    return _layerThree;
}
const Tile* const * const TileMap::getLayerSixTiles()   const
{
    return _layerSix;
}
const Tile* const * const TileMap::getCanopyTiles()     const
{
    return _canopy;
}

int TileMap::getWidth()  const
{
    return _width;
}
int TileMap::getHeight() const
{
    return _height;
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


