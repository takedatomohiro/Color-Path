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
	SkyCube* m_skyCube = nullptr;			//��B
	Player* m_player = nullptr;			//�v���C���[�B
	BackGround* m_backGround = nullptr;	//�w�i�B
	GameCamera* m_gameCamera = nullptr;	//�J�����B
	StageManager* m_stageManager = nullptr; //�X�e�[�W�}�l�[�W���[�B
	SoundSource* m_gameBGM = nullptr; // �Q�[������BGM�B
};

