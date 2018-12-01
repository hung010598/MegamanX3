#include "PlayerFallingOnWallState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "GameCollision.h"
#include "GameDefine.h"
#include "PlayerJumpingState.h"

PlayerFallingOnWallState::PlayerFallingOnWallState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	acceleratorY = 10.0f;

	allowMoveX = false;
}


PlayerFallingOnWallState::~PlayerFallingOnWallState()
{
}

void PlayerFallingOnWallState::Update(float dt)
{
	this->mPlayerData->player->AddVy(acceleratorY);

	if (mPlayerData->player->GetVy() > Define::PLAYER_MAX_FALLING_ON_WALL_VELOCITY)
	{
		mPlayerData->player->SetVy(Define::PLAYER_MAX_FALLING_ON_WALL_VELOCITY);
	}
}

void PlayerFallingOnWallState::HandleKeyboard(std::map<int, bool> keys)
{
	// Player se bat ra mot doan khi nhan nhay
	if (keys[VK_SPACE]) {
		this->mPlayerData->player->AddVy(Define::PLAYER_MAX_JUMP_VELOCITY);

		if (this->mPlayerData->player->GetReverse() == true)
			this->mPlayerData->player->AddVx(Define::PLAYER_MAX_RUNNING_SPEED / 2);
		else
			this->mPlayerData->player->AddVx(-Define::PLAYER_MAX_RUNNING_SPEED / 2);

		this->mPlayerData->player->SetState(new PlayerJumpingState(this->mPlayerData));
	}
}

void PlayerFallingOnWallState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);

	switch (side)
	{
	case Entity::Left:
		if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
		{
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			this->mPlayerData->player->SetVx(0);
		}
		break;

	case Entity::Right:
		if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		{
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			this->mPlayerData->player->SetVx(0);
		}
		break;

	case Entity::Top:
		break;

	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		if (data.RegionCollision.right - data.RegionCollision.left >= Define::PLAYER_BOTTOM_RANGE_FALLING)
		{
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));


			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));

		}
		return;

	default:
		break;
	}
}

PlayerState::StateName PlayerFallingOnWallState::GetState()
{
	return PlayerState::FallingOnWall;
}
