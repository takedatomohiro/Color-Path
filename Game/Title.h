#pragma once
#include "sound/SoundSource.h"
class Game;
class Title : public IGameObject
{
	public:
	Title();
	~Title();

	void Update()override final;

	void Render(RenderContext& rc)override final;

	SpriteRender spriteRender;
	SoundSource* titleBGM; // サウンドソース	
	SpriteRender m_pressButton; // プレスボタンのスプライトレンダ―
	FontRender m_fontRender; // フォントレンダ―
	FontRender m_startText; // ゲーム開始のテキストレンダ―
	float m_ghost = 0.4f; // フェードアウト用の変数
	bool m_ghostState = false; // フェードアウト状態のフラグ
	bool m_startState = false; // ゲーム開始状態のフラグ
	int m_flash = 0; // フラッシュ用の変数
	int m_count = 0; // カウント用の変数
};

