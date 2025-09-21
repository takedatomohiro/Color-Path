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

	DeleteGO(FindGO<Game>("Game")); // �Q�[���I�u�W�F�N�g���폜
	DeleteGO(FindGO<Player>("player")); // �v���C���[�I�u�W�F�N�g���폜
	DeleteGO(FindGO<StageManager>("stageManager")); // �X�e�[�W�}�l�[�W���I�u�W�F�N�g���폜
	DeleteGO(FindGO<BackGround>("backGround")); // �w�i�I�u�W�F�N�g���폜
	DeleteGO(FindGO<GameCamera>("GameCamera")); // �J�����I�u�W�F�N�g���폜
}

GameOver::~GameOver()
{
	DeleteGO(gameOverBGM);
}

void GameOver::Update()
{
	//A�{�^���������ꂽ��B
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//�^�C�g���̃I�u�W�F�N�g������B
		NewGO<Title>(0, "title");
		//���g���폜����B
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
