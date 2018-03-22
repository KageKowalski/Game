#ifndef Event_hpp
#define Event_hpp

#include "EventBus.h"

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
