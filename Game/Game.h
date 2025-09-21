#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class GameCamera;
class StageManager;

class Game : public IGameObject
{
public:
	Game();
	~Game();

	void Update();
	void Render(RenderContext& rc);

private:
	ModelRender m_modelRender;
	Vector3 m_pos;
	float m_timer = 60.0f;
	FontRender m_timeFontRender;
	FontRender m_distance;
	SkyCube* m_skyCube = nullptr;			//空。
	Player* m_player = nullptr;			//プレイヤー。
	BackGround* m_backGround = nullptr;	//背景。
	GameCamera* m_gameCamera = nullptr;	//カメラ。
	StageManager* m_stageManager = nullptr; //ステージマネージャー。
	SoundSource* m_gameBGM = nullptr; // ゲーム中のBGM。
};

