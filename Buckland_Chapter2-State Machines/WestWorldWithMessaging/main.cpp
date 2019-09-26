#include <fstream>
#include <time.h>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "Drunkard.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"	
#include "EntityNames.h"


std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif
  bool initOk = false; 
  int chosenState;
  std::cout << "Choose original drunkard state by pressing the right key : " << std::endl
	  << "A : GoHomeAndSleepStillRested" << std::endl
	  << "Z : GoSaloonAndDrinkTilDrunk" << std::endl
	  << "E : Drunk" << std::endl
	  /*<< "R : Brawling" << std::endl*/;
  while (!initOk)
  {
	  if (GetKeyState('A'))
	  {
		  chosenState = 0;
		  initOk = true;
	  }
	  if (GetKeyState('Z') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
	  {
		  chosenState = 1;
		  initOk = true;
	  }
	  if (GetKeyState('E') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
	  {
		  chosenState = 2;
		  initOk = true;
	  }
	  if (GetKeyState('R') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
	  {
		  chosenState = 3;
		  initOk = true;
	  }
  }
  
  //seed random number generator
  srand((unsigned) time(NULL));

  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob);

  //create his wife
  MinersWife* Elsa = new MinersWife(ent_Elsa);
  
  //create a drunkard
  Drunkard* drunkard = new Drunkard(ent_Drunkard, chosenState);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(drunkard);

  //run Bob and Elsa through a few Update calls
  for (int i=0; i<30; ++i)
  { 
    Bob->Update();
    Elsa->Update();
	drunkard->Update();

    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
	std::cout << std::endl;
  }

  //tidy up
  delete Bob;
  delete Elsa;
  delete drunkard;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






