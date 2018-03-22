#include "Events.h"
CreateThreadEvent::CreateThreadEvent()
{
    _type = EV_CREATETHREADS;
}
CreateThreadEvent::~CreateThreadEvent(){}

Event::EventType CreateThreadEvent::getType() const
{
    return _type;
}

SoundEvent::SoundEvent()
{
    _type = EV_SOUND;
}
SoundEvent::~SoundEvent(){}

Event::EventType SoundEvent::getType() const
{
    return _type;
}
