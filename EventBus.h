//josh Seelye
#ifndef EventBus_h
#define EventBus_h

#include <queue>
#include <set>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

class Event
{
public:
	enum EventType
	{
		EV_FULLSCREEN,
		EV_RUN,
		EV_WALK,
		EV_TURN,
		EV_INTERACT,
		EV_INTERACTABLECONNECTOR,
		EV_RADIALSOUND,
		EV_LOADMAP,
		EV_FULLLOADING,
        EV_COLLISION
	};
	virtual ~Event() {};
	virtual EventType getType() const = 0;

};

class EventListener
{
public:
	virtual void handleEvent(Event* const e) = 0;
};

class EventBus
{
public:
	void update();
	void postEvent(std::unique_ptr<Event> &e);
	void registerListener(Event::EventType t, EventListener* l);
	void removeListener(Event::EventType t, EventListener* l);

private:
	EventBus() {}
	~EventBus() {}

	std::queue<std::unique_ptr<Event>> _eventBus;
	std::map<Event::EventType, std::set<EventListener*>> _routingTable;

public:
	EventBus(EventBus const&) = delete;
	void operator=(EventBus const&) = delete;

	static EventBus& get()
	{
		static EventBus instance;
		return          instance;
	}
};



#endif
