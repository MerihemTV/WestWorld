#include "Drunkard.h"

bool Drunkard::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Drunkard::Update()
{
	SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}



bool Drunkard::Alcoholized()const
{
	if (m_iAlcoholized >= DrunkLevel) { return true; }

	return false;
}

bool Drunkard::Fatigued()const
{
	if (m_iFatigue > TirednessThreshold)
	{
		return true;
	}

	return false;
}
