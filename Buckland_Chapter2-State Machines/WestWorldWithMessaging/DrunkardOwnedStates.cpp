#include "DrunkardOwnedStates.h"
#include "fsm/State.h"
#include "Drunkard.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"
#include "EntityManager.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for GoHomeAndSleepStillRested

GoHomeAndSleepStillRested* GoHomeAndSleepStillRested::Instance()
{
	static GoHomeAndSleepStillRested instance;

	return &instance;
}

void GoHomeAndSleepStillRested::Enter(Drunkard* pDrunkard)
{
	if (pDrunkard->Location() != DrunkardsShack)
	{
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
			<< "Huh, where's my home ? Is it here ? "
			<< "It seems... Well let's sleep here anyways";

		pDrunkard->ChangeLocation(DrunkardsShack);
	}
}

void GoHomeAndSleepStillRested::Execute(Drunkard* pDrunkard)
{
	//if Drunkard is not fatigued start to dig for nuggets again.
	if (!pDrunkard->Fatigued())
	{
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
			<< "Ouah... I don't remember anything from yesterday... "
			<< "I should go to the saloon and drink some Whisky";

		pDrunkard->GetFSM()->ChangeState(Drink::Instance());
	}

	else
	{
		//sleep
		pDrunkard->DecreaseFatigue();

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "ZZZZ... *Burp* ZZZZ... ";
	}
}

void GoHomeAndSleepStillRested::Exit(Drunkard* pDrunkard)
{
}


bool GoHomeAndSleepStillRested::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	return false; //send message to global message handler
}

//------------------------------------------------------------------------Drink

Drink* Drink::Instance()
{
	static Drink instance;

	return &instance;
}

void Drink::Enter(Drunkard* pDrunkard)
{
	if (pDrunkard->Location() != saloon)
	{
		pDrunkard->ChangeLocation(saloon);

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Give me a drink ! I'm thursty ! ";
	}
}

void Drink::Execute(Drunkard* pDrunkard)
{
	pDrunkard->IncreaseAlcoholization();
	pDrunkard->IncreaseFatigue();

	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Slurp, that Whisky's really good !";

	if (pDrunkard->Alcoholized())
	{
		pDrunkard->GetFSM()->ChangeState(Drunk::Instance());
	}
}


void Drink::Exit(Drunkard* pDrunkard)
{
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "I've... drunk... way... to much... Whisky... *Burp*";
}


bool Drink::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}


//------------------------------------------------------------------------methods for IsDrunk

IsDrunk* IsDrunk::Instance()
{
	static IsDrunk instance;

	return &instance;
}

void IsDrunk::Enter(Drunkard* pDrunkard)
{
}

void IsDrunk::Execute(Drunkard* pDrunkard)
{
	pDrunkard->DecreaseAlcoholization();
	pDrunkard->IncreaseFatigue();

	if (EntityMgr->GetEntityFromID(ent_Miner_Bob)->Location() == saloon )
	{
		//say something
		pDrunkard->GetFSM()->ChangeState(IsBrawling::Instance());
	} else if(pDrunkard->Fatigued())
	{
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
			<< "Getting tired... Should sleep...";

		pDrunkard->GetFSM()->ChangeState(GoHomeAndSleepStillRested::Instance());
	}
	else if (pDrunkard->GetAlcoholization()==0)
	{
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
			<< "Hmmm, am feeling better now, let's take more Whisky !";

		pDrunkard->GetFSM()->ChangeState(Drink::Instance());
	}
}

void IsDrunk::Exit(Drunkard* pDrunkard)
{
}


bool IsDrunk::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	return false; //send message to global message handler
}



//------------------------------------------------------------------------methods for IsBrawling

IsBrawling* IsBrawling::Instance()
{
	static IsBrawling instance;

	return &instance;
}

void IsBrawling::Enter(Drunkard* pDrunkard)
{
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
		<< "Hey yah ! Give me your whisky !";
}

void IsBrawling::Execute(Drunkard* pDrunkard)
{
	//do smth ?
}

void IsBrawling::Exit(Drunkard* pDrunkard)
{
}


bool IsBrawling::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	/*SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_StewReady:

		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pDrunkard->ID())
			<< ": Okay Hun, ahm a comin'!";

		//pDrunkard->GetFSM()->ChangeState(EatStew::Instance());

		return true;

	}//end switch*/

	return false; //send message to global message handler
}
