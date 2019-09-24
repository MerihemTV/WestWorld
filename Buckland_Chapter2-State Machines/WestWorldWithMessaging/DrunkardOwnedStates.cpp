#include "DrunkardOwnedStates.h"
#include "fsm/State.h"
#include "Drunkard.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for GoHomeAndSleepStillRested

GoHomeAndSleepIilRested* GoHomeAndSleepIilRested::Instance()
{
	static GoHomeAndSleepIilRested instance;

	return &instance;
}

void GoHomeAndSleepIilRested::Enter(Drunkard* pDrunkard)
{
	if (pDrunkard->Location() != DrunkardsShack)
	{
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
			<< "Huh, where's my home ? Is it here ? "
			<< "It seems... Well let's sleep here anyways";

		pDrunkard->ChangeLocation(DrunkardsShack);
	}
}

void GoHomeAndSleepIilRested::Execute(Drunkard* pDrunkard)
{
	//if Drunkard is not fatigued start to dig for nuggets again.
	if (!pDrunkard->Fatigued())
	{
		pDrunkard->GetFSM()->ChangeState(GoSaloonAndDrinkTilDrunk::Instance());
	}

	else
	{
		//sleep and sober up
		pDrunkard->DecreaseFatigue();
		pDrunkard->DecreaseAlcoholization();

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "ZZZZ... *HIC* ZZZZ... ";
	}
}

void GoHomeAndSleepIilRested::Exit(Drunkard* pDrunkard)
{
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
		<< "Ouah... I don't remember anything from yesterday... "
		<< "I should go to the saloon and drink some Whiskey";
}

bool GoHomeAndSleepIilRested::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	return false; //send message to global message handler
}



//------------------------------------------------------------------------methods for GoSaloonAndDrinkTilDrunk

GoSaloonAndDrinkTilDrunk* GoSaloonAndDrinkTilDrunk::Instance()
{
	static GoSaloonAndDrinkTilDrunk instance;

	return &instance;
}

void GoSaloonAndDrinkTilDrunk::Enter(Drunkard* pDrunkard)
{
	if (pDrunkard->Location() != saloon)
	{
		pDrunkard->ChangeLocation(saloon);

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Give me a drink ! I'm thirsty ! ";
	}
}

void GoSaloonAndDrinkTilDrunk::Execute(Drunkard* pDrunkard)
{
	pDrunkard->IncreaseAlcoholization();
	pDrunkard->IncreaseFatigue();

	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Slurp, that Whisky's really good !";

	if (pDrunkard->Alcoholized())
	{
		pDrunkard->GetFSM()->ChangeState(Drunk::Instance());
	}
}

void GoSaloonAndDrinkTilDrunk::Exit(Drunkard* pDrunkard)
{
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "I've... drunk... way... to much... Whiskey... *HIC!*";
}

bool GoSaloonAndDrinkTilDrunk::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}



//------------------------------------------------------------------------methods for Drunk

Drunk* Drunk::Instance()
{
	static Drunk instance;

	return &instance;
}

void Drunk::Enter(Drunkard* pDrunkard)
{
	if (pDrunkard->Location() != saloon)
	{
		pDrunkard->ChangeLocation(saloon);

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "*HIC!* I'm gonna stop drinking a lil' *HIC!* bit";
	}

	// Let Bob know the drunkard is drunk
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pDrunkard->ID(),        //ID of sender
		ent_Miner_Bob,          //ID of recipient
		Msg_DrunkardDrunk,		//the message
		NO_ADDITIONAL_INFO);
}

void Drunk::Execute(Drunkard* pDrunkard)
{
	pDrunkard->DecreaseAlcoholization();
	pDrunkard->IncreaseFatigue();

	if(pDrunkard->Fatigued())
	{
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
			<< "Getting tired... Should go home and sleep...";

		pDrunkard->GetFSM()->ChangeState(GoHomeAndSleepIilRested::Instance());
	}
	else if (pDrunkard->GetAlcoholization()==0)
	{
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
			<< "Hmmm, am feeling better now, let's take some more Whiskey !";

		pDrunkard->GetFSM()->ChangeState(GoSaloonAndDrinkTilDrunk::Instance());
	}
}

void Drunk::Exit(Drunkard* pDrunkard)
{
}

bool Drunk::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	SetTextColor(BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_HiDrunkardImAtSaloon:

		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
			<< "*HIC!* Heya ! I saw ya lookin' at me the wrong way !";
		pDrunkard->GetFSM()->ChangeState(Brawling::Instance());

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pDrunkard->ID(),        //ID of sender
			ent_Miner_Bob,          //ID of recipient
			Msg_LetsFight,			//the message
			NO_ADDITIONAL_INFO);

		return true;

	case Msg_LetsFight:

		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
			<< "*HIC!* Heya ! I saw ya lookin' at me the wrong way !";
		pDrunkard->GetFSM()->ChangeState(Brawling::Instance());

		return true;
	
	}//end switch

	return false; //send message to global message handler
}



//------------------------------------------------------------------------methods for Brawling

Brawling* Brawling::Instance()
{
	static Brawling instance;

	return &instance;
}

void Brawling::Enter(Drunkard* pDrunkard)
{
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
		<< "*HIC!* I'ma beat you down now !*HIC!*";
}

void Brawling::Execute(Drunkard* pDrunkard)
{
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pDrunkard->ID(),        //ID of sender
		ent_Miner_Bob,          //ID of recipient
		Msg_FightRound,		//the message
		(void*)pDrunkard->GetFatigueLevel());
}

void Brawling::Exit(Drunkard* pDrunkard)
{
}

bool Brawling::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	SetTextColor(BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_FightRound:

		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);

		if ((int)msg.ExtraInfo >= pDrunkard->GetFatigueLevel())
		{
			// Drunkard won the fight
			cout << "\n" << GetNameOfEntity(pDrunkard->ID())
				<< ": Let's grab anotha whiskey to celebrate this easy victory !";

			pDrunkard->GetFSM()->ChangeState(GoSaloonAndDrinkTilDrunk::Instance());
		}
		else
		{
			// Drunkard lost the fight
			cout << "\n" << GetNameOfEntity(pDrunkard->ID())
				<< ": Gosh, my head hurt so much ... Let's go home now.";

			pDrunkard->GetFSM()->ChangeState(GoHomeAndSleepIilRested::Instance());
		}

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pDrunkard->ID(),        //ID of sender
			ent_Miner_Bob,          //ID of recipient
			Msg_FightRound,		//the message
			(void*)pDrunkard->GetFatigueLevel());

		return true;

	}//end switch

	return false; //send message to global message handler
}
