#pragma once

#include <d3dx9.h>
#include <d3d9.h>

#include "GameComponents/GameGlobal.h"


class Entity
{
public:
	Entity();

	enum SideCollisions
	{
		Left,
		Right,
		Top,
		Bottom,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		NotKnow
	};

	enum EntityTypes
	{
		None, Enemy, Megaman, Static
	};

	EntityTypes Tag;

	virtual RECT GetBound();

	virtual void SetPosition(float x, float y);

	virtual void SetPosition(D3DXVECTOR2 pos);

	virtual void SetPosition(D3DXVECTOR3 pos);

	virtual void AddPosition(D3DXVECTOR3 pos);

	virtual void AddPosition(D3DXVECTOR2 pos);

	virtual void AddPosition(float x, float y);

	virtual void SetWidth(int width);

	virtual int GetWidth();

	virtual void SetHeight(int height);

	virtual int GetHeight();

	virtual float GetVx();

	virtual void SetVx(float vx);

	virtual void AddVx(float vx);

	virtual float GetVy();

	virtual void SetVy(float vy);

	virtual void AddVy(float vy);

	virtual D3DXVECTOR3 GetPosition();

	virtual void Update(float dt);


protected:

	// duoc goi khi set position cua Entity, dung cho ke thua
	virtual void OnSetPosition(D3DXVECTOR3 pos);

	// vi tri tam position x va y
	float posX, posY;

	// van toc vx, vy
	float vx, vy;

	// size cua entity
	float width, height;


};

