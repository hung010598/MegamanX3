#include "DemoScene.h"

DemoScene::DemoScene()
{
    LoadContent();
}

void DemoScene::LoadContent()
{
    //set mau backcolor cho scene o day la mau xanh
    mBackColor = 0x0b032d;

	mMap = new GameMap("Resources/BlastHornet.tmx");

	mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	mCamera->SetPosition(36, mMap->GetHeight() / 2 - GameGlobal::GetHeight() / 4 );

	mMap->SetCamera(mCamera);

	mPlayer = new Player();
	mPlayer->SetPosition(36, mMap->GetHeight() / 2 - GameGlobal::GetHeight() / 4);
	mPlayer->SetCamera(mCamera);

}

void DemoScene::Update(float dt)
{
	mPlayer->HandleKeyboard(keys);
	mPlayer->Update(dt);

	CheckCameraAndWorldMap();
}

void DemoScene::Draw()
{
	mMap->Draw();
	mPlayer->Draw();
}

void DemoScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;

	mPlayer->OnKeyPressed(keyCode);
}

void DemoScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;

	mPlayer->OnKeyUp(keyCode);
}

void DemoScene::OnMouseDown(float x, float y)
{
}

void DemoScene::CheckCameraAndWorldMap()
{
	mCamera->SetPosition(mPlayer->GetPosition());

	if (mCamera->GetBound().left < 0)
	{
		//vi position cua camera ma chinh giua camera
		//luc nay o vi tri goc ben trai cua the gioi thuc
		mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().right > mMap->GetWidth())
	{
		//luc nay cham goc ben phai cua the gioi thuc
		mCamera->SetPosition(mMap->GetWidth() - mCamera->GetWidth() / 2,
			mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().top < 0)
	{
		//luc nay cham goc tren the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
	}

	if (mCamera->GetBound().bottom > mMap->GetHeight())
	{
		//luc nay cham day cua the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x,
			mMap->GetHeight() - mCamera->GetHeight() / 2);
	}
}
