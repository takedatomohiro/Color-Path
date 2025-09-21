#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"

Title::Title()
{
	spriteRender.Init("Assets/sprite/title.dds",1920.0f, 1080.0f);
	m_fontRender.SetText(L"Press A to Start");
	m_fontRender.SetPosition({ -225.0f, -250.0f,0.0f });
	m_fontRender.SetColor(1.0f, 1.0f, 0.0f, 1.0f); // �t�H���g�̐F�𔒂ɐݒ�
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
		m_ghost += 0.006f; // �t�F�[�h�A�E�g;
	}

	if (m_ghost >= maxColor) {
		m_ghostState = true; // �t�F�[�h�A�E�g��Ԃɂ���
	}

	if (m_ghostState == true) {
		m_ghost -= 0.006f; // �t�F�[�h�C��
		if (m_ghost <= 0.0f) {
			m_ghostState = false; // �t�F�[�h�C����Ԃɂ���
		}
	}

	if (m_startState == false) {
		m_fontRender.SetColor({ 0.0f,0.0f,0.0f,m_ghost }); // �t�F�[�h�A�E�g
	}
	else {
		m_fontRender.SetColor({ 0.0f,0.0f,0.0f,1.0f }); // �t�F�[�h�C��
	}

	m_startText.SetColor({ m_ghost,m_ghost,1.0f,m_ghost });
	if (g_pad[0]->IsTrigger(enButtonA) or m_flash >= 1) {
		if (m_startState == false) {
			m_startText.SetColor({ 1.0f, 1.0f, 0.0f, 1.0f }); // �Q�[���J�n�̃e�L�X�g�𔒐F�ɐݒ�
			m_startState = true; // �Q�[���J�n��Ԃɂ���
		}
		else {
			m_startText.SetColor({ 0.0f, 0.0f, 0.0f, 0.0f }); // �Q�[���J�n�̃e�L�X�g�𓧖��ɐݒ�
			m_startState = false; // �Q�[���J�n��Ԃ�����
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
		if (m_count >= 30) { // 1�b��ɃQ�[���J�n
			m_startState = true; // �Q�[���J�n��Ԃɂ���
			NewGO<Game>(0, "game");
			DeleteGO(this);
		}
	}

	spriteRender.Update();
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
	m_fontRender.Draw(rc); // �t�H���g�̕`��
}
