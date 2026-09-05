#pragma once
class SkillObject : public GameObject {
public:
	SkillObject();
	virtual ~SkillObject();

public:
	void	Initialize()			override;
	int		Update()				override;
	void	Late_Update()			override;
	void	Render(HDC DC)			override;
	void	Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) override;
	void	Release()				override;

public:
	void PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer, INT LoopFrame,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);

	BOOL PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer,
		Vector2D _CenterPos, FLOAT _MultipleWidth = 1, FLOAT _MultipleHeight = 1);

	void GravitySetting();
	void MoveDrill();

private:
	DWORD	dwTime[10];
	FLOAT	Angle;

	GameObject* Player;
	INT		PlayerDirection;
	INT		StartPixelFrame[10];
	FLOAT	ObjectJumpSpeed;

	Vector2D	MonsterPos;

	BOOL	GetGravity;
	BOOL	ONGROUND;
	BOOL	ONHIT;
};

