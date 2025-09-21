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

	DeleteGO(FindGO<Game>("Game")); // �Q�[���I�u�W�F�N�g���폜
	DeleteGO(FindGO<Player>("player")); // �v���C���[�I�u�W�F�N�g���폜
	DeleteGO(FindGO<StageManager>("stageManager")); // �X�e�[�W�}�l�[�W���I�u�W�F�N�g���폜
	DeleteGO(FindGO<BackGround>("backGround")); // �w�i�I�u�W�F�N�g���폜
	DeleteGO(FindGO<GameCamera>("GameCamera")); // �J�����I�u�W�F�N�g���폜
}

GameClear::~GameClear()
{
	DeleteGO(m_gameClearBGM);
}

void GameClear::Update()
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

void GameClear::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
