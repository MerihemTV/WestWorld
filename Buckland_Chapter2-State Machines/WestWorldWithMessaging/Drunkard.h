#pragma once

#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "DrunkardOwnedStates.h"
#include "fsm/StateMachine.h"

template <class entity_type> class State;
struct Telegram;



class Drunkard : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Drunkard>*  m_pStateMachine;

	location_type         m_Location;

	//the higher the value, the more alcoholized the drunkard
	int                   m_iAlcoholized;

	//the higher the value, the more tired the drunkard
	int                   m_iFatigue;

	//above this value the drunkard is drunk
	const int DrunkLevel = 5;

	//above this value a drunkard is sleepy
	const int TirednessThreshold = 5;

public:

	Drunkard(int id) :m_Location(DrunkardsShack),
		m_iAlcoholized(0),
		m_iFatigue(0),
		BaseGameEntity(id)

	{
		//set up state machine
		m_pStateMachine = new StateMachine<Drunkard>(this);

		m_pStateMachine->SetCurrentState(GoHomeAndSleepIilRested::Instance());
	}

	~Drunkard() { delete m_pStateMachine; }

	void Update();

	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Drunkard>* GetFSM()const { return m_pStateMachine; }



	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool          Fatigued()const;
	void          DecreaseFatigue() { m_iFatigue -= 1; }
	void          IncreaseFatigue() { m_iFatigue += 1; }
	int			  GetFatigueLevel()const { return m_iFatigue; }

	void          DecreaseAlcoholization() { m_iAlcoholized -= 1; }
	void          IncreaseAlcoholization() { m_iAlcoholized += 1; }
	bool          Alcoholized()const;
	int			  GetAlcoholization()const { return m_iAlcoholized; };

};