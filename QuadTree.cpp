#include "QuadTree.h"
#include "GameComponents/GameGlobal.h"
#include <fstream>
#include <string.h>

using namespace std;
QuadTree::~QuadTree()
{
	
}

QuadTree::QuadTree(int level, RECT bound,int x,int y,int w,int h,int id)
{
	//chia lam 4
	this->Bound = bound;
	this->mLevel = level;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->id = id;
}

void QuadTree::setID(Entity *entity)
{
	this->id=entity->GetID();
}
int QuadTree::getID()
{
	return id;
}
void QuadTree::setW(Entity *entity)
{
	this->w = entity->GetWidth();
}
int QuadTree::getW()
{
	return w;
}
void QuadTree::setH(Entity *entity)
{
	this->h = entity->GetHeight();
}
int QuadTree::getH()
{
	return h;
}
void QuadTree::setX(Entity *entity)
{
	this->x = entity->GetX();
}
int QuadTree::getX()
{
	return x;
}
void QuadTree::setY(Entity *entity)
{
	this->y = entity->GetY();
}
int QuadTree::getY()
{
	return y;
}
void QuadTree::Clear()
{
	if (Nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (Nodes[i])
			{
				Nodes[i]->Clear();
				delete Nodes[i];
				Nodes[i] = nullptr;
			}
		}

		delete[] Nodes;
	}
}

void QuadTree::insertEntity(Entity *entity)
{
	int index = getIndex(entity->GetBound());
	
	//neu node ta ton tai thi insert vao node con
	if (Nodes != NULL)
	{
		if (index != -1)
		{
			Nodes[index]->insertEntity(entity);
			
			return;
		}
	}

	//luc nay entity nam giua 2 Bound nen se add vao node nay luon
	if (index == -1)
	{
		setID(entity);
		setW(entity);
		setH(entity);
		setX(entity);
		setY(entity);
		this->mListEntity.push_back(entity);
		
	}
	else
	{
		//node chua dc tao nen se tao va split roi moi insert
		if (Nodes == NULL)
		{
			split();
		}

		Nodes[index]->insertEntity(entity);
		
	}
	
}

bool QuadTree::isContain(Entity *entity)
{
	RECT r = entity->GetBound();

	if (r.left >= Bound.left && r.right <= Bound.right && r.top >= Bound.top && r.bottom <= Bound.bottom)
	{
		return true;
	}

	return false;
}

void QuadTree::split()
{
	//cat phan region (ranh gioi) ra thanh 4 phan bang nhau
	Nodes = new QuadTree *[4];
	
	RECT bound;

	int width = (Bound.right - Bound.left) / 2;
	int height = (Bound.bottom - Bound.top) / 2;

	//phan goc trai tren
	bound.left = Bound.left;
	bound.right = bound.left + width;
	bound.top = Bound.top;
	bound.bottom = bound.top + height;
	Nodes[0] = new QuadTree(mLevel + 1, bound,x,y,w,h,id);

	//phan goc phai tren
	bound.left = Bound.left + width;
	bound.right = bound.left + width;
	bound.top = Bound.top;
	bound.bottom = bound.top + height;
	Nodes[1] = new QuadTree(mLevel + 1, bound, x, y, w, h, id);

	//phan goc trai duoi
	bound.left = Bound.left;
	bound.right = bound.left + width;
	bound.top = Bound.top + height;
	bound.bottom = bound.top + height;
	Nodes[2] = new QuadTree(mLevel + 1, bound, x, y, w, h, id);

	//phan goc phai duoi
	bound.left = Bound.left + width;
	bound.right = bound.left + width;
	bound.top = Bound.top + height;
	bound.bottom = bound.top + height;
	Nodes[3] = new QuadTree(mLevel + 1, bound, x, y, w, h, id);
}

//void QuadTree::serialize(QuadTree *n, FILE *fp)
//{
//	if (n == NULL)
//		return;
//	ofstream out("Data/QuadTree.txt");
//	out << getID;
//}
int QuadTree::getTotalEntities()
{
	int total = mListEntity.size();

	if (Nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			total += Nodes[i]->getTotalEntities();
		}
	}
	
	return total;
}

int QuadTree::getIndex(RECT body)
{
	/*lay vi tri cua Entity
	0: nam trong Node con goc trai tren
	1: nam trong Node con goc phai tren
	2: nam trong Node con goc trai duoi
	3: nam trong Node con goc phai duoi
	-1: bi dinh > 2 node con*/

	float middleVerticle = Bound.left + (Bound.right - Bound.left) / 2.0f;
	float middleHorizontal = Bound.top + (Bound.bottom - Bound.top) / 2.0f;

	if (body.top > Bound.top && body.bottom < middleHorizontal)
	{
		//nam phia ben tren
		if (body.left > Bound.left && body.right < middleVerticle)
		{
			//nam phia ben trai
			return 0;
		}
		else if (body.left > middleVerticle && body.right < Bound.right)
		{
			//nam phia ben phai
			return 1;
		}
	}
	else if (body.top > middleHorizontal && body.bottom < Bound.bottom)
	{
		//nam phia ben duoi
		if (body.left > Bound.left && body.right < middleVerticle)
		{
			//nam phia ben trai
			return 2;
		}
		else if (body.left > middleVerticle && body.right < Bound.right)
		{
			//nam phia ben phai
			return 3;
		}
	}

	return -1;
}

void QuadTree::getAllEntities(std::vector<Entity*> &entitiesOut)
{
	for (auto child : mListEntity)
	{
		entitiesOut.push_back(child);
	}

	if (Nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			Nodes[i]->getAllEntities(entitiesOut);
		}
	}
	
}

void QuadTree::getEntitiesCollideAble(std::vector<Entity*> &entitiesOut, Entity *entity)
{
	int index = this->getIndex(entity->GetBound());

	if (index != -1)
	{
		//nhung Entity o day se la nam tren 2 node con nen chung ta cung se lay de set va cham
		for (auto child : mListEntity)
		{
			entitiesOut.push_back(child);
		}

		if (Nodes != NULL)
		{
			//kiem tra va lay cac node trong node con
			Nodes[index]->getEntitiesCollideAble(entitiesOut, entity);
		}
	}
	else
	{
		getAllEntities(entitiesOut);
	}
}
void QuadTree::save()
{
	if (Nodes)
	{
		if (Nodes[0])
		{
			fstream f;
			f.open("Data/QuadTree.txt", ios::out | ios::app);
			if(Nodes[0]->getID()!=0)
				f << Nodes[0]->getID() << " " << Nodes[0]->getW() << " " << Nodes[0]->getH() << " " << Nodes[0]->getX() << " " << Nodes[0]->getY() << "	";
			Nodes[0]->save();
		}
		if (Nodes[1])
		{
			fstream f;
			f.open("Data/QuadTree.txt", ios::out | ios::app);
			if (Nodes[1]->getID() != 0)
				f << Nodes[1]->getID() << " " << Nodes[1]->getW() << " " << Nodes[1]->getH() << " " << Nodes[1]->getX() << " " << Nodes[1]->getY() << "	";
			Nodes[1]->save();
		}
		if (Nodes[2])
		{
			fstream f;
			f.open("Data/QuadTree.txt", ios::out | ios::app);
			if (Nodes[2]->getID() != 0)
				f << Nodes[2]->getID() << " " << Nodes[2]->getW() << " " << Nodes[2]->getH() << " " << Nodes[2]->getX() << " " << Nodes[2]->getY() << "	";
			Nodes[2]->save();
		}
		if (Nodes[3])
		{
			fstream f;
			f.open("Data/QuadTree.txt", ios::out | ios::app);
			if (Nodes[3]->getID() != 0)
				f << Nodes[3]->getID() << " " << Nodes[3]->getW() << " " << Nodes[3]->getH() << " " << Nodes[3]->getX() << " " << Nodes[3]->getY() << "	";
			Nodes[3]->save();
		}
		
	}
	// needs to add EOL 
	/*if (n->Nodes[0]->getID() == NULL)
		return;*/
	/*fstream f;
	f.open("Data/QuadTree.txt", ios::out | ios::app);
	f << Nodes[0]->getID();*/
	/*n = n->Nodes[1];
	if (n->getID() != NULL)
	{
		
		save(n);
	}*/
}
