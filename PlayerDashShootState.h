#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerDashShootState : public PlayerState
{
public:
	PlayerDashShootState(PlayerData *playerData);
	~PlayerDashShootState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();

protected:
	//do bien thien van toc sau moi frame tinh bang pixel / s
	float acceleratorX;
	bool noPressed;
};

