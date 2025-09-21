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
	SoundSource* titleBGM; // �T�E���h�\�[�X	
	SpriteRender m_pressButton; // �v���X�{�^���̃X�v���C�g�����_�\
	FontRender m_fontRender; // �t�H���g�����_�\
	FontRender m_startText; // �Q�[���J�n�̃e�L�X�g�����_�\
	float m_ghost = 0.4f; // �t�F�[�h�A�E�g�p�̕ϐ�
	bool m_ghostState = false; // �t�F�[�h�A�E�g��Ԃ̃t���O
	bool m_startState = false; // �Q�[���J�n��Ԃ̃t���O
	int m_flash = 0; // �t���b�V���p�̕ϐ�
	int m_count = 0; // �J�E���g�p�̕ϐ�
};

