#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_DrunkardDrunk,
  Msg_HiDrunkardImAtSaloon,
  Msg_LetsFight
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    
    return "HiHoneyImHome"; 

  case 1:
    
    return "StewReady";

  case 2:

	  return "DrunkardDrunk";

  case 3:

	  return "HiDrunkardImAtSaloon";

  case 4:

	  return "LetsFight";

  default:

    return "Not recognized!";
  }
}

#endif