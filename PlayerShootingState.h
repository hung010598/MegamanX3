#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerShootingState : public PlayerState
{
public:
	PlayerShootingState(PlayerData *playerData);
	~PlayerShootingState();
	void HandleKeyboard(std::map<int, bool> keys);

	void Update(float dt);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float acceleratorX;
	bool noPressed;
};