#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include "GameCollision.h"
#include "GameComponents/Camera.h"
#include "Entity.h"
#include <fstream>


class QuadTree
{
public:

	RECT Bound;
	QuadTree(int level, RECT bound,int x,int y,int w,int h,int id);
	~QuadTree();
	void Clear();
	void insertEntity(Entity *entity);

	/*lay danh sach nhung Entity co kha nang xay ra va cham
	tra ve danh sach cac phan tu nam trong vung va cham */
	void getEntitiesCollideAble(std::vector<Entity*> &entitiesOut, Entity *entity);

	void getAllEntities(std::vector<Entity*> &entitiesOut);
	void save();
	int getTotalEntities();
	void setID(Entity *entity);
	int getID();
	void setW(Entity *entity);
	int getW();
	void setH(Entity *entity);
	int getH();
	void setX(Entity *entity);
	int getX();
	void setY(Entity *entity);
	int getY();
protected:
	QuadTree **Nodes;
	QuadTree *n;
	Entity *entity;
	std::vector<Entity*> mListEntity; //danh sach cac phan tu co trong vung va cham (Bound)

	/*lay vi tri cua Entity
	0: nam trong Node con goc trai tren
	1: nam trong Node con goc phai tren
	2: nam trong Node con goc trai duoi
	3: nam trong Node con goc phai duoi
	-1: bi dinh > 2 node con*/
	int getIndex(RECT body);

	void split(); //thuc hien chia ra cac node
	//void serialize(QuadTree *n, FILE *fp);
	bool isContain(Entity *entity);
	int mLevel; //tuong ung voi so node
	int x, y,w,h;
	int id;
};