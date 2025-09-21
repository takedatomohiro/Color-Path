#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "StageManager.h"
#include "GameOver.h"
#include "GameClear.h"

Game::Game()
{
	m_player=NewGO<Player>(0, "player");
	m_gameCamera=NewGO<GameCamera>(0, "gameCamera");
	m_backGround=NewGO<BackGround>(0, "backGround");
	m_stageManager=NewGO<StageManager>(0, "stageManager");

	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetType(nsK2Engine::enSkyCubeType_Night);

	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/game.wav");
	m_gameBGM = NewGO<SoundSource>(0);
	m_gameBGM->Init(3);
	m_gameBGM->Play(true);
}

Game::~Game()
{
	DeleteGO(m_player); // プレイヤーオブジェクトを削除
	DeleteGO(m_stageManager); // ステージマネージャオブジェクトを削除
	DeleteGO(m_backGround); // 背景オブジェクトを削除
	DeleteGO(m_gameCamera); // カメラオブジェクトを削除
	DeleteGO(m_gameBGM); // ゲーム中のBGMオブジェクトを削除
}

void Game::Update()
{
	int minute = (int)m_timer / 60;
	int sec = (int)m_timer % 60;

	wchar_t text[256];
	swprintf_s(text, 256, L"%02d:%02d", minute, sec);
	m_timeFontRender.SetText(text);
	//文字の座標
	m_timeFontRender.SetPosition(-100.0f, 500.0f, 0.0f);
	//文字の大きさ
	m_timeFontRender.SetScale(2.0f);
	//文字の色
	m_timeFontRender.SetColor(g_vec4White);

	m_timer -= g_gameTime->GetFrameDeltaTime();

	if (m_timer < 0.0f)
	{
		m_timer = 0.0f;
		NewGO<GameOver>(0, "gameOver");
		DeleteGO(this);
		return;
	}

	if (m_player->m_position.z < -3370.0f)
	{
		NewGO<GameClear>(0, "gameClear");
		DeleteGO(this);
		return;
	}
}

void Game::Render(RenderContext& rc)
{
	m_timeFontRender.Draw(rc);
}