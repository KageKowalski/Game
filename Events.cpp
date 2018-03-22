#include "Events.h"

SoundEvent::SoundEvent()
{
    _type = EV_SOUND;
}
SoundEvent::~SoundEvent(){}

Event::EventType SoundEvent::getType() const
{
    return _type;
}
