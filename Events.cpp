#include "Events.h"

FullscreenEvent::FullscreenEvent() {
	_type = EV_FULLSCREEN;
}
FullscreenEvent::~FullscreenEvent() {}

Event::EventType FullscreenEvent::getType() const {
	return _type;
}

RunDownEvent::RunDownEvent() {
	_type = EV_RUNDOWN;
}
RunDownEvent::~RunDownEvent() {}

Event::EventType RunDownEvent::getType() const {
	return _type;
}

RunUpEvent::RunUpEvent() {
	_type = EV_RUNUP;
}
RunUpEvent::~RunUpEvent() {}

Event::EventType RunUpEvent::getType() const {
	return _type;
}

RunLeftEvent::RunLeftEvent() {
	_type = EV_RUNLEFT;
}
RunLeftEvent::~RunLeftEvent() {}

Event::EventType RunLeftEvent::getType() const {
	return _type;
}

RunRightEvent::RunRightEvent() {
	_type = EV_RUNRIGHT;
}
RunRightEvent::~RunRightEvent() {}

Event::EventType RunRightEvent::getType() const {
	return _type;
}

WalkDownEvent::WalkDownEvent() {
	_type = EV_WALKDOWN;
}
WalkDownEvent::~WalkDownEvent() {}

Event::EventType WalkDownEvent::getType() const {
	return _type;
}

WalkUpEvent::WalkUpEvent() {
	_type = EV_WALKUP;
}
WalkUpEvent::~WalkUpEvent() {}

Event::EventType WalkUpEvent::getType() const {
	return _type;
}

WalkLeftEvent::WalkLeftEvent() {
	_type = EV_WALKLEFT;
}
WalkLeftEvent::~WalkLeftEvent() {}

Event::EventType WalkLeftEvent::getType() const {
	return _type;
}

WalkRightEvent::WalkRightEvent() {
	_type = EV_WALKRIGHT;
}
WalkRightEvent::~WalkRightEvent() {}

Event::EventType WalkRightEvent::getType() const {
	return _type;
}

InteractEvent::InteractEvent() {
    _type = EV_INTERACT;
}
InteractEvent::~InteractEvent() {}

Event::EventType InteractEvent::getType() const {
    return _type;
}

RadialSoundEvent::RadialSoundEvent() {
    _type = EV_RADIALSOUND;
}
RadialSoundEvent::~RadialSoundEvent() {}

Event::EventType RadialSoundEvent::getType() const {
    return _type;
}
