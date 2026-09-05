#pragma once
class Panel : public GameObject {
public:
	Panel();
	Panel(FLOAT _X, FLOAT _Y, FLOAT _WTH, FLOAT _HGT, const TCHAR* _TW, UINT _FontSize);
	virtual ~Panel();
public:
	void Initialize()		override;
	void Update()			override;
	void Late_Update()		override;
	void Render(HDC DC)		override;
	void Release()			override;

public:
	void Change_FontSize(UINT	_Size);

private:
	TCHAR		TextWord[10];
	BOOL		SelectFont;
	HFONT		SerifFont;
	UINT		FontSize;
};

