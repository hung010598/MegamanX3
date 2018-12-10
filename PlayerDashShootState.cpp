#include "PlayerDashShootState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "GameDefine.h"

PlayerDashShootState::PlayerDashShootState(PlayerData *playerData)
{
	this->mPlayerData = playerData;

	acceleratorX = 4.0f;

	noPressed = false;
}


PlayerDashShootState::~PlayerDashShootState()
{
}

void PlayerDashShootState::Update(float dt)
{
	if (mPlayerData->player->GetReverse()) {
		if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_DASHING_SPEED)
		{
			this->mPlayerData->player->AddVx(-acceleratorX);
		}
	}
	else {
		if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_DASHING_SPEED)
		{
			this->mPlayerData->player->AddVx(acceleratorX);
		}
	}

	if (this->mPlayerData->player->GetVx() <= -Define::PLAYER_MAX_DASHING_SPEED ||
		this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_DASHING_SPEED)
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

void PlayerDashShootState::HandleKeyboard(std::map<int, bool> keys)
{
	
	if (keys[0x51])
	{
		if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
		{
			mPlayerData->player->SetReverse(true);

			//di chuyen sang trai
			if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_DASHING_SPEED)
			{
				this->mPlayerData->player->AddVx(-acceleratorX);

				if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_DASHING_SPEED)
				{
					this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_DASHING_SPEED);
				}
			}
		}

		else if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		{
			mPlayerData->player->SetReverse(false);

			//di chuyen sang phai
			if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_DASHING_SPEED)
			{
				this->mPlayerData->player->AddVx(acceleratorX);

				if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_DASHING_SPEED)
				{
					this->mPlayerData->player->SetVx(Define::PLAYER_MAX_DASHING_SPEED);
				}
			}
		}

		noPressed = false;
	}
	else
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

PlayerState::StateName PlayerDashShootState::GetState()
{
	return PlayerState::DashShoot;
}

void PlayerDashShootState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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
