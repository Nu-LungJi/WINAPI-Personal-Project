#pragma once
class BossObject : public GameObject {
public:
	BossObject();
	virtual ~BossObject();

public:
	void Initialize()			override;
	int Update()				override;
	void Late_Update()			override;
	void Render(HDC DC)			override;
	void Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) override;
	void Release()				override;

public:
	void		Boss_GravitySetting();

	void		Boss_Skill_StateMachine();
	void		Boss_StateMachine();

	void		Boss_Skill_Control();
	void		Boss_State_Control();

	void		Boss_Nnock_Back();

	FLOAT		Catch_PlayerPosition() { return Player->Get_Pos().X; }
	BOOL		Boss_Shield() { return TimeDelay; }

	void		Boss_Animation_Dash(HDC DC);
	void		Boss_Animation_Poke(HDC DC);
	void		Boss_Animation_Spin(HDC DC);
	void		Boss_Animation_Land(HDC DC);
	void		Boss_Animation_Splt(HDC DC);
	void		Boss_Animation_Idle(HDC DC);
	void		Boss_Animation_Prng(HDC DC);
	void		Boss_Animation_PATK(HDC DC);
	void		Boss_Animation_ASLH(HDC DC);

	void		Boss_Animation_START(HDC DC);
	void		Boss_Animation_FURY(HDC DC);
	void		Boss_Animation_STUN(HDC DC);
	void		Boss_Animation_DEAD(HDC DC);

	void		Boss_After_DefeatTalk() { Current_State = BOSS_STATE::BOSS_DOWN; }
	void		Flower_Parade();

	BOOL PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);
	void PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD Timer, 
		Vector2D _CenterPos, INT LoopFrame = 0, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);
	void PlayAnimation_Once_Stable(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);


	
private:
	GameObject*			Player;
	FLOAT				PlayerPos;
	INT					PlayerDirection;

	GameObject*			HitBox;
	GameObject*			HitBox_Circle;
	INT					HitBox_Enable;

	FLOAT				BossJumpSpeed;

	FLOAT				Gravity;

	BOOL				GetGravity;
	BOOL				OnUsingSkill;
	BOOL				OnGround;
	BOOL				TimeDelay;
	BOOL				IsDead;
	BOOL				ONHIT;
	INT					BossMovable;

	BOSS_SKILL_STATE			Previous_SkillState;
	BOSS_SKILL_STATE			Current_SkillState;

	BOSS_STATE					Previous_State;
	BOSS_STATE					Current_State;

	DWORD				dwTime[20];
	DWORD				PNGTime;
	DWORD				LoopTime;
	INT					degree;
	INT					Pattern_Selector;

	INT					StartPixelFrame[20];

	BOOL				NnockBacking_R;
	BOOL				NnockBacking_L;
	INT					NnockBack_Value;

	INT					STATE_VALUE;
	INT					Stage_StartTime;
	BOOL				Charging;

	Vector2D			LandStartPoint;
	Vector2D			StunPoint;
	INT					ASLH_Count;
	INT					EffectIndex;

	vector<Vector2D>	FlowerVec;
};

