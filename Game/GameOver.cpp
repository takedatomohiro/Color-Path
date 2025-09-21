#include "stdafx.h"
#include "GameOver.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "StageManager.h"
#include "GameCamera.h"
#include "Title.h"

GameOver::GameOver()
{
	spriteRender.Init("Assets/sprite/TimeOver.dds", 1920.0f, 1080.0f);

	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/gameover.wav");
	gameOverBGM = NewGO<SoundSource>(0);
	gameOverBGM->Init(2);
	gameOverBGM->Play(false);

	DeleteGO(FindGO<Game>("Game")); // ゲームオブジェクトを削除
	DeleteGO(FindGO<Player>("player")); // プレイヤーオブジェクトを削除
	DeleteGO(FindGO<StageManager>("stageManager")); // ステージマネージャオブジェクトを削除
	DeleteGO(FindGO<BackGround>("backGround")); // 背景オブジェクトを削除
	DeleteGO(FindGO<GameCamera>("GameCamera")); // カメラオブジェクトを削除
}

GameOver::~GameOver()
{
	DeleteGO(gameOverBGM);
}

void GameOver::Update()
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

void GameOver::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
