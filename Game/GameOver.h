#pragma once

class Player;
class BackGround;
class StageManager;
class GameCamera;
class Game;
class GameOver :public IGameObject
{
	public:
		GameOver();
		~GameOver();
		void Update()override final;
		void Render(RenderContext& rc)override final;
private:
	SpriteRender spriteRender; // スプライトレンダ―。
	SoundSource* gameOverBGM; // ゲームオーバー時のBGM。
};

