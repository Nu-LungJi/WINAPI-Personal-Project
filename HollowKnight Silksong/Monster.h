#pragma once
#include "GameObject.h"

enum class MONSTER_TYPE{ MONSTER_ENVOY, MONSTER_CHAMBER };

class MonsterObject : public GameObject {
public:
	MonsterObject();
	virtual ~MonsterObject();
public:
	void Initialize()			override;
	int Update()				override;
	void Late_Update()			override;
	void Render(HDC DC)			override;
	void Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) override;
	void Release()				override;

public:
	void Monster_GravitySetting();
	void Monster_StateMachine();
	void Monster_Control();

	void Monster_Animation_IDLE(HDC DC);
	void Monster_Animation_WALK(HDC DC);
	void Monster_Animation_ATTK(HDC DC);
	void Monster_Animation_DEAD(HDC DC);

	Vector2D	Check_Distance_Player() 
		{ return { fabsf(OBJINFO.CenterPosX - Player->Get_Info()->CenterPosX), fabsf(OBJINFO.CenterPosY - Player->Get_Info()->CenterPosY) }; }

	void	Set_MonsterType(MONSTER_TYPE _MTYPE) { Monster_Type = _MTYPE; }

public:
	BOOL PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);
	void PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);
	void PlayAnimation_Once_Stable(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);

private:
	FLOAT	MonsterSpeed;
	FLOAT	MonsterJumpSpeed;
	INT		MonsterDirection;

	GameObject* MonsterHitBox;
	GameObject* Player;

	MONSTER_STATE Previous_State;
	MONSTER_STATE Current_State;

	BOOL	Previous_HitState;
	BOOL	Current_HitState;

	MONSTER_TYPE  Monster_Type;

	INT		StartPixelFrame[10];

	FLOAT		Angle;
	BOOL		ONHIT;
	BOOL		ONGROUND;

	BOOL		PlayerCurrent_AttackState;
	BOOL		PlayerPrevious_AttackState;

	BOOL		Gravity_Enable;
	BOOL		Catch_Player;
	BOOL		Death_Sound;
	FLOAT		Player_CatchRange;

	DWORD		dwTime[10];
	DWORD		AnimationTime;
	FLOAT		Action_Transition_Time;
};

