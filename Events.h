#ifndef Event_hpp
#define Event_hpp

#include "EventBus.h"

class GenericEvent : public Event
{
public:
    GenericEvent();
    ~GenericEvent();
    
private:
    Event::EventType _type;
    virtual Event::EventType getType() const;
};

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
