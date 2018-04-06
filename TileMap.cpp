//Josh Seelye
#include "TileMap.h"

/********************************
  TileMap Functions/Constructors
 ********************************/

TileMap::TileMap(std::string name) : _name(name)
{
    EventBus::get().registerListener(Event::EV_INTERACTABLECONNECTOR, this);
    static int mapCounter = 0;
    _mapIdentifier = mapCounter;
    mapCounter++;
	_groundVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
    _layerTwoVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
    _layerThreeVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
    _layerSixVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
    _canopyVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
}

bool TileMap::build(int* ground, int* layerTwo, int* layerThree, int* layerSix, int* canopy, int width, int height, std::string Music, std::string tilesetFileName)
{
    if(!_tileset.load(tilesetFileName)) return false;
    _width = width;
    _height = height;

	_groundVerticies.resize(_width * _height * 4    );
    _layerTwoVerticies.resize(_width * _height * 4  );
    _layerThreeVerticies.resize(_width * _height * 4);
    _layerSixVerticies.resize(_width * _height * 4  );
    _canopyVerticies.resize(_width * _height * 4    );

	int tileCounter = 0;
    for(int i = 0; i < _height; i++)
    {
        for(int j = 0; j < _width; j++)
        {
            LayeredTile* h = new LayeredTile;
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
                        h->ground = new Tile(ground[i*_width+j],sf::Vector2f(static_cast<float>(i),static_cast<float>(j)), tileCounter, 0x05, "waves.wav");
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
                        h->ground = new Tile(ground[i*_width+j],sf::Vector2f(static_cast<float>(i),static_cast<float>(j)), tileCounter, 0x02, "grass_foot.wav");
                        break;
                    default:
                        h->ground = new Tile(ground[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), tileCounter);
                        break;
                }
            }
            else
            {
                h->ground = new Tile();
            }
            if(layerTwo[0]!=-2)
            {
                switch(layerTwo[i*_width+j])
                {
                    case 28:
                        h->layerTwo = new Tile(layerTwo[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), tileCounter, 0x01);
                        break;
                    case 92:
                        h->layerTwo = new Tile(layerTwo[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), tileCounter, 0x09);
                        break;
                    default:
                        h->layerTwo = new Tile(layerTwo[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), tileCounter);
                }
            }
            else
            {
                h->layerTwo = new Tile();
            }
            if(layerThree[0]!=-2)
            {
                h->layerThree = new Tile(layerThree[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), tileCounter);
            }
            else
            {
                h->layerThree = new Tile();
            }
            if(layerSix[0]!=-2)
            {
                h->layerSix = new Tile(layerSix[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), tileCounter);
            }
            else
            {
                h->layerSix = new Tile();
            }
            if(canopy[0]!=-2)
            {
                switch(canopy[i*_width+j])
                {
                    case 52:
                    case 53:
                    case 54:
                        h->canopy = new Tile(canopy[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), tileCounter, 0x10);
                        break;
                    default:
                        h->canopy = new Tile(canopy[i*_width+j], sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), tileCounter);
                }
            }
            else
            {
                h->canopy = new Tile();
            }
            _map.insert(std::pair<int, LayeredTile*>(tileCounter, h));
			vertexFill(_map.find(tileCounter));
            tileCounter++;
        }
    }

    return true;
}

TileMap::~TileMap()
{
    EventBus::get().removeListener(Event::EV_INTERACTABLECONNECTOR, this);
    for(auto it = _map.begin(); it != _map.end(); it++)
    {
        delete it->second->ground;
        delete it->second->layerTwo;
        delete it->second->layerThree;
        delete it->second->layerSix;
        delete it->second->canopy;
        _map.erase(it);
    }
}

void TileMap::vertexFill(std::map<int, LayeredTile*>::iterator it)
{
    // Sets up random tile, Cache ID, y position, and x position
    int groundTileID = it->second->ground->getID();
    int layerTwoTileID = it->second->layerTwo->getID();
    int layerThreeTileID = it->second->layerThree->getID();
    int layerSixTileID = it->second->layerSix->getID();
    int canopyTileID = it->second->canopy->getID();
    float i = it->second->ground->getPosition().x;
    float j = it->second->ground->getPosition().y;

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
        quadGro->texCoords = sf::Vector2f(groundTilePosX * 16.0f, (groundTilePosY + it->second->ground->getAnimStep()) * 16.0f);

        // Define top-right corner
        quadGro++;
        quadGro->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadGro->texCoords = sf::Vector2f((groundTilePosX + 1) * 16.0f, (groundTilePosY + it->second->ground->getAnimStep())* 16.0f);

        // Define bottom-right corner
        quadGro++;
        quadGro->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadGro->texCoords = sf::Vector2f((groundTilePosX + 1) * 16.0f, (groundTilePosY + 1 + it->second->ground->getAnimStep()) * 16.0f);

        // Define bottom-left corner
        quadGro++;
        quadGro->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadGro->texCoords = sf::Vector2f(groundTilePosX * 16.0f, (groundTilePosY + 1 + it->second->ground->getAnimStep()) * 16.0f);
    }
    if(layerTwoTileID != -1)
    {
        quadTwo->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quadTwo->texCoords = sf::Vector2f(layTwoTilePosX * 16.0f, (layTwoTilePosY + it->second->layerTwo->getAnimStep()) * 16.0f);

        // Define top-right corner
        quadTwo++;
        quadTwo->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadTwo->texCoords = sf::Vector2f((layTwoTilePosX + 1) * 16.0f, (layTwoTilePosY + it->second->layerTwo->getAnimStep())* 16.0f);

        // Define bottom-right corner
        quadTwo++;
        quadTwo->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadTwo->texCoords = sf::Vector2f((layTwoTilePosX + 1) * 16.0f, (layTwoTilePosY + 1 + it->second->layerTwo->getAnimStep()) * 16.0f);

        // Define bottom-left corner
        quadTwo++;
        quadTwo->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadTwo->texCoords = sf::Vector2f(layTwoTilePosX * 16.0f, (layTwoTilePosY + 1 + it->second->layerTwo->getAnimStep()) * 16.0f);
    }
    if(layerThreeTileID != -1)
    {
        quadThree->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quadThree->texCoords = sf::Vector2f(layThreeTilePosX * 16.0f, (layThreeTilePosY + it->second->layerThree->getAnimStep()) * 16.0f);

        // Define top-right corner
        quadThree++;
        quadThree->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadThree->texCoords = sf::Vector2f((layThreeTilePosX + 1) * 16.0f, (layThreeTilePosY + it->second->layerThree->getAnimStep())* 16.0f);

        // Define bottom-right corner
        quadThree++;
        quadThree->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadThree->texCoords = sf::Vector2f((layThreeTilePosX + 1) * 16.0f, (layThreeTilePosY + 1 + it->second->layerThree->getAnimStep()) * 16.0f);

        // Define bottom-left corner
        quadThree++;
        quadThree->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadThree->texCoords = sf::Vector2f(layThreeTilePosX * 16.0f, (layThreeTilePosY + 1 + it->second->layerThree->getAnimStep()) * 16.0f);
    }
    if(layerSixTileID != -1)
    {
        quadSix->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quadSix->texCoords = sf::Vector2f(laySixTilePosX * 16.0f, (laySixTilePosY + it->second->layerSix->getAnimStep()) * 16.0f);

        // Define top-right corner
        quadSix++;
        quadSix->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadSix->texCoords = sf::Vector2f((laySixTilePosX + 1) * 16.0f, (laySixTilePosY + it->second->layerSix->getAnimStep())* 16.0f);

        // Define bottom-right corner
        quadSix++;
        quadSix->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadSix->texCoords = sf::Vector2f((laySixTilePosX + 1) * 16.0f, (laySixTilePosY + 1 + it->second->layerSix->getAnimStep()) * 16.0f);

        // Define bottom-left corner
        quadSix++;
        quadSix->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadSix->texCoords = sf::Vector2f(laySixTilePosX * 16.0f, (laySixTilePosY + 1 + it->second->layerSix->getAnimStep()) * 16.0f);
    }
    if(canopyTileID != -1)
    {
        quadCanopy->position = sf::Vector2f(j * 16.0f, i * 16.0f);
        quadCanopy->texCoords = sf::Vector2f(canopyTilePosX * 16.0f, (canopyTilePosY + it->second->canopy->getAnimStep()) * 16.0f);

        // Define top-right corner
        quadCanopy++;
        quadCanopy->position = sf::Vector2f((j + 1) * 16.0f, i * 16.0f);
        quadCanopy->texCoords = sf::Vector2f((canopyTilePosX + 1) * 16.0f, (canopyTilePosY + it->second->canopy->getAnimStep())* 16.0f);

        // Define bottom-right corner
        quadCanopy++;
        quadCanopy->position = sf::Vector2f((j + 1) * 16.0f, (i + 1) * 16.0f);
        quadCanopy->texCoords = sf::Vector2f((canopyTilePosX + 1) * 16.0f, (canopyTilePosY + 1 + it->second->canopy->getAnimStep()) * 16.0f);

        // Define bottom-left corner
        quadCanopy++;
        quadCanopy->position = sf::Vector2f(j * 16.0f, (i + 1) * 16.0f);
        quadCanopy->texCoords = sf::Vector2f(canopyTilePosX * 16.0f, (canopyTilePosY + 1 + it->second->canopy->getAnimStep()) * 16.0f);
    }
}

void TileMap::updateMap()
{
    for(std::map<int, LayeredTile*>::iterator it = _map.begin(); it != _map.end(); it++)
    {
        it->second->ground->update();
        it->second->layerTwo->update();
        it->second->layerThree->update();
        it->second->layerSix->update();
        it->second->canopy->update();
        vertexFill(it);
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

void TileMap::handleEvent(Event* const e)
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


