#pragma once
#include "GameObject.h"
class PlayerObject : public GameObject	{
public:
	PlayerObject();
	virtual ~PlayerObject();

public:
	void	Initialize() override;
	int		Update() override;
	void	Late_Update() override;
	void	Render(HDC DC) override;
	void	Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) override;
	void	Release() override;

public:
	void Player_Control();
	void Player_Animation(HDC DC);
	void Player_StateMachine();
	void Player_JumpDirection_Transition();

	void Player_NormalAttack();
	void Player_SkillAttack();

	void Player_Animation_Attack(HDC DC);
	void Player_Animation_Dash(HDC DC);
	void Player_Animation_Jump(HDC DC);
	void Player_Animation_MoveMent(HDC DC);
	void Player_Animation_OnHitState(HDC DC);
	void Player_Animation_ThreadSKILL(HDC DC);
	void Player_Animation_HealSKILL(HDC DC);
	void Player_Animation_Throw(HDC DC);

	void Player_GravitySetting();

	void	Set_JumpState(PLAYER_JUMP_STATE _PJS) { Current_JumpState = _PJS; }
	void	Set_JumpSpeed(FLOAT _Value) { PlayerJumpSpeed = _Value; }
	FLOAT	Get_JumpSpeed() { return PlayerJumpSpeed; }

	void	Get_Gravity() { OBJINFO.CenterPosY -= PlayerJumpSpeed; }

	FLOAT	Get_PlayerDirection() { return PlayerDirection; }
	
	INT		Get_MukJu()			{ return MukJu; }
	INT		Get_SilverStone()	{ return SilverStone; }
	INT		Get_Silk()			{ return SILK; }

	void	Set_MukJu(INT	_MJ)	{ MukJu = _MJ; }
	void	Set_SilverStone(INT _SS)		{ SilverStone = _SS; }
	void	Set_Silk(INT _SK)				{ SILK = _SK; }

	void	Set_Infinity(BOOL _INF) { Player_Infinity_Enable = _INF; }
	BOOL	Get_Infinity() { return Player_Infinity_Enable; }

	void	Set_PlayerSpeed(INT _VALUE) { PlayerSpeed = _VALUE; }

	void	Set_UIVisibility(BOOL _VALUE) { MainUI_Enable = _VALUE; }
	void	Set_PlayerDefaultState(PLAYER_DEFAULT_STATE _PDS) { Current_DefaultState = _PDS; }
	void	Set_PlayerMoveState(PLAYER_MOVE_STATE _PMS) { Current_MovementState = _PMS; }
	void	Set_PlayerPreviousMoveState(PLAYER_MOVE_STATE _PMS) { Previous_MovementState = _PMS; }

	PLAYER_ATTACK_STATE Get_PlayerAttackState() { return Current_AttackState; }

	void	Set_PlayerJumpState(INT _VALUE) { PlayerMovable = _VALUE; }

	void	Set_PlayerRender(BOOL _VALUE) { Player_Render = _VALUE; }

	GameObject* Get_Inventory() { return Inventory; }

	void PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);

	BOOL PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);

	GameObject* Get_PlayerMainUI() { return PlayerMainUI; }

private:
	GameObject*		Inventory;
	INT				Inventory_Enable;

	GameObject*		HitBox;
	INT				HitBox_Enable;

	GameObject*		PlayerMainUI;
	INT				MainUI_Enable;

	FLOAT			PlayerSpeed;
	FLOAT			PlayerPastDirection;
	FLOAT			PlayerDirection;
	INT				PlayerJumpCount;

	FLOAT			PlayerJumpSpeed;

	INT				PlayerFace;
	INT				PlayerLastFace;
	INT				PlayerMovable;
	INT				effectIndex;

	BOOL			GetGravity;
	BOOL			Player_Damaged;
	BOOL			Player_Infinity_Enable;
	BOOL			Player_Render;

	PLAYER_MOVE_STATE				Previous_MovementState;
	PLAYER_MOVE_STATE				Current_MovementState;

	PLAYER_JUMP_STATE				Previous_JumpState;
	PLAYER_JUMP_STATE				Current_JumpState;

	PLAYER_ATTACK_STATE				Previous_AttackState;
	PLAYER_ATTACK_STATE				Current_AttackState;

	PLAYER_SKILL_STATE				Previous_SkillState;
	PLAYER_SKILL_STATE				Current_SkillState;

	PLAYER_DEFAULT_STATE				Previous_DefaultState;
	PLAYER_DEFAULT_STATE				Current_DefaultState;

	INT			MukJu;
	INT			SilverStone;
	INT			SILK;

	FLOAT		Gravity;
	DWORD		dwTime[10];
	DWORD		InfinityTime;

	INT			StartPixelIndex[10];
	INT			SkillRoutine;
	BOOL		OnGround;

	Vector2D	PlayerEffectPos;

	/////////////////////////////////////// GDI
	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	Image* image[50];
	int idx = 0;

};

