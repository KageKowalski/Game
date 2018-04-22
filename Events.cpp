#include "Events.h"

FullscreenEvent::FullscreenEvent() {
	_type = EV_FULLSCREEN;
}
FullscreenEvent::~FullscreenEvent() {}

Event::EventType FullscreenEvent::getType() const {
	return _type;
}

RunEvent::RunEvent(unsigned int targetID, Direction direction) {
	_type = EV_RUN;
	_targetID = targetID;
	_direction = direction;
}
RunEvent::~RunEvent() {}

unsigned int RunEvent::getTargetID() const {
	return _targetID;
}

Direction RunEvent::getDirection() const {
	return _direction;
}

Event::EventType RunEvent::getType() const {
	return _type;
}

WalkEvent::WalkEvent(unsigned int targetID, Direction direction) {
	_targetID = targetID;
	_type = EV_WALK;
	_direction = direction;
}
WalkEvent::~WalkEvent() {}

unsigned int WalkEvent::getTargetID() const {
	return _targetID;
}

Direction WalkEvent::getDirection() const {
	return _direction;
}

Event::EventType WalkEvent::getType() const {
	return _type;
}

InteractEvent::InteractEvent() {
    _type = EV_INTERACT;
}
InteractEvent::~InteractEvent() {}

Event::EventType InteractEvent::getType() const {
    return _type;
}

InteractableConnectorEvent::InteractableConnectorEvent(std::pair<int, sf::Vector2f> workingTile) : _workingTile(workingTile)
{
    _type = EV_INTERACTABLECONNECTOR;
}
InteractableConnectorEvent::~InteractableConnectorEvent() {}

const std::pair<int, sf::Vector2f>& InteractableConnectorEvent::getWorkingTile() const
{
    return _workingTile;
}

Event::EventType InteractableConnectorEvent::getType() const {
    return _type;
}

RadialSoundEvent::RadialSoundEvent() {
    _type = EV_RADIALSOUND;
}
RadialSoundEvent::~RadialSoundEvent() {}

Event::EventType RadialSoundEvent::getType() const {
    return _type;
}

TurnEvent::TurnEvent(unsigned int targetID, Direction direction) {
	_type = EV_TURN;
	_targetID = targetID;
	_direction = direction;
}
TurnEvent::~TurnEvent() {}

unsigned int TurnEvent::getTargetID() const {
	return _targetID;
}

Event::EventType TurnEvent::getType() const {
	return _type;
}

Direction TurnEvent::getDirection() const {
	return _direction;
}

LoadMapEvent::LoadMapEvent() {
	_type = EV_LOADMAP;
}
LoadMapEvent::~LoadMapEvent() {}

Event::EventType LoadMapEvent::getType() const {
	return _type;
}

FullLoadingEvent::FullLoadingEvent() {
	_type = EV_FULLLOADING;
}
FullLoadingEvent::~FullLoadingEvent() {}

Event::EventType FullLoadingEvent::getType() const {
	return _type;
}

CollisionEvent::CollisionEvent()
{
    _type = EV_COLLISION;
}
CollisionEvent::~CollisionEvent(){}

Event::EventType CollisionEvent::getType() const
{
    return _type;
}
