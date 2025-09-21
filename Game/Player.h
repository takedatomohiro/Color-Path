#pragma once
class Player :public IGameObject
{
	public:
	Player();
	~Player();
	void Update();
	void Move();
	void Rotation();
	void Render(RenderContext& rc);
	void PlayAnimation();
	void ManageState();
//	void ManageJumpState();

	enum EnAnimationClip
	{
		enAnimClip_Idle,
		enAnimClip_Walk,
		enAnimClip_Jump,
		enAnimClip_Run,
		enAnimClip_Num,
	};
	ModelRender m_modelRender;
	AnimationClip animationClips[enAnimClip_Num];
	CharacterController characterController;
	Vector3 m_position;
	Vector3 moveSpeed;
	Quaternion m_rot;
	int JumpCount = 0;
	const int MaxJumpCount = 2;
	int playerState;
	Vector3 firstPos = { 0,0,0 };
	Vector3 startPos;
	Vector3 GetPosition() { return m_position; }
	void SetPosition(Vector3 pos){ m_position = pos; characterController.SetPosition(pos); }
	bool isControlReversed = false; // ”½“]ƒtƒ‰ƒO
};