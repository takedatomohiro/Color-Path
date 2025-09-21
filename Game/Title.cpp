#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"

Title::Title()
{
	spriteRender.Init("Assets/sprite/title.dds",1920.0f, 1080.0f);
	m_fontRender.SetText(L"Press A to Start");
	m_fontRender.SetPosition({ -225.0f, -250.0f,0.0f });
	m_fontRender.SetColor(1.0f, 1.0f, 0.0f, 1.0f); // フォントの色を白に設定
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/title.wav");
	titleBGM = NewGO<SoundSource>(0);
	titleBGM->Init(1);
	titleBGM->Play(true);
}

Title::~Title()
{
	DeleteGO(titleBGM);
}

void Title::Update()
{
	float maxColor = 1.0f;
	float enptyColor = 0.0f;
	float Color = 1.0f;

	if (m_ghost >= maxColor) {
		m_ghost = 1.0f;
	}

	if (m_ghost <= enptyColor) {
		m_ghost = 0.0f;
	}

	if (m_ghost < maxColor and m_ghostState == false) {
		m_ghost += 0.006f; // フェードアウト;
	}

	if (m_ghost >= maxColor) {
		m_ghostState = true; // フェードアウト状態にする
	}

	if (m_ghostState == true) {
		m_ghost -= 0.006f; // フェードイン
		if (m_ghost <= 0.0f) {
			m_ghostState = false; // フェードイン状態にする
		}
	}

	if (m_startState == false) {
		m_fontRender.SetColor({ 0.0f,0.0f,0.0f,m_ghost }); // フェードアウト
	}
	else {
		m_fontRender.SetColor({ 0.0f,0.0f,0.0f,1.0f }); // フェードイン
	}

	m_startText.SetColor({ m_ghost,m_ghost,1.0f,m_ghost });
	if (g_pad[0]->IsTrigger(enButtonA) or m_flash >= 1) {
		if (m_startState == false) {
			m_startText.SetColor({ 1.0f, 1.0f, 0.0f, 1.0f }); // ゲーム開始のテキストを白色に設定
			m_startState = true; // ゲーム開始状態にする
		}
		else {
			m_startText.SetColor({ 0.0f, 0.0f, 0.0f, 0.0f }); // ゲーム開始のテキストを透明に設定
			m_startState = false; // ゲーム開始状態を解除
		}
	}

	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_flash += 1;
	}
	if (m_flash >= 1) {
		bool inGame = true;
		if (inGame = true) {
			m_count += 1;
		}
		if (m_count >= 30) { // 1秒後にゲーム開始
			m_startState = true; // ゲーム開始状態にする
			NewGO<Game>(0, "game");
			DeleteGO(this);
		}
	}

	spriteRender.Update();
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
	m_fontRender.Draw(rc); // フォントの描画
}
