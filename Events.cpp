#include "Events.h"

FullscreenEvent::FullscreenEvent() {
	_type = EV_FULLSCREEN;
}
FullscreenEvent::~FullscreenEvent() {}

Event::EventType FullscreenEvent::getType() const {
	return _type;
}

RunDownEvent::RunDownEvent(unsigned int targetID) {
	_type = EV_RUNDOWN;
	_targetID = targetID;
}
RunDownEvent::~RunDownEvent() {}

unsigned int RunDownEvent::getTargetID() const {
	return _targetID;
}

Event::EventType RunDownEvent::getType() const {
	return _type;
}

RunUpEvent::RunUpEvent(unsigned int targetID) {
	_type = EV_RUNUP;
	_targetID = targetID;
}
RunUpEvent::~RunUpEvent() {}

unsigned int RunUpEvent::getTargetID() const {
	return _targetID;
}

Event::EventType RunUpEvent::getType() const {
	return _type;
}

RunLeftEvent::RunLeftEvent(unsigned int targetID) {
	_type = EV_RUNLEFT;
	_targetID = targetID;
}
RunLeftEvent::~RunLeftEvent() {}

unsigned int RunLeftEvent::getTargetID() const {
	return _targetID;
}

Event::EventType RunLeftEvent::getType() const {
	return _type;
}

RunRightEvent::RunRightEvent(unsigned int targetID) {
	_type = EV_RUNRIGHT;
	_targetID = targetID;
}
RunRightEvent::~RunRightEvent() {}

unsigned int RunRightEvent::getTargetID() const {
	return _targetID;
}

Event::EventType RunRightEvent::getType() const {
	return _type;
}

WalkDownEvent::WalkDownEvent(unsigned int targetID) {
	_targetID = targetID;
	_type = EV_WALKDOWN;
}
WalkDownEvent::~WalkDownEvent() {}

unsigned int WalkDownEvent::getTargetID() const {
	return _targetID;
}

Event::EventType WalkDownEvent::getType() const {
	return _type;
}

WalkUpEvent::WalkUpEvent(unsigned int targetID) {
	_targetID = targetID;
	_type = EV_WALKUP;
}
WalkUpEvent::~WalkUpEvent() {}

unsigned int WalkUpEvent::getTargetID() const {
	return _targetID;
}

Event::EventType WalkUpEvent::getType() const {
	return _type;
}

WalkLeftEvent::WalkLeftEvent(unsigned int targetID) {
	_targetID = targetID;
	_type = EV_WALKLEFT;
}
WalkLeftEvent::~WalkLeftEvent() {}

unsigned int WalkLeftEvent::getTargetID() const {
	return _targetID;
}

Event::EventType WalkLeftEvent::getType() const {
	return _type;
}

WalkRightEvent::WalkRightEvent(unsigned int targetID) {
	_type = EV_WALKRIGHT;
	_targetID = targetID;
}
WalkRightEvent::~WalkRightEvent() {}

unsigned int WalkRightEvent::getTargetID() const {
	return _targetID;
}

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

TurnDownEvent::TurnDownEvent(unsigned int targetID) {
	_type = EV_TURNDOWN;
}
TurnDownEvent::~TurnDownEvent() {}

unsigned int TurnDownEvent::getTargetID() const {
	return _targetID;
}

Event::EventType TurnDownEvent::getType() const {
	return _type;
}

TurnUpEvent::TurnUpEvent(unsigned int targetID) {
	_type = EV_TURNUP;
	_targetID = targetID;
}
TurnUpEvent::~TurnUpEvent() {}

unsigned int TurnUpEvent::getTargetID() const {
	return _targetID;
}

Event::EventType TurnUpEvent::getType() const {
	return _type;
}

TurnLeftEvent::TurnLeftEvent(unsigned int targetID) {
	_type = EV_TURNLEFT;
	_targetID = targetID;
}
TurnLeftEvent::~TurnLeftEvent() {}

unsigned int TurnLeftEvent::getTargetID() const {
	return _targetID;
}

Event::EventType TurnLeftEvent::getType() const {
	return _type;
}

TurnRightEvent::TurnRightEvent(unsigned int targetID) {
	_type = EV_TURNRIGHT;
	_targetID = targetID;
}
TurnRightEvent::~TurnRightEvent() {}

unsigned int TurnRightEvent::getTargetID() const {
	return _targetID;
}

Event::EventType TurnRightEvent::getType() const {
	return _type;
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
