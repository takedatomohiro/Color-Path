#include "stdafx.h"
#include "GameClear.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "StageManager.h"
#include "GameCamera.h"
#include "Title.h"

GameClear::GameClear()
{
	spriteRender.Init("Assets/sprite/gameclear.dds", 1920.0f, 1080.0f);

	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/gameclear.wav");
	m_gameClearBGM = NewGO<SoundSource>(0);
	m_gameClearBGM->Init(4);
	m_gameClearBGM->Play(false);

	DeleteGO(FindGO<Game>("Game")); // ゲームオブジェクトを削除
	DeleteGO(FindGO<Player>("player")); // プレイヤーオブジェクトを削除
	DeleteGO(FindGO<StageManager>("stageManager")); // ステージマネージャオブジェクトを削除
	DeleteGO(FindGO<BackGround>("backGround")); // 背景オブジェクトを削除
	DeleteGO(FindGO<GameCamera>("GameCamera")); // カメラオブジェクトを削除
}

GameClear::~GameClear()
{
	DeleteGO(m_gameClearBGM);
}

void GameClear::Update()
{
	//Aボタンが押されたら。
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//タイトルのオブジェクトをつくる。
		NewGO<Title>(0, "title");
		//自身を削除する。
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
