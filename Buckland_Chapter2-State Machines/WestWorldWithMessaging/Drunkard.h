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
	const int DrunkLevel = 10;

	//above this value a drunkard is sleepy
	const int TirednessThreshold = 10;

public:

	Drunkard(int id, int state) :m_Location(DrunkardsShack),
		m_iFatigue(0),
		BaseGameEntity(id)

	{
		//set up state machine
		m_pStateMachine = new StateMachine<Drunkard>(this);
		switch (state)
		{
		case 0:
			m_pStateMachine->SetCurrentState(GoHomeAndSleepStillRested::Instance());
			m_iAlcoholized = 0;
			break;
		case 1:
			m_pStateMachine->SetCurrentState(GoSaloonAndDrinkTilDrunk::Instance());
			m_iAlcoholized = 0;
			break;
		case 2:
			m_pStateMachine->SetCurrentState(Drunk::Instance());
			m_iAlcoholized = DrunkLevel;
			break;
		/*case 3:
			m_pStateMachine->SetCurrentState(Brawling::Instance());
			m_iAlcoholized = DrunkLevel;
			break;*/
		}
	}

	~Drunkard() { delete m_pStateMachine; }

	void Update();

	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Drunkard>* GetFSM()const { return m_pStateMachine; }



	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool          Fatigued()const;
	void          DecreaseFatigue(int fatigueDecrease)
	{ 
		m_iFatigue = max(m_iFatigue- fatigueDecrease,0);
	}
	void          IncreaseFatigue(int fatigueDecrease) { m_iFatigue += fatigueDecrease; }
	int			  GetFatigueLevel()const { return m_iFatigue; }

	void          DecreaseAlcoholization(int alcoholizationDecrease)
	{ 
		 m_iAlcoholized = max(m_iAlcoholized - alcoholizationDecrease, 0);
	}
	void          IncreaseAlcoholization(int alcoholizationDecrease) { m_iAlcoholized += alcoholizationDecrease; }
	bool          Alcoholized()const;
	int			  GetAlcoholization()const { return m_iAlcoholized; };

};