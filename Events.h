#ifndef Event_hpp
#define Event_hpp

#include "EventBus.h"

class FullscreenEvent : public Event {
public:
	FullscreenEvent();
	virtual ~FullscreenEvent();

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;
};

class RunDownEvent : public Event {
public:
	RunDownEvent(unsigned int targetID);
	virtual ~RunDownEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class RunUpEvent : public Event {
public:
	RunUpEvent(unsigned int targetID);
	virtual ~RunUpEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class RunLeftEvent : public Event {
public:
	RunLeftEvent(unsigned int targetID);
	virtual ~RunLeftEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class RunRightEvent : public Event {
public:
	RunRightEvent(unsigned int targetID);
	virtual ~RunRightEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class WalkDownEvent : public Event {
public:
	WalkDownEvent(unsigned int targetID);
	virtual ~WalkDownEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class WalkUpEvent : public Event {
public:
	WalkUpEvent(unsigned int targetID);
	virtual ~WalkUpEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class WalkLeftEvent : public Event {
public:
	WalkLeftEvent(unsigned int targetID);
	virtual ~WalkLeftEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class WalkRightEvent : public Event {
public:
	WalkRightEvent(unsigned int targetID);
	virtual ~WalkRightEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
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
    InteractableConnectorEvent(std::pair<int, int> workingTile);
	virtual ~InteractableConnectorEvent();
    
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
	virtual ~RadialSoundEvent();

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;
};

class TurnDownEvent : public Event {
public:
	TurnDownEvent(unsigned int targetID);
	virtual ~TurnDownEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class TurnUpEvent : public Event {
public:
	TurnUpEvent(unsigned int targetID);
	virtual ~TurnUpEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class TurnLeftEvent : public Event {
public:
	TurnLeftEvent(unsigned int targetID);
	virtual ~TurnLeftEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class TurnRightEvent : public Event {
public:
	TurnRightEvent(unsigned int targetID);
	virtual ~TurnRightEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;

	unsigned int _targetID;
};

class LoadMapEvent : public Event {
public:
	LoadMapEvent(int** movementMap);
	virtual ~LoadMapEvent();

	unsigned int getTargetID() const;

private:
	Event::EventType _type;
	virtual Event::EventType getType() const;
};

#endif
