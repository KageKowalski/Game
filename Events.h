#ifndef Event_hpp
#define Event_hpp

#include "EventBus.h"

class CreateThreadEvent : public Event
{
public:
    CreateThreadEvent();
    ~CreateThreadEvent();
    
private:
    Event::EventType _type;
    virtual Event::EventType getType() const;
};

class SoundEvent : public Event
{
public:
    SoundEvent();
    ~SoundEvent();
    
private:
    Event::EventType _type;
    virtual Event::EventType getType() const;
    
};

#endif
