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
	RunDownEvent(unsigned int targetID);
	~RunDownEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class RunUpEvent : public Event {
public:
	RunUpEvent(unsigned int targetID);
	~RunUpEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class RunLeftEvent : public Event {
public:
	RunLeftEvent(unsigned int targetID);
	~RunLeftEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class RunRightEvent : public Event {
public:
	RunRightEvent(unsigned int targetID);
	~RunRightEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class WalkDownEvent : public Event {
public:
	WalkDownEvent(unsigned int targetID);
	~WalkDownEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class WalkUpEvent : public Event {
public:
	WalkUpEvent(unsigned int targetID);
	~WalkUpEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class WalkLeftEvent : public Event {
public:
	WalkLeftEvent(unsigned int targetID);
	~WalkLeftEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class WalkRightEvent : public Event {
public:
	WalkRightEvent(unsigned int targetID);
	~WalkRightEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
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

class TurnDownEvent : public Event {
public:
	TurnDownEvent(unsigned int targetID);
	~TurnDownEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class TurnUpEvent : public Event {
public:
	TurnUpEvent(unsigned int targetID);
	~TurnUpEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class TurnLeftEvent : public Event {
public:
	TurnLeftEvent(unsigned int targetID);
	~TurnLeftEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class TurnRightEvent : public Event {
public:
	TurnRightEvent(unsigned int targetID);
	~TurnRightEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class LoadMapEvent : public Event {
public:
	LoadMapEvent(int** movementMap);
	~LoadMapEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;
};

#endif
