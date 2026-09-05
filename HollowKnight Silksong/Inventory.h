#pragma once
#include "GameObject.h"
struct item {
	item() {};
	item(const TCHAR* _obj, INT _count, Vector2D _point, ITEM_TYPE _Type, BOOL _IsShaking = false)
		: Count(_count), Position(_point), Type(_Type), Shaking(_IsShaking)
	{
		ZeroMemory(itemObject, sizeof(itemObject));
		lstrcpyW(itemObject, _obj);
	}

	TCHAR		itemObject[32];
	INT			Count;
	Vector2D	Position;
	BOOL		Shaking;
	ITEM_TYPE	Type;
};

class InventoryObject : public GameObject {
public:
	InventoryObject();
	virtual ~InventoryObject();

public:
	void	Initialize()		override;
	int  	Update()			override;
	void	Late_Update()		override;
	void	Render(HDC DC)		override;
	void	Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) override;
	void	Release()			override;

	BOOL	Register_DefaultItem(const TCHAR* _obj, INT _count);

	void	Set_Render_Enable(BOOL _VALUE)	{ Render_Enable = _VALUE; }
	BOOL	Get_Render_Enable()				{ return Render_Enable; }

	void Display_PageIcon(HDC DC);
	void Display_PageBackGround(HDC DC);
	void Display_ItemList(HDC DC);
	void Display_ItemInfo(HDC DC);
	void Display_KeyGuide(HDC DC);

	void Picking_Swap(HDC DC, vector<item*>* _ItemList);
	void Picking_Swap_Armor(HDC DC);

	void Append_MukJu(HDC DC, INT _MJR);

	BOOL ObjectShake(HDC DC, vector<item*>* _ItemList, UINT _HDN, UINT _Time);

	BOOL ObjectArmed(HDC DC, INT _Crest_ItemNumb);

	BOOL SwapMotion(HDC DC, item* itemR, item* itemL);

private:
	vector<item*>	Default_ItemList;
	vector<item*>	Armed_ItemList;
	vector<item*>	Crest_ItemList;

	FLOAT	DistanceStackRX;
	FLOAT	DistanceStackRY;
	FLOAT	DistanceStackLX;
	FLOAT	DistanceStackLY;

	INT		CurrentPickingItem;
	INT		PreviousPickingItem;
	INT		ArmorPickingItem;

	DWORD	dwTime;

	BOOL	Item_SwappingA;
	BOOL	Item_SwappingB;
	BOOL	Show_ErrorMessage;
	BOOL	Render_Enable;

	Vector2D	CameraOffset;
	HFONT	SerifFont;

	UINT	CurrentIcon;
	INT		RandomMukJu;
	INT		RandomStone;
};

