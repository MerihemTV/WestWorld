#pragma once
#include "fsm/State.h"


class Drunkard;
struct Telegram;

//------------------------------------------------------------------------
//
//  Drunkard will go home and sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
class GoHomeAndSleepStillRested : public State<Drunkard>
{
private:

	GoHomeAndSleepStillRested(){}

	//copy ctor and assignment should be private
	GoHomeAndSleepStillRested(const GoHomeAndSleepStillRested&);
	GoHomeAndSleepStillRested& operator=(const GoHomeAndSleepStillRested&);

public:

	//this is a singleton
	static GoHomeAndSleepStillRested* Instance();

	virtual void Enter(Drunkard* Drunkard);

	virtual void Execute(Drunkard* Drunkard);

	virtual void Exit(Drunkard* Drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  Drunkard keeps buying Whiskey until he's drunk. 
//------------------------------------------------------------------------
class Drink : public State<Drunkard>
{
private:

	Drink() {}

	//copy ctor and assignment should be private
	Drink(const Drink&);
	Drink& operator=(const Drink&);

public:

	//this is a singleton
	static Drink* Instance();

	virtual void Enter(Drunkard* Drunkard);

	virtual void Execute(Drunkard* Drunkard);

	virtual void Exit(Drunkard* Drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  Drunkard has drunk too much alcohol and is now drunk
//------------------------------------------------------------------------
class IsDrunk : public State<Drunkard>
{
private:

	IsDrunk() {}

	//copy ctor and assignment should be private
	IsDrunk(const IsDrunk&);
	IsDrunk& operator=(const IsDrunk&);

public:

	//this is a singleton
	static IsDrunk* Instance();

	virtual void Enter(Drunkard* Drunkard);

	virtual void Execute(Drunkard* Drunkard);

	virtual void Exit(Drunkard* Drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};



//------------------------------------------------------------------------
//
//  Drunkard is drunk and Miner Bob is present, he wants to brawl 
//	because... Eh he's drunk don't expect logical actions !
//------------------------------------------------------------------------
class IsBrawling : public State<Drunkard>
{
private:

	IsBrawling() {}

	//copy ctor and assignment should be private
	IsBrawling(const IsDrunk&);
	IsBrawling& operator=(const IsDrunk&);

public:

	//this is a singleton
	static IsBrawling* Instance();

	virtual void Enter(Drunkard* Drunkard);

	virtual void Execute(Drunkard* Drunkard);

	virtual void Exit(Drunkard* Drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};