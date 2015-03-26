#pragma once
#include "cocos2d.h"
USING_NS_CC;
class FSM 
	:public CCObject
{
public:
	FSM(std::string state,std::function<void()> onEnter = nullptr);
	~FSM(void);
	static FSM* create(std::string state,std::function<void()> onEnter = nullptr);
	FSM* addState(std::string state,std::function<void()> onEnter = nullptr);
	FSM* addEvent(std::string eventName,std::string from,std::string to);
	bool isContainState(std::string state);
	void doEvent(std::string eventName);
	bool canDoEvent(std::string eventName);
	void setOnEnter(std::string state,std::function<void()> onEnter = nullptr);
	std::string getState(){return _currentState;}
	std::string getPreState(){return _previousState;}
private:
	void changeToState(std::string state);
private:
	std::set<std::string> _states;
	std::map<std::string,std::map<std::string,std::string>> _events;
	std::map<std::string,std::function<void()>> _onEnters;
	std::string _currentState;
	std::string _previousState;
};

