#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerDashingState : public PlayerState
{
public:
	PlayerDashingState(PlayerData *playerData);
	~PlayerDashingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();

protected:
	//do bien thien van toc sau moi frame tinh bang pixel / s
	float acceleratorX;
	bool noPressed;
};

