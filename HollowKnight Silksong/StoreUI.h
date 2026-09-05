#pragma once

struct Item {
	Item() {}
	Item(const TCHAR* _IIN, const TCHAR* _IPN, const TCHAR* _Name, INT _Price) {
		lstrcpyW(ItemImageName, _IIN);
		lstrcpyW(ItemPriceImageName, _IPN);
		lstrcpyW(ItemName, _Name);
		ItemPrice = _Price;
	}

	TCHAR	ItemImageName[32];
	TCHAR	ItemPriceImageName[32];
	TCHAR	ItemName[32];
	INT		ItemPrice;
};

class StoreUI : public GameObject {
public:
	StoreUI();
	virtual ~StoreUI();

public:
	void	Initialize()			override;
	int		Update()				override;
	void	Late_Update()			override;
	void	Render(HDC DC)			override;
	void	Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) override {};
	void	Release()				override;

public:
	void STORE_DefaultSetting(HDC DC);
	void STORE_SlotAnimation(HDC DC);
	void STORE_BeforePurchase(HDC DC);
	void STORE_CompletePurchase(HDC DC);
	void STORE_DisplayTextAnimation(HDC DC);

	void Set_StoreManager(GameObject* _Manager) { StoreManager = _Manager; }
	void PlayAnimation_Once_Stable(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight);
	void PlayAnimation_Reverse(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
		Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight);
		
private:
	GameObject*			Player;
	GameObject*			StoreManager;

	GameObject*			ButtonYes;
	GameObject*			ButtonNo;
	INT					ButtonIndex;

	vector<Item>		ItemList;

	INT					Open_Store, Close_Store;
	INT					Slot_CurrentIndex, Slot_PastIndex;
	INT					Selecting, Purchasing, Deciding;

	FLOAT				SwingValue;
	BOOL				Swinging;
	BOOL				PayMukJu;
	BOOL				Closing;
	BOOL				Completed;

	DWORD				dwTime;

	HFONT				SerifFont;
	Vector2D			CameraOffset;

	INT					StartPixelFrame[10];
};

