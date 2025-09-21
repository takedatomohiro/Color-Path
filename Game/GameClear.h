#pragma once

class Game;
class Player;
class BackGround;
class StageManager;
class GameCamera;
class red;
class blue;
class purple;
class green;
class GameClear:public IGameObject
{
	public:
		GameClear();
		~GameClear();
		void Update()override final;
		void Render(RenderContext& rc)override final;
	private:
		SpriteRender spriteRender; // スプライトレンダ―。
		SoundSource* m_gameClearBGM; // ゲームクリア時のBGM。
};

