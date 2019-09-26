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
class GoSaloonAndDrinkTilDrunk : public State<Drunkard>
{
private:

	GoSaloonAndDrinkTilDrunk() {}

	//copy ctor and assignment should be private
	GoSaloonAndDrinkTilDrunk(const GoSaloonAndDrinkTilDrunk&);
	GoSaloonAndDrinkTilDrunk& operator=(const GoSaloonAndDrinkTilDrunk&);

public:

	//this is a singleton
	static GoSaloonAndDrinkTilDrunk* Instance();

	virtual void Enter(Drunkard* Drunkard);

	virtual void Execute(Drunkard* Drunkard);

	virtual void Exit(Drunkard* Drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  Drunkard has drunk too much alcohol and is now drunk
//------------------------------------------------------------------------
class Drunk : public State<Drunkard>
{
private:

	Drunk() {}

	//copy ctor and assignment should be private
	Drunk(const Drunk&);
	Drunk& operator=(const Drunk&);

public:

	//this is a singleton
	static Drunk* Instance();

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
class Brawling : public State<Drunkard>
{
private:

	Brawling() {}

	//copy ctor and assignment should be private
	Brawling(const Brawling&);
	Brawling& operator=(const Brawling&);

public:

	//this is a singleton
	static Brawling* Instance();

	virtual void Enter(Drunkard* Drunkard);

	virtual void Execute(Drunkard* Drunkard);

	virtual void Exit(Drunkard* Drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};