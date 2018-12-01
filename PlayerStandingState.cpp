#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerFallingState.h"
#include "PlayerShootingState.h"
#include "GameDefine.h"

PlayerStandingState::PlayerStandingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}


PlayerStandingState::~PlayerStandingState()
{
}


void PlayerStandingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
	if (keys[0x57])
	{
		this->mPlayerData->player->SetState(new PlayerShootingState(this->mPlayerData));
		return;
	}
}

PlayerState::StateName PlayerStandingState::GetState()
{
	return PlayerState::Standing;
}

