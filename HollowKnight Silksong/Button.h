#pragma once

class ButtonObject : public GameObject	{
public:
	ButtonObject();
	ButtonObject(FLOAT _X, FLOAT _Y, FLOAT _WTH, FLOAT _HGT, const TCHAR* _TW, BTN_TAG _BT = BTN_TAG::BTN_END, UINT _FontSize = 30);
	virtual ~ButtonObject();
public:
	void	Initialize()		override;
	int		Update()			override;
	void	Late_Update()		override;
	void	Render(HDC DC)		override;
	void	Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) override;
	void	Release()			override;

	
public:
	BTN_EVENT	ButtonEvent();

	void		Set_BTNTAG(BTN_TAG _Tag)	{	Button_Tag = _Tag;	}
	BTN_TAG		Get_BTNTAG()				{	return Button_Tag;	}

	void		Set_TextWord(const TCHAR* _TW)		{ wsprintf(TextWord, _TW); }

private:
	BTN_TAG		Button_Tag;
	TCHAR		TextWord[32];
	bool		Test;
	HFONT		SerifFont;
	UINT		FontSize;
};

