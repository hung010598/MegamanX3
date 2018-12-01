#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerRunShootState : public PlayerState
{
public:
	PlayerRunShootState(PlayerData *playerData);
	~PlayerRunShootState();
	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float acceleratorX;
};

