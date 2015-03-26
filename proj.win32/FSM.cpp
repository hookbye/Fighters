#include "FSM.h"


FSM::FSM(std::string state,std::function<void()> onEnter )
{
	_currentState = state;
	_previousState = "";
	this->addState(state,onEnter);
}


FSM::~FSM(void)
{
}

FSM* FSM::create(std::string state,std::function<void()> onEnter)
{
	FSM* fsm = new FSM(state,onEnter);
	if(fsm)
	{
		fsm->autorelease();
		return fsm;
	}
	CC_SAFE_DELETE(fsm);
	return nullptr;
}
FSM* FSM::addState(std::string state,std::function<void()> onEnter)
{
	if("" == state)
	{
		return nullptr;
	}
	_states.insert(state);
	_onEnters[state] = onEnter;
	return this;
}

bool FSM::isContainState(std::string state)
{
	return _states.find(state) != _states.end();
}

void FSM::changeToState(std::string state)
{
	if(isContainState(state))
	{
		_previousState = _currentState;
		_currentState = state;
		if(_onEnters[state])
			_onEnters[state]();
	}
	else
	{
		cocos2d::CCLog("FSM::changeToState: no such state as %s , state unchanged", state.c_str());
	}
}

FSM* FSM::addEvent(std::string eventName, std::string from, std::string to)
{
	if("" == eventName)
	{
		cocos2d::CCLog("FSM::addEvent: eventName can't be empty!");
		return nullptr;
	}
	if(!isContainState(from))
	{
		cocos2d::CCLog("FSM::addEvent: from state %s does not exit", from.c_str());
		return nullptr;
	}
	if(!isContainState(to))
	{
		cocos2d::CCLog("FSM::addEvent: to state %s does not exit", to.c_str());
		return nullptr;
	}
	std::map<std::string ,std::string>& oneEvent = _events[eventName];
	oneEvent[from] = to;
	return this;
}

bool FSM::canDoEvent(std::string eventName)
{
	return _events[eventName].find(_currentState) != _events[eventName].end();
}

void FSM::doEvent(std::string eventName)
{
	if(canDoEvent(eventName))
	{
		cocos2d::CCLog("FSM::doEvent: doing event %s", eventName.c_str());
		changeToState(_events[eventName][_currentState]);
	}else
	{
		cocos2d::CCLog("FSM::doEvent: cannot do event %s", eventName.c_str());
	}
}

void FSM::setOnEnter(std::string state,std::function<void()> onEnter)
{
	if(isContainState(state))
	{
		_onEnters[state] = onEnter;
	}
}

