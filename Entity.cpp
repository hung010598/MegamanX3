#include "Entity.h"
#include "GameCollision.h"


Entity::Entity()
{
	Tag = None;
}
Entity::Entity(float id,float x,float y,float width,float height)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}
D3DXVECTOR3 Entity::GetPosition()
{
	return D3DXVECTOR3(posX, posY,0);
}

RECT Entity::GetBound()
{
	RECT bound;

	bound.left = posX - width / 2;
	bound.right = posX + width / 2;
	bound.top = posY - height / 2;
	bound.bottom = posY + height / 2;

	return bound;
}

void Entity::OnCollision(Entity *impactor, CollisionReturn data, Entity::SideCollisions side)
{
	vx = 0, vy = 0;
}

void Entity::OnSetPosition(D3DXVECTOR3 pos)
{

}

void Entity::Update(float dt)
{
	//velocity = pixel / s
	posX += vx * dt;
	posY += vy * dt;
}

void Entity::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR2(x, y));
}

void Entity::SetPosition(D3DXVECTOR2 pos)
{
	SetPosition(D3DXVECTOR3(pos.x, pos.y, 0));
}

void Entity::SetPosition(D3DXVECTOR3 pos)
{
	this->posX = pos.x;
	this->posY = pos.y;

	OnSetPosition(pos);
}

void Entity::AddPosition(D3DXVECTOR3 pos)
{
	this->SetPosition(this->GetPosition() + pos);
}

void Entity::AddPosition(D3DXVECTOR2 pos)
{
	AddPosition(D3DXVECTOR3(pos));
}

void Entity::AddPosition(float x, float y)
{
	AddPosition(D3DXVECTOR3(x, y, 0));
}
void Entity::SetID(int ID)
{
	this->id = ID;
}
int Entity::GetID()
{
	return id;
}
void Entity::SetWidth(int width)
{
	this->width = width;
}

int Entity::GetWidth()
{
	return width;
}

void Entity::SetHeight(int height)
{
	this->height = height;
}

int Entity::GetHeight()
{
	return height;
}
void Entity::SetX(int X)
{
	this->x = X;
}
int Entity::GetX()
{
	return x;
}
void Entity::SetY(int Y)
{
	this->y = Y;
}
int Entity::GetY()
{
	return y;
}
float Entity::GetVx()
{
	return vx;
}

void Entity::SetVx(float vx)
{
	this->vx = vx;
}

void Entity::AddVx(float vx)
{
	this->vx += vx;
}

float Entity::GetVy()
{
	return vy;
}

void Entity::SetVy(float vy)
{
	this->vy = vy;
}

void Entity::AddVy(float vy)
{
	this->vy += vy;
}
