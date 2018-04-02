#ifndef Event_hpp
#define Event_hpp

#include "EventBus.h"

class FullscreenEvent : public Event {
public:
	FullscreenEvent();
	~FullscreenEvent();

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;
};

class RunDownEvent : public Event {
public:
	RunDownEvent();
	~RunDownEvent();

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;
};

class RunUpEvent : public Event {
public:
	RunUpEvent();
	~RunUpEvent();

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;
};

class RunLeftEvent : public Event {
public:
	RunLeftEvent();
	~RunLeftEvent();

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;
};

class RunRightEvent : public Event {
public:
	RunRightEvent();
	~RunRightEvent();

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;
};

class WalkDownEvent : public Event {
public:
	WalkDownEvent();
	~WalkDownEvent();

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;
};

class WalkUpEvent : public Event {
public:
	WalkUpEvent();
	~WalkUpEvent();

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;
};

class WalkLeftEvent : public Event {
public:
	WalkLeftEvent();
	~WalkLeftEvent();

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;
};

class WalkRightEvent : public Event {
public:
	WalkRightEvent();
	~WalkRightEvent();

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;
};

class InteractEvent : public Event {
public:
    InteractEvent();
    ~InteractEvent();
private:
    Event::EventType _type;
    virtual Event::EventType getType() const;
};

class InteractableConnectorEvent : public Event {
public:
    InteractableConnectorEvent(std::pair<int, int> workingTile);
    ~InteractableConnectorEvent();
    
    const std::pair<int, int>& getWorkingTile() const;
private:
    //first is the tile id. second is map key
    std::pair<int, int> _workingTile;
    Event::EventType _type;
    virtual Event::EventType getType() const;
};

class RadialSoundEvent : public Event {
public:
    RadialSoundEvent();
    ~RadialSoundEvent();
    
private:
    Event::EventType _type;
    virtual Event::EventType getType() const;
};

#endif
