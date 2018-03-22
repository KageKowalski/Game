//josh Seelye
#ifndef EventBus_h
#define EventBus_h

#include <queue>
#include <set>
#include <map>
#include <memory>

class Event
{
public:
    enum EventType
    {
        EV_SOUND
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
    EventBus(){}
    ~EventBus(){}
    
    std::queue<std::unique_ptr<Event>> _eventBus;
    std::map<Event::EventType, std::set<EventListener*>> _routingTable;
    
public:
    EventBus(EventBus const&)        = delete;
    void operator=(EventBus const&)  = delete;
    
    static EventBus& get()
    {
        static EventBus instance;
        return          instance;
    }
};



#endif
