#pragma once
class GameObject abstract {
public:
	GameObject();
	virtual ~GameObject();

public:
	virtual void	Initialize()		= 0;
	virtual int	    Update()			= 0;
	virtual void	Late_Update()		= 0;
	virtual void	Render(HDC DC)		= 0;
	virtual void	Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value)	= 0;
	virtual void	Release()			= 0;

public:
	const RECT*		Get_Rect() { return &OBJRECT; }
	const INFO*		Get_Info() { return &OBJINFO; }

	void			Set_Info(FLOAT _CPX, FLOAT _CPY, FLOAT _Width, FLOAT _Height) { OBJINFO = { _CPX , _CPY, _Width, _Height }; }

	void			Set_Pos(FLOAT _CPX, FLOAT _CPY)			{ OBJINFO.CenterPosX = _CPX; OBJINFO.CenterPosY = _CPY;	}
	void			Set_PosX(FLOAT _CPX) { OBJINFO.CenterPosX += _CPX; }
	void			Set_PosY(FLOAT _CPY) { OBJINFO.CenterPosY += _CPY; }

 	Vector2D		Get_Pos() { return { OBJINFO.CenterPosX, OBJINFO.CenterPosY }; }
	void			Set_Scale(FLOAT _Width, FLOAT _Height)	{ OBJINFO.Width = _Width;	 OBJINFO.Height = _Height;	}
	
	void			Set_Tag(OBJECT_TAG _Tag) { OBJTAG = _Tag; }
	OBJECT_TAG		Get_Tag() { return OBJTAG; }

	void			Set_HP(INT _HP) { OBJHP = _HP; }
	INT				Get_HP()		{ return OBJHP; }

	void			Set_Dead(BOOL	_DEAD) { DEAD = _DEAD; }
	BOOL			GET_DEAD() { return DEAD; }

	void			Set_Damage(INT _DMG) { OBJDMG = _DMG; }
	INT				Get_Damage() { return OBJDMG; }
public:
	void Update_RECT();
	
protected:
	INFO		OBJINFO;
	RECT		OBJRECT;
	OBJECT_TAG	OBJTAG;

	INT			OBJHP;
	INT			OBJDMG;
	BOOL		DEAD;
};

