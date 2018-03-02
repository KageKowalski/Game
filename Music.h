#ifndef Music_hpp
#define Music_hpp

#include <SFML/Audio.hpp>

class Music
{
private:
    sf::Music _background;
    std::string _filename;
    
public:
    Music(std::string filename);
    sf::Music& getMusic();
    void  setMusic(std::string filename);
    void  startMusic();
    void  stopMusic();
    void  setPitch(float j);
    void  setVolume(float volume);
    float getVolume();
    void  incrementVolume();
    void  decrementVolume();
};

#endif
