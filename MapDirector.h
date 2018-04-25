#ifndef MAPDIRECTOR_H
#define MAPDIRECTOR_H

#include <SFML/Graphics.hpp>
#include "MapBuilder.h"
#include "MapBank.h"

// MapDirector provides all meta functionality needed for querying information
// about a map, running algorithms on a map, or running any other processes that
// need access to a map's structure or current state.
// The Director only knows about the currently loaded map--it does not have
// access to any other stored map components in MapBank. The Director can load a
// new map whenever necessary.
class MapDirector {

public:

	// Loads and builds the specified map, allowing MapDirector to begin
	// working on it. If another map is already loaded, this function will
	// fail. You must call unloadMap() before calling loadMap() if a map
	// is already loaded.
	bool loadMap(unsigned int ID);

	// Unloads the currently loaded map, if one exists.
	void unloadMap();

	// Updates the current map.
	void update();

	// Retrieves the current map's transform.
	const sf::Transform& getCurrTransform() const;

	// Retrieves the current map's verticies.
	const std::vector<sf::VertexArray>& getCurrVerticies() const;

	// Retrieves the current map's textures.
	const std::vector<sf::Texture>& getCurrTextures() const;

private:

	// Pointer to currently loaded map.
	// All Maps are stored in MapBank, so this will point to any map stored there.
	Map* _currMap;

	// Contains functionality for loading map data and building maps.
	MapBuilder _mapBuilder;

	// Current map's vertex arrays, ordered by increasing layers.
	// Convenience for passing result into Renderer.
	std::vector<sf::VertexArray> _currVerticies;

	// Current map's textures, order of: tiles, universal sprites, local sprites.
	// Convenience for passing result into Renderer.
	std::vector<sf::Texture> _currTextures;

	// --- SINGLETON IMPLEMENTATION ---
public:

	MapDirector(MapDirector const&) = delete;
	void operator=(MapDirector const&) = delete;

	static MapDirector& get() {
		static MapDirector instance;
		return instance;
	}

private:

	MapDirector();
	~MapDirector();

};

#endif