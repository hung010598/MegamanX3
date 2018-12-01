#include "PlayerShootingState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "GameCollision.h"
#include "GameDefine.h"

PlayerShootingState::PlayerShootingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	noPressed = false;
}


PlayerShootingState::~PlayerShootingState()
{
}


void PlayerShootingState::Update(float dt)
{
	if (noPressed)
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
	}

}

void PlayerShootingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[0x57])
	{
		if (keys[VK_LEFT] || keys[VK_RIGHT])
		{
			this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
			return;
		}
	}
	else
	{

		noPressed = true;
	}

}

void PlayerShootingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);

	switch (side)
	{
	case Entity::Left:
	{
		//va cham phia ben trai player
		if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
		{
			this->mPlayerData->player->allowMoveLeft = false;

			//day Player ra phia ben phai de cho player khong bi xuyen qua object
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		}

		return;
	}

	case Entity::Right:
	{
		//va cham phia ben phai player
		if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		{
			this->mPlayerData->player->allowMoveRight = false;
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		}
		return;
	}

	case Entity::Top:
		break;

	case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
	{
		this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

		this->mPlayerData->player->SetVy(0);
		return;
	}
	}
}

PlayerState::StateName PlayerShootingState::GetState()
{
	return PlayerState::Shooting;
}
