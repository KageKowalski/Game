#ifndef Event_hpp
#define Event_hpp

#include "EventBus.h"
#include "Direction.h"

class FullscreenEvent : public Event {
public:
    FullscreenEvent();
    virtual ~FullscreenEvent();
    
private:
    Event::EventType _type;
    virtual Event::EventType getType() const;
};

class RunEvent : public Event {
public:
    RunEvent(unsigned int targetID, Direction direction);
    virtual ~RunEvent();
    
    unsigned int getTargetID() const;
	Direction getDirection() const;
    
private:
    Event::EventType _type;
    virtual Event::EventType getType() const;
    
    unsigned int _targetID;
	Direction _direction;
};

class WalkEvent : public Event {
public:
    WalkEvent(unsigned int targetID, Direction direction);
    virtual ~WalkEvent();
    
    unsigned int getTargetID() const;
	Direction getDirection() const;
    
private:
    Event::EventType _type;
    virtual Event::EventType getType() const;
    
    unsigned int _targetID;
	Direction _direction;
};

class InteractEvent : public Event {
public:
    InteractEvent();
    virtual ~InteractEvent();
private:
    Event::EventType _type;
    virtual Event::EventType getType() const;
};

class InteractableConnectorEvent : public Event {
public:
    InteractableConnectorEvent(std::pair<int, sf::Vector2f> workingTile);
    virtual ~InteractableConnectorEvent();
    
    const std::pair<int, sf::Vector2f>& getWorkingTile() const;
private:
    //first is the tile id. second is map key
    std::pair<int, sf::Vector2f> _workingTile;
    Event::EventType _type;
    virtual Event::EventType getType() const;
};

class RadialSoundEvent : public Event {
public:
    RadialSoundEvent();
    virtual ~RadialSoundEvent();
    
private:
    Event::EventType _type;
    virtual Event::EventType getType() const;
};

class TurnEvent : public Event {
public:
    TurnEvent(unsigned int targetID, Direction direction);
    virtual ~TurnEvent();
    
    unsigned int getTargetID() const;
	Direction getDirection() const;
    
private:
    Event::EventType _type;
    virtual Event::EventType getType() const;
    
    unsigned int _targetID;
	Direction _direction;
};

class LoadMapEvent : public Event {
public:
    LoadMapEvent();
    virtual ~LoadMapEvent();
    
    unsigned int getTargetID() const;
    
private:
    Event::EventType _type;
    virtual Event::EventType getType() const;
};

class FullLoadingEvent : public Event {
public:
	FullLoadingEvent();
	virtual ~FullLoadingEvent();

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;
};

class CollisionEvent : public Event {
public:
    CollisionEvent();
    virtual ~CollisionEvent();
    
private:
    Event::EventType _type;
    virtual Event::EventType getType() const;
};

#endif
