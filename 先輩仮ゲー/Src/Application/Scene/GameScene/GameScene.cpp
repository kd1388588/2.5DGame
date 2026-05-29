#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/Player/Player.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void GameScene::Init()
{
	// ============================
	//	Playerの追加
	// ============================
	m_player = std::make_shared<Player>();
	m_player->Init();
	m_objList.push_back(m_player);
}
