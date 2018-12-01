#pragma once

#include "PlayerData.h"
#include "Entity.h"
#include <map>
#include "GameCollision.h"

class PlayerState
{
public:
	enum StateName
	{
		Standing,
		Running,
		Falling,
		FallingOnWall,
		Jumping,
		Shooting,
		RunAndShoot,
		Dashing,
		Die
	};

	~PlayerState();

	virtual void Update(float dt);

	virtual void HandleKeyboard(std::map<int, bool> keys);
	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	//ham thuan ao bat buoc phai ke thua
	virtual StateName GetState() = 0;

protected:
	PlayerState(PlayerData *playerData);
	PlayerState();

	PlayerData *mPlayerData;

};
