//Josh Seelye
#include "EventBus.h"

void EventBus::postEvent(std::unique_ptr<Event> &e)
{
    _eventBus.push(std::unique_ptr<Event>(std::move(e)));
}
void EventBus::registerListener(Event::EventType t, EventListener* l)
{
    _routingTable[t].insert(l);
}
void EventBus::removeListener(Event::EventType t, EventListener* l)
{
    auto keyIterator = _routingTable.find(t);
    if(keyIterator != _routingTable.end())
    {
        _routingTable[t].erase(l);
    }
}
void EventBus::update()
{
    while(!_eventBus.empty())
    {
        std::unique_ptr<Event> e_local(std::move(_eventBus.front()));
        _eventBus.pop();
        
        Event::EventType t = e_local->getType();
        auto it = _routingTable.find(t);
        if(it != _routingTable.end())
        {
            for(auto l : ((*it).second))
            {
                l->handleEvent(e_local.get());
            }
        }
    }
}


