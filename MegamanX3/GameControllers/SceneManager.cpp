#include "SceneManager.h"

SceneManager* SceneManager::mInstance = NULL;

SceneManager::SceneManager()
{
    mCurrentScene = nullptr;
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
    if (!mInstance)
        mInstance = new SceneManager();

    return mInstance;
}

Scene* SceneManager::GetCurrentScene()
{
    return mCurrentScene;
}

void SceneManager::Update(float dt)
{
    mCurrentScene->Update(dt);
}

void SceneManager::ReplaceScene(Scene *scene)
{
    delete mCurrentScene;

    mCurrentScene = scene;
}