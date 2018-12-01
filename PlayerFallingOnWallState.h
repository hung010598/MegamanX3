#pragma once
#include "PlayerState.h"



class PlayerFallingOnWallState : public PlayerState
{
public:
	PlayerFallingOnWallState(PlayerData *playerData);
	~PlayerFallingOnWallState();

	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float acceleratorY;
	float acceleratorX;

	//neu nhu van toc ban dau = khong thi se khong cho giam toc do
	bool allowMoveX;

	bool isLeftOrRightKeyPressed;
};
