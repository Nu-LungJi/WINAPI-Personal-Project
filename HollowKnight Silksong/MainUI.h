#pragma once
class MainUI : public GameObject {
public:
	MainUI();
	virtual ~MainUI();

public:
	void Initialize()																override;
	int Update()																	override;
	void Late_Update()																override;
	void Render(HDC DC)																override;
	void Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value)		override;
	void Release()																	override;

	void	Append_MukJu_Quantity(HDC DC, INT* _EA);

	void	Append_Stone_Quantity(INT* _Stone, INT _EA);
	void	Append_HP_Quantity(INT* _HP, INT _EA);
	void	Append_Silk_Quantity(INT* _Silk, INT _EA);

	void	Remove_MukJu_Quantity(INT* _MukJu, INT _EA);
	void	Remove_Stone_Quantity(INT* _Stone, INT _EA);
	void	Remove_HP_Quantity(INT* _HP, INT _EA);
	void	Remove_Silk_Quantity(INT* _Silk, INT _EA);

	BOOL PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight);

	void Set_Render_Enable(BOOL _VALUE) { Render_Enable = _VALUE; }
	BOOL Get_Render_Enable()			{ return Render_Enable; }

	void Set_MukJuQuantity_ToAppend(INT _VALUE) { MukJuQuantity_ToAppend = _VALUE; }
	void Set_StoneQuantity_ToAppend(INT _VALUE) { StoneQuantity_ToAppend = _VALUE; }
private:
	GameObject*		Player;

	INT				HP_INFO[10];

	INT				Silk_INFO[15];

	TCHAR			CoinText[16];

	INT				MukJu_Quantity;
	BOOL			MukJu_Appended;

	INT				Stone_Quantity;
	BOOL			Stone_Appended;

	INT				Silk_Quantity;
	INT				HP_Quantity;
	BOOL			AnimEscape;

	DWORD			dwTime[10];

	INT				StartPixelFrame;

	BOOL			Render_Enable;

	INT				MukJuQuantity_ToAppend;
	INT				StoneQuantity_ToAppend;
};

