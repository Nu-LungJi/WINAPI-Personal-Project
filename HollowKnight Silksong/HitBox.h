#pragma once
class HitBoxObject : public GameObject {
public:
	void Initialize()																override;
	int  Update()																	override;
	void Late_Update()																override;
	void Render(HDC DC)																override;
	void Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value)		override;
	void Release()																	override;

public:
	void	Activate_HitBox() { HITBOX_CURRENT = true; }
	void	DeActivate_HitBox() { HITBOX_PREVIOUS = false; HITBOX_CURRENT = false; }

	INT		Get_HitBoxDamage() { return HITBOX_DAMAGE; };
	void	Set_HitBoxDamage(INT _Damage) { HITBOX_DAMAGE = _Damage; }

private:

	GameObject* Player;
	GameObject* Boss;

	INT		StartPixelFrame[10];
	DWORD	dwTime;

	HDC MainDC;

	Vector2D	BossPos;
	BOOL		ONHIT;

	BOOL	HITBOX_PREVIOUS;
	BOOL	HITBOX_CURRENT;

	INT		HITBOX_DAMAGE;
};

