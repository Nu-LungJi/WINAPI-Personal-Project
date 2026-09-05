#include "PCH.h"
#include "Inventory.h"

InventoryObject::InventoryObject()
	: CurrentIcon(1), CurrentPickingItem(0), PreviousPickingItem(0), ArmorPickingItem(0), dwTime(GetTickCount()), RandomMukJu(0), RandomStone(0),
	DistanceStackRX(0), DistanceStackRY(0), DistanceStackLX(0), DistanceStackLY(0), Item_SwappingA(false), Item_SwappingB(false), Show_ErrorMessage(false), Render_Enable(false){}
InventoryObject::~InventoryObject() { Release(); }

void InventoryObject::Initialize()
{
	SerifFont = CreateFont(25, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("SourceHanSerif-Light"));

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Back01.bmp",						L"Back01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Back02.bmp",						L"Back02");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_ItemSelectorR.bmp",			L"SelectorR");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_ItemSelectorL.bmp",			L"SelectorL");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_Attribute_01.bmp",			L"Inven_Attribute01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_Attribute_02.bmp",			L"Inven_Attribute02");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Ring.bmp",							L"Ring");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Ring_Red.bmp",						L"RingR");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Ring_Blue.bmp",					L"RingB");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Ring_Yellow.bmp",					L"RingY");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/4Arrow_KeySet.bmp",				L"Key_4Arrow");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/2Arrow_KeySet.bmp",				L"Key_2Arrow");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/ZKeySet.bmp",						L"Key_Z");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/XKeySet.bmp",						L"Key_X");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/NonUsableTotem01.bmp",					L"NTotem01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/NonUsableTotem02.bmp",					L"NTotem02");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/NonUsableTotem03.bmp",					L"NTotem03");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/NonUsableTotem04.bmp",					L"NTotem04");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/UsableTotem01.bmp",					L"UTotem01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/UsableTotem02.bmp",					L"UTotem02");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/UsableTotem03.bmp",					L"UTotem03");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/UsableTotem04.bmp",					L"UTotem04");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_Icon_01.bmp",				L"Icon_01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_Icon_02.bmp",				L"Icon_02");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_Icon_03.bmp",				L"Icon_03");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_Icon_04.bmp",				L"Icon_04");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_Icon_05.bmp",				L"Icon_05");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_Icon_01_Disable.bmp",		L"Icon_01_Disable");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_Icon_02_Disable.bmp",		L"Icon_02_Disable");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_Icon_03_Disable.bmp",		L"Icon_03_Disable");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_Icon_04_Disable.bmp",		L"Icon_04_Disable");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_Icon_05_Disable.bmp",		L"Icon_05_Disable");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_SmallArrowR.bmp",			L"ArrowR");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/InvenSetting/Inven_SmallArrowL.bmp",			L"ArrowL");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Weapon01.bmp",							L"Weapon01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Weapon02.bmp",							L"Weapon02");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Weapon03.bmp",							L"Weapon03");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Weapon04.bmp",							L"Weapon04");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Shield01.bmp",							L"Shield01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Shield02.bmp",							L"Shield02");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Shield03.bmp",							L"Shield03");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Util01.bmp",							L"Util01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Util02.bmp",							L"Util02");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Util03.bmp",							L"Util03");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Armed01.bmp",							L"Armed01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Armed02.bmp",							L"Armed02");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Armed03.bmp",							L"Armed03");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Armed04.bmp",							L"Armed04");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Armed05.bmp",							L"Armed05");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Inventory/ItemList/Armed06.bmp",							L"Armed06");

	Default_ItemList.push_back(new item(L"NTotem01", 1, { DEFAULT_WINDOW_CX / 2.f - 170.f,	DEFAULT_WINDOW_CY / 2.f - 170.f }, ITEM_TYPE::ITEM_DEFAULT));
	Default_ItemList.push_back(new item(L"NTotem02", 1, { DEFAULT_WINDOW_CX / 2.f - 85.f ,	DEFAULT_WINDOW_CY / 2.f - 170.f }, ITEM_TYPE::ITEM_DEFAULT));
	Default_ItemList.push_back(new item(L"NTotem03", 1, { DEFAULT_WINDOW_CX / 2.f 	     ,	DEFAULT_WINDOW_CY / 2.f - 170.f }, ITEM_TYPE::ITEM_DEFAULT));
	Default_ItemList.push_back(new item(L"NTotem04", 1, { DEFAULT_WINDOW_CX / 2.f + 85.f ,	DEFAULT_WINDOW_CY / 2.f - 170.f }, ITEM_TYPE::ITEM_DEFAULT));
	Default_ItemList.push_back(new item(L"", 0, { DEFAULT_WINDOW_CX / 2.f + 170.f,	DEFAULT_WINDOW_CY / 2.f - 170.f }, ITEM_TYPE::ITEM_DEFAULT));

	Default_ItemList.push_back(new item(L"", 0, { DEFAULT_WINDOW_CX / 2.f - 170.f,	DEFAULT_WINDOW_CY / 2.f - 85.f }, ITEM_TYPE::ITEM_DEFAULT));
	Default_ItemList.push_back(new item(L"", 0, { DEFAULT_WINDOW_CX / 2.f - 85.f ,	DEFAULT_WINDOW_CY / 2.f - 85.f }, ITEM_TYPE::ITEM_DEFAULT));
	Default_ItemList.push_back(new item(L"", 0, { DEFAULT_WINDOW_CX / 2.f 	     ,	DEFAULT_WINDOW_CY / 2.f - 85.f }, ITEM_TYPE::ITEM_DEFAULT));
	Default_ItemList.push_back(new item(L"", 0, { DEFAULT_WINDOW_CX / 2.f + 85.f ,	DEFAULT_WINDOW_CY / 2.f - 85.f }, ITEM_TYPE::ITEM_DEFAULT));
	Default_ItemList.push_back(new item(L"", 0, { DEFAULT_WINDOW_CX / 2.f + 170.f,	DEFAULT_WINDOW_CY / 2.f - 85.f }, ITEM_TYPE::ITEM_DEFAULT));

///////////////////////////////////////////////////////// Default Item ///////////////////////////////////////////////////////////////////

	Default_ItemList.push_back(new item(L"UTotem01", 1, { DEFAULT_WINDOW_CX / 2.f - 170.f,	DEFAULT_WINDOW_CY / 2.f + 50.f }, ITEM_TYPE::ITEM_USABLE));
	Default_ItemList.push_back(new item(L"UTotem02", 1, { DEFAULT_WINDOW_CX / 2.f - 85.f ,	DEFAULT_WINDOW_CY / 2.f + 50.f }, ITEM_TYPE::ITEM_USABLE));
	Default_ItemList.push_back(new item(L"UTotem03", 1, { DEFAULT_WINDOW_CX / 2.f 	   ,	DEFAULT_WINDOW_CY / 2.f + 50.f }, ITEM_TYPE::ITEM_USABLE));
	Default_ItemList.push_back(new item(L"UTotem04", 1, { DEFAULT_WINDOW_CX / 2.f + 85.f ,	DEFAULT_WINDOW_CY / 2.f + 50.f }, ITEM_TYPE::ITEM_USABLE));
	Default_ItemList.push_back(new item(L"", 0, { DEFAULT_WINDOW_CX / 2.f + 170.f,	DEFAULT_WINDOW_CY / 2.f + 50.f }, ITEM_TYPE::ITEM_END));

	Default_ItemList.push_back(new item(L"", 0, { DEFAULT_WINDOW_CX / 2.f - 170.f,	DEFAULT_WINDOW_CY / 2.f + 135.f }, ITEM_TYPE::ITEM_END));
	Default_ItemList.push_back(new item(L"", 0, { DEFAULT_WINDOW_CX / 2.f - 85.f ,	DEFAULT_WINDOW_CY / 2.f + 135.f }, ITEM_TYPE::ITEM_END));
	Default_ItemList.push_back(new item(L"", 0, { DEFAULT_WINDOW_CX / 2.f 	   ,	DEFAULT_WINDOW_CY / 2.f + 135.f }, ITEM_TYPE::ITEM_END));
	Default_ItemList.push_back(new item(L"", 0, { DEFAULT_WINDOW_CX / 2.f + 85.f ,	DEFAULT_WINDOW_CY / 2.f + 135.f }, ITEM_TYPE::ITEM_END));
	Default_ItemList.push_back(new item(L"", 0, { DEFAULT_WINDOW_CX / 2.f + 170.f,	DEFAULT_WINDOW_CY / 2.f + 135.f }, ITEM_TYPE::ITEM_END));

	Armed_ItemList.push_back(new item(L"Armed01", 1, { 348.f, 245.f }, ITEM_TYPE::ITEM_WEAPON));
	Armed_ItemList.push_back(new item(L"Armed02", 1, { 451.f, 297.f }, ITEM_TYPE::ITEM_WEAPON));
	Armed_ItemList.push_back(new item(L"Armed04", 1, { 451.f, 406.f }, ITEM_TYPE::ITEM_SHIELD));
	Armed_ItemList.push_back(new item(L"Armed06", 1, { 348.f, 458.f }, ITEM_TYPE::ITEM_UTIL));
	Armed_ItemList.push_back(new item(L"Armed05", 1, { 246.f, 406.f }, ITEM_TYPE::ITEM_SHIELD));
	Armed_ItemList.push_back(new item(L"Armed03", 1, { 246.f, 297.f }, ITEM_TYPE::ITEM_WEAPON));

	Crest_ItemList.push_back(new item(L"Weapon01", 1, { DEFAULT_WINDOW_CX / 2.f		   ,	DEFAULT_WINDOW_CY / 2.f - 170.f },	ITEM_TYPE::ITEM_WEAPON));
	Crest_ItemList.push_back(new item(L"Weapon02", 1, { DEFAULT_WINDOW_CX / 2.f + 85.f ,	DEFAULT_WINDOW_CY / 2.f - 170.f },	ITEM_TYPE::ITEM_WEAPON));
	Crest_ItemList.push_back(new item(L"Weapon03", 1, { DEFAULT_WINDOW_CX / 2.f + 170.f,	DEFAULT_WINDOW_CY / 2.f - 170.f },	ITEM_TYPE::ITEM_WEAPON));
																															 
	Crest_ItemList.push_back(new item(L"Weapon04", 1, { DEFAULT_WINDOW_CX / 2.f		   ,	DEFAULT_WINDOW_CY / 2.f - 85.f },	ITEM_TYPE::ITEM_WEAPON));
	Crest_ItemList.push_back(new item(L"", 0, { DEFAULT_WINDOW_CX / 2.f + 85.f ,			DEFAULT_WINDOW_CY / 2.f - 85.f },	ITEM_TYPE::ITEM_END));
	Crest_ItemList.push_back(new item(L"", 0, { DEFAULT_WINDOW_CX / 2.f + 170.f ,			DEFAULT_WINDOW_CY / 2.f - 85.f },	ITEM_TYPE::ITEM_END));

	Crest_ItemList.push_back(new item(L"Shield01", 1, { DEFAULT_WINDOW_CX / 2.f		   ,	DEFAULT_WINDOW_CY / 2.f + 40.f },	ITEM_TYPE::ITEM_SHIELD));
	Crest_ItemList.push_back(new item(L"Shield02", 1, { DEFAULT_WINDOW_CX / 2.f + 85.f ,	DEFAULT_WINDOW_CY / 2.f + 40.f },	ITEM_TYPE::ITEM_SHIELD));
	Crest_ItemList.push_back(new item(L"Shield03", 1, { DEFAULT_WINDOW_CX / 2.f + 170.f ,	DEFAULT_WINDOW_CY / 2.f + 40.f },	ITEM_TYPE::ITEM_SHIELD));

	Crest_ItemList.push_back(new item(L"Util01", 1, { DEFAULT_WINDOW_CX / 2.f		   ,	DEFAULT_WINDOW_CY / 2.f + 165.f },	ITEM_TYPE::ITEM_UTIL));
	Crest_ItemList.push_back(new item(L"Util02", 1, { DEFAULT_WINDOW_CX / 2.f + 85.f ,		DEFAULT_WINDOW_CY / 2.f + 165.f },	ITEM_TYPE::ITEM_UTIL));
	Crest_ItemList.push_back(new item(L"Util03", 1, { DEFAULT_WINDOW_CX / 2.f + 170.f ,		DEFAULT_WINDOW_CY / 2.f + 165.f },	ITEM_TYPE::ITEM_UTIL));
}
int  InventoryObject::Update() {
	if (Render_Enable) {
		if (KEY_COMMAND(KEY::F1, KEY_STATE::DOWN)) { CurrentIcon = 1; CurrentPickingItem = 0; PreviousPickingItem = 0; }
		if (KEY_COMMAND(KEY::F2, KEY_STATE::DOWN)) { CurrentIcon = 2; CurrentPickingItem = 0; PreviousPickingItem = 0; }
		if (KEY_COMMAND(KEY::F3, KEY_STATE::DOWN)) { CurrentIcon = 3; CurrentPickingItem = 0; PreviousPickingItem = 0; }
		if (KEY_COMMAND(KEY::F4, KEY_STATE::DOWN)) { CurrentIcon = 4; CurrentPickingItem = 0; PreviousPickingItem = 0; }

		if (KEY_COMMAND(KEY::P, KEY_STATE::DOWN)) { Register_DefaultItem(L"Totem02", 1); }
		CameraOffset = CameraManager::Get_Instance()->GetOffset();
	}

	return OBJ_ALIVE;
}
void InventoryObject::Late_Update()
{
	
}
void InventoryObject::Render(HDC DC) {
	if (Render_Enable) {
		Display_PageBackGround(DC);
		Display_PageIcon(DC);
		Display_ItemList(DC);
		Display_KeyGuide(DC);
		Display_ItemInfo(DC);
	}
}
void InventoryObject::Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value)
{
}
void InventoryObject::Release() {
	SAFE_DELETE_VEC(Default_ItemList);
	SAFE_DELETE_VEC(Armed_ItemList);
	SAFE_DELETE_VEC(Crest_ItemList);
}

BOOL InventoryObject::Register_DefaultItem(const TCHAR* _obj, INT _count) {
	TCHAR Register_item_Name[32]{0};
	lstrcpyW(Register_item_Name, _obj);
	for (int i = 0; i < Default_ItemList.size(); ++i) {
		if (wcsncmp(Default_ItemList[i]->itemObject, Register_item_Name, sizeof(Register_item_Name)) == 1) {
			Default_ItemList[i]->Count++;
			return true;
		}
	}
	for (int i = 10; i < Default_ItemList.size(); ++i) {
		if (Default_ItemList[i]->Count < 1) {
			lstrcpyW(Default_ItemList[i]->itemObject, _obj);
			Default_ItemList[i]->Count = _count;
			Default_ItemList[i]->Type = ITEM_TYPE::ITEM_USABLE;
			return true;
		}
	}
	return false;
}

void InventoryObject::Display_PageIcon(HDC DC) {
	FileManager::Get_Instance()->Append_Image(DC, L"ArrowL", { DEFAULT_WINDOW_CX / 2.f + 60.f + CameraOffset.X,  75.f + CameraOffset.Y }, 0.6f, 0.6f);
	FileManager::Get_Instance()->Append_Image(DC, L"ArrowR", { DEFAULT_WINDOW_CX / 2.f + 420.f + CameraOffset.X,  75.f + CameraOffset.Y}, 0.6f, 0.6f);

	if (CurrentIcon == 1)	FileManager::Get_Instance()->Append_Image(DC, L"Icon_01", { DEFAULT_WINDOW_CX / 2.f + 120.f + CameraOffset.X,  75.f +CameraOffset.Y }, 0.4f, 0.4f);
	else					FileManager::Get_Instance()->Append_Image(DC, L"Icon_01_Disable", { DEFAULT_WINDOW_CX / 2.f + 120.f + CameraOffset.X,  75.f + CameraOffset.Y}, 0.4f, 0.4f);

	if (CurrentIcon == 2)	FileManager::Get_Instance()->Append_Image(DC, L"Icon_02", { DEFAULT_WINDOW_CX / 2.f + 180.f + CameraOffset.X,  75.f +CameraOffset.Y }, 0.4f, 0.4f);
	else					FileManager::Get_Instance()->Append_Image(DC, L"Icon_02_Disable", { DEFAULT_WINDOW_CX / 2.f + 180.f + CameraOffset.X,  75.f + CameraOffset.Y }, 0.4f, 0.4f);

	if (CurrentIcon == 3)	FileManager::Get_Instance()->Append_Image(DC, L"Icon_03", { DEFAULT_WINDOW_CX / 2.f + 240.f + CameraOffset.X,  75.f + CameraOffset.Y }, 0.4f, 0.4f);
	else					FileManager::Get_Instance()->Append_Image(DC, L"Icon_03_Disable", { DEFAULT_WINDOW_CX / 2.f + 240.f + CameraOffset.X,  75.f + CameraOffset.Y }, 0.4f, 0.4f);

	if (CurrentIcon == 4)	FileManager::Get_Instance()->Append_Image(DC, L"Icon_04", { DEFAULT_WINDOW_CX / 2.f + 300.f + CameraOffset.X,  75.f + CameraOffset.Y }, 0.4f, 0.4f);
	else					FileManager::Get_Instance()->Append_Image(DC, L"Icon_04_Disable", { DEFAULT_WINDOW_CX / 2.f + 300.f + CameraOffset.X,  75.f + CameraOffset.Y }, 0.4f, 0.4f);

	//if (CurrentIcon == 5)	FileManager::Get_Instance()->Append_Image(DC, L"Icon_05", { DEFAULT_WINDOW_CX / 2.f + 360.f,  75.f }, 0.4f, 0.4f);
	//else					
	FileManager::Get_Instance()->Append_Image(DC, L"Icon_05_Disable", { DEFAULT_WINDOW_CX / 2.f + 360.f + CameraOffset.X,  75.f + CameraOffset.Y }, 0.4f, 0.4f);

}
void InventoryObject::Display_PageBackGround(HDC DC) {
	if (CurrentIcon == 1) {
		FileManager::Get_Instance()->Append_Image(DC, L"Back01", { DEFAULT_WINDOW_CX / 2.f + CameraOffset.X,  DEFAULT_WINDOW_CY / 2.f + CameraOffset.Y });
	}
	else if (CurrentIcon == 2) {
		FileManager::Get_Instance()->Append_Image(DC, L"Back02", { DEFAULT_WINDOW_CX / 2.f + CameraOffset.X,  DEFAULT_WINDOW_CY / 2.f + CameraOffset.Y });
		FileManager::Get_Instance()->Append_Image(DC, L"Ring", { 351.f + CameraOffset.X,  351.f + CameraOffset.Y }, 0.5f, 0.5f);

		FileManager::Get_Instance()->Append_Image(DC, L"RingR", { 348.f+ CameraOffset.X, 245.f + CameraOffset.Y}, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"RingR", { 246.f+ CameraOffset.X, 297.f + CameraOffset.Y}, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"RingR", { 451.f+ CameraOffset.X, 297.f + CameraOffset.Y}, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"RingB", { 246.f+ CameraOffset.X, 406.f + CameraOffset.Y}, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"RingB", { 451.f+ CameraOffset.X, 406.f + CameraOffset.Y}, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"RingY", { 348.f+ CameraOffset.X, 458.f + CameraOffset.Y}, 0.5f, 0.5f);
		
		FileManager::Get_Instance()->Append_Image(DC, L"Inven_Attribute01", { DEFAULT_WINDOW_CX / 2.f + 85.f + CameraOffset.X , DEFAULT_WINDOW_CY / 2.f - 30.f + CameraOffset.Y }, 0.8f, 0.8f);
		FileManager::Get_Instance()->Append_Image(DC, L"Inven_Attribute02", { DEFAULT_WINDOW_CX / 2.f + 85.f + CameraOffset.X, DEFAULT_WINDOW_CY / 2.f + 110.f + CameraOffset.Y }, 0.75f, 0.75f);
	}
}
void InventoryObject::Display_ItemList(HDC DC) {
	if (CurrentIcon == 1) {
		for (auto& DI : Default_ItemList) {
			if (DI->Count > 0 && !DI->Shaking)
				FileManager::Get_Instance()->Append_Image(DC, DI->itemObject, DI->Position + CameraOffset, 0.5f, 0.5f);
		}
		Picking_Swap(DC, &Default_ItemList);
		if (ObjectShake(DC, &Default_ItemList, 5, 1000)) {
			dwTime = GetTickCount();
			RandomStone += rand() % 30 + 10;
			srand((UINT)time(NULL));
			RandomMukJu += rand() % 30 + 10;
		}
	}
	else if (CurrentIcon == 2) {
		for (auto& AI : Armed_ItemList) {
			if (AI->Count > 0 && !AI->Shaking)
				FileManager::Get_Instance()->Append_Image(DC, AI->itemObject, AI->Position + CameraOffset, 0.5f, 0.5f);
		}
		for (auto& CI : Crest_ItemList) {
			if (CI->Count > 0 && !CI->Shaking) {
				FileManager::Get_Instance()->Append_Image(DC, CI->itemObject, CI->Position + CameraOffset, 0.5f, 0.5f);
				
			}
		}
		if(!Item_SwappingA)
			Picking_Swap(DC, &Crest_ItemList);
		ObjectArmed(DC, CurrentPickingItem);
	}
}
void InventoryObject::Display_ItemInfo(HDC DC) {
	if (CurrentIcon == 1) {
		RECT MukJuText = { 270, 508 ,450 , 540 };
		TCHAR MUKJU[16] = { 0 };

		if (RandomMukJu > 0) {
			if (dwTime + 1000 >= GetTickCount()) {
				wsprintf(MUKJU, L"%d + %d", dynamic_cast<PlayerObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front())->Get_MukJu(), RandomMukJu);
			}
			if (dwTime + 1000 < GetTickCount()) {
				dynamic_cast<PlayerObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front())->Set_MukJu(
					dynamic_cast<PlayerObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front())->Get_MukJu() + 1);
				RandomMukJu -= 1;
				wsprintf(MUKJU, L"%d + %d", dynamic_cast<PlayerObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front())->Get_MukJu(), RandomMukJu);
			}
		}
		else if (RandomMukJu == 0) {
			wsprintf(MUKJU, L"%d", dynamic_cast<PlayerObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front())->Get_MukJu());
		}
		
		RECT StoneText = { 270, 563, 350 , 600 };
		TCHAR STONE[16] = { 0 };

		if (RandomStone > 0) {
			if (dwTime + 1000 >= GetTickCount()) {
				wsprintf(STONE, L"%d + %d", dynamic_cast<PlayerObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front())->Get_SilverStone(), RandomStone);
			}
			if (dwTime + 1000 < GetTickCount()) {
				dynamic_cast<PlayerObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front())->Set_SilverStone(
					dynamic_cast<PlayerObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front())->Get_SilverStone() + 1);
				RandomStone -= 1;
				wsprintf(STONE, L"%d + %d", dynamic_cast<PlayerObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front())->Get_SilverStone(), RandomStone);
			}
		}
		else if (RandomStone == 0) {
			wsprintf(STONE, L"%d", dynamic_cast<PlayerObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front())->Get_SilverStone());
		}

		DrawText(DC, MUKJU, 10, &MukJuText, DT_LEFT | DT_VCENTER);
		DrawText(DC, STONE, 10, &StoneText, DT_LEFT | DT_VCENTER);
	}
}

void InventoryObject::Display_KeyGuide(HDC DC) {
	SetBkMode(DC, TRANSPARENT);
	SetTextColor(DC, RGB(255, 255, 255));
	HFONT OldFont = (HFONT)SelectObject(DC, SerifFont);

	if (CurrentIcon == 1) {
		FileManager::Get_Instance()->Append_Image(DC, L"Key_4Arrow",	{ 915.f + CameraOffset.X, 580.f + CameraOffset.Y }, 0.4f, 0.4f);
		RECT ArrowText = { 890, 568 ,1050, 630 };
		DrawText(DC, L"슬롯 이동", 5, &ArrowText, DT_CENTER | DT_VCENTER);

		if (Default_ItemList[CurrentPickingItem]->Type == ITEM_TYPE::ITEM_USABLE) {
			FileManager::Get_Instance()->Append_Image(DC, L"Key_Z",			{ 1050.f + CameraOffset.X, 580.f + CameraOffset.Y }, 0.4f, 0.4f);
			RECT ZText = { 980, 568 ,1200, 630 };
			DrawText(DC, L"사용", 2, &ZText, DT_CENTER | DT_VCENTER);
		}
	}
	if (CurrentIcon == 2) {
		if (!Item_SwappingA && !Item_SwappingB) {
			FileManager::Get_Instance()->Append_Image(DC, L"Key_4Arrow", { 915.f + CameraOffset.X, 580.f + CameraOffset.Y }, 0.4f, 0.4f);
			RECT ArrowText = { 890, 568 ,1050, 630 };
			DrawText(DC, L"슬롯 이동", 5, &ArrowText, DT_CENTER | DT_VCENTER);

			if (Crest_ItemList[CurrentPickingItem]->Type != ITEM_TYPE::ITEM_END) {
				FileManager::Get_Instance()->Append_Image(DC, L"Key_Z", { 1050.f + CameraOffset.X, 580.f + CameraOffset.Y }, 0.4f, 0.4f);
				RECT ZText = { 980, 568 ,1200, 630 };
				DrawText(DC, L"장착", 2, &ZText, DT_CENTER | DT_VCENTER);
			}
		}
		else {
			FileManager::Get_Instance()->Append_Image(DC, L"Key_2Arrow", { 256.f + CameraOffset.X, 530.f + CameraOffset.Y }, 0.4f, 0.4f);
			RECT ArrowText = { 270, 518 ,370, 618 };
			DrawText(DC, L"슬롯 이동", 5, &ArrowText, DT_CENTER | DT_VCENTER);

			FileManager::Get_Instance()->Append_Image(DC, L"Key_X", { 386.f + CameraOffset.X, 530.f + CameraOffset.Y }, 0.4f, 0.4f);
			RECT ZText = { 380, 518 ,470, 618 };
			DrawText(DC, L"장착", 2, &ZText, DT_CENTER | DT_VCENTER);
		}
	}
	if (Show_ErrorMessage) {
		if (dwTime + 1500 < GetTickCount()) {
			Show_ErrorMessage = false;
			dwTime = GetTickCount();
		}
		else {
			RECT ErrorText = { 200, 570 ,600, 630 };
			DrawText(DC, L"같은 계열의 아이템만 착용할 수 있습니다!", 24, &ErrorText, DT_LEFT | DT_VCENTER);
		}
	}
			
}

void InventoryObject::Picking_Swap(HDC DC, vector<item*>* _ItemList) {
	INT LayerCount = 0;

	if (_ItemList == &Default_ItemList) { LayerCount = 5; }
	if (_ItemList == &Crest_ItemList  ) { LayerCount = 3; }

	FLOAT OriginRX = (*_ItemList)[PreviousPickingItem]->Position.X + 25.f + CameraOffset.X;
	FLOAT OriginRY = (*_ItemList)[PreviousPickingItem]->Position.Y + 25.f + CameraOffset.Y;
	FLOAT OriginLX = (*_ItemList)[PreviousPickingItem]->Position.X - 25.f + CameraOffset.X;
	FLOAT OriginLY = (*_ItemList)[PreviousPickingItem]->Position.Y - 25.f + CameraOffset.Y;

	if (CurrentPickingItem < _ItemList->size()-1) {
		if(KEY_COMMAND(KEY::ARROW_RIGHT, KEY_STATE::DOWN))		{ CurrentPickingItem++; 
		SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
		SoundManager::Get_Instance()->PlaySoundW(L"SlotMove.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
		}
	}
	if (CurrentPickingItem > 0) {
		if (KEY_COMMAND(KEY::ARROW_LEFT, KEY_STATE::DOWN))		{ CurrentPickingItem--; 
		SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
		SoundManager::Get_Instance()->PlaySoundW(L"SlotMove.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
		}
	}
	if (CurrentPickingItem - LayerCount >= 0) {
		if (KEY_COMMAND(KEY::ARROW_UP, KEY_STATE::DOWN))		{ CurrentPickingItem -= LayerCount;
		SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
		SoundManager::Get_Instance()->PlaySoundW(L"SlotMove.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
		}
	}
	if (CurrentPickingItem + LayerCount <= _ItemList->size() - 1) {
		if (KEY_COMMAND(KEY::ARROW_DOWN, KEY_STATE::DOWN))		{ CurrentPickingItem += LayerCount;
		SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
		SoundManager::Get_Instance()->PlaySoundW(L"SlotMove.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
		}
	}

	if (CurrentPickingItem != PreviousPickingItem) {
		
		FLOAT MoveScaleX = ((INT)((*_ItemList)[CurrentPickingItem]->Position.X + 25.f) - (INT)((*_ItemList)[PreviousPickingItem]->Position.X + 25.f)) / 3.f;
		FLOAT MoveScaleY = ((INT)((*_ItemList)[CurrentPickingItem]->Position.Y - 25.f) - (INT)((*_ItemList)[PreviousPickingItem]->Position.Y - 25.f)) / 3.f;

		DistanceStackRX += MoveScaleX;
		DistanceStackRY += MoveScaleY;

		DistanceStackLX += MoveScaleX;
		DistanceStackLY += MoveScaleY;

		if (fabsf(DistanceStackRX - 5.f) > fabsf((INT)((*_ItemList)[CurrentPickingItem]->Position.X + 25.f) - (INT)((*_ItemList)[PreviousPickingItem]->Position.X + 25.f))
			&& fabsf(DistanceStackRY - 5.f) > fabsf((INT)((*_ItemList)[CurrentPickingItem]->Position.Y + 25.f) - (INT)((*_ItemList)[PreviousPickingItem]->Position.Y + 25.f))) {
			DistanceStackRX = 0.f;
			DistanceStackRY = 0.f;
			DistanceStackLX = 0.f;
			DistanceStackLY = 0.f;
			PreviousPickingItem = CurrentPickingItem;
			return;
		}

		FileManager::Get_Instance()->Append_Image(DC, L"SelectorR", { OriginRX + DistanceStackRX, OriginRY + DistanceStackRY }, 0.6f, 0.6f);
		FileManager::Get_Instance()->Append_Image(DC, L"SelectorL", { OriginLX + DistanceStackLX, OriginLY + DistanceStackLY }, 0.6f, 0.6f);
	}
	else {
		FileManager::Get_Instance()->Append_Image(DC, L"SelectorR",
			{ (*_ItemList)[PreviousPickingItem]->Position.X + 25.f + CameraOffset.X, (*_ItemList)[PreviousPickingItem]->Position.Y + CameraOffset.Y + 25.f }, 0.6f, 0.6f);
		FileManager::Get_Instance()->Append_Image(DC, L"SelectorL",
			{ (*_ItemList)[PreviousPickingItem]->Position.X - 25.f + CameraOffset.X, (*_ItemList)[PreviousPickingItem]->Position.Y + CameraOffset.Y - 25.f }, 0.6f, 0.6f);
	}
}

void InventoryObject::Picking_Swap_Armor(HDC DC) {
	
	if (KEY_COMMAND(KEY::ARROW_RIGHT, KEY_STATE::DOWN)) { CurrentPickingItem = (CurrentPickingItem + 1) % Armed_ItemList.size(); 
	SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
	SoundManager::Get_Instance()->PlaySoundW(L"SlotMove.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
	}
	if (KEY_COMMAND(KEY::ARROW_LEFT, KEY_STATE::DOWN)) { 
		CurrentPickingItem = CurrentPickingItem-- % Armed_ItemList.size();
		if (CurrentPickingItem < 0) {
			CurrentPickingItem = 5;
		}
		SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
		SoundManager::Get_Instance()->PlaySoundW(L"SlotMove.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
	}
	PreviousPickingItem = CurrentPickingItem;

	FLOAT OriginRX = Armed_ItemList[PreviousPickingItem]->Position.X + 25.f+ CameraOffset.X;
	FLOAT OriginRY = Armed_ItemList[PreviousPickingItem]->Position.Y + 25.f+ CameraOffset.Y;
	FLOAT OriginLX = Armed_ItemList[PreviousPickingItem]->Position.X - 25.f+ CameraOffset.X;
	FLOAT OriginLY = Armed_ItemList[PreviousPickingItem]->Position.Y - 25.f+ CameraOffset.Y;

	FileManager::Get_Instance()->Append_Image(DC, L"SelectorR", { OriginRX, OriginRY }, 0.6f, 0.6f);
	FileManager::Get_Instance()->Append_Image(DC, L"SelectorL", { OriginLX, OriginLY }, 0.6f, 0.6f);
}

void InventoryObject::Append_MukJu(HDC DC, INT _MJR) {

}

BOOL InventoryObject::ObjectShake(HDC DC, vector<item*>* _ItemList, UINT _HDN, UINT _Time) {
	if (KEY_COMMAND(KEY::Z, KEY_STATE::DOWN) && (*_ItemList)[CurrentPickingItem]->Count > 0
		&& (*_ItemList)[CurrentPickingItem]->Type == ITEM_TYPE::ITEM_USABLE) {
		dwTime = GetTickCount();
	}
	if (KEY_COMMAND(KEY::Z, KEY_STATE::HOLD) && (*_ItemList)[CurrentPickingItem]->Count > 0 
		&& (*_ItemList)[CurrentPickingItem]->Type == ITEM_TYPE::ITEM_USABLE) {

		(*_ItemList)[CurrentPickingItem]->Shaking = true;

		FileManager::Get_Instance()->Append_Image(DC, (*_ItemList)[CurrentPickingItem]->itemObject, 
			{ (*_ItemList)[CurrentPickingItem]->Position.X + CameraOffset.X + rand() % _HDN - _HDN / 2,
			(*_ItemList)[CurrentPickingItem]->Position.Y + CameraOffset.Y + rand() % _HDN - _HDN / 2 },
			 0.5f, 0.5f);

		if (dwTime + _Time < GetTickCount() && (*_ItemList)[CurrentPickingItem]->Count > 0) {
			(*_ItemList)[CurrentPickingItem]->Count -= 1;
			(*_ItemList)[CurrentPickingItem]->Shaking = false;

			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
			SoundManager::Get_Instance()->PlaySoundW(L"ItemBreak.WAV", CHANNELID::SOUND_EFFECT, 1.1f);

			dwTime = GetTickCount();

			return true;
		}
	}
	else if (KEY_COMMAND(KEY::Z, KEY_STATE::UP) || (*_ItemList)[CurrentPickingItem]->Shaking == true ) {
		(*_ItemList)[CurrentPickingItem]->Shaking = false;
		dwTime = GetTickCount();
	}
	return false;
}

BOOL InventoryObject::ObjectArmed(HDC DC, INT _Crest_ItemNumb) {
	item* _item = Crest_ItemList[ArmorPickingItem];
	if (Item_SwappingA) {
		Picking_Swap_Armor(DC);
		if (KEY_COMMAND(KEY::X, KEY_STATE::DOWN) && Armed_ItemList[PreviousPickingItem]->Type == _item->Type) {
			Armed_ItemList[PreviousPickingItem]->Shaking = true;
			_item->Shaking = true;
			Item_SwappingB = true;
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
			SoundManager::Get_Instance()->PlaySoundW(L"SwapWeapon.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
		}
		else if (KEY_COMMAND(KEY::X, KEY_STATE::DOWN) && Armed_ItemList[PreviousPickingItem]->Type != _item->Type) {
			Show_ErrorMessage = true;
			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_EFFECT);
			SoundManager::Get_Instance()->PlaySoundW(L"SwapWeaponFail.WAV", CHANNELID::SOUND_EFFECT, 1.1f);
		}
	}
	if (KEY_COMMAND(KEY::Z, KEY_STATE::DOWN) && Crest_ItemList[_Crest_ItemNumb]->Count > 0 &&
		(Crest_ItemList[_Crest_ItemNumb]->Type == ITEM_TYPE::ITEM_WEAPON || Crest_ItemList[_Crest_ItemNumb]->Type == ITEM_TYPE::ITEM_SHIELD || Crest_ItemList[_Crest_ItemNumb]->Type == ITEM_TYPE::ITEM_UTIL)) {
		Item_SwappingA = true;
		ArmorPickingItem = _Crest_ItemNumb;
		CurrentPickingItem = 0;
		PreviousPickingItem = 0;
	}

	if (Item_SwappingB && SwapMotion(DC, Armed_ItemList[PreviousPickingItem], _item)) {
		Item_SwappingA = false;
		Item_SwappingB = false;

		Armed_ItemList[PreviousPickingItem]->Shaking = false;
		_item->Shaking = false;

		CurrentPickingItem = 0;
		PreviousPickingItem = 0;

		return true;
	}
}

BOOL InventoryObject::SwapMotion(HDC DC, item* itemR, item* itemL) {
	FLOAT MoveScaleX = (itemR->Position.X - itemL->Position.X) / 6.f;
	FLOAT MoveScaleY = (itemR->Position.Y - itemL->Position.Y) / 6.f;

	DistanceStackRX -= MoveScaleX ;
	DistanceStackRY -= MoveScaleY ;

	DistanceStackLX += MoveScaleX ;
	DistanceStackLY += MoveScaleY ;

	if (fabsf(DistanceStackRX) > fabsf(itemR->Position.X - itemL->Position.X)) {
		DistanceStackRX = 0.f;
		DistanceStackRY = 0.f;
		DistanceStackLX = 0.f;
		DistanceStackLY = 0.f;

		swap(itemR->itemObject, itemL->itemObject);
		swap(itemR->Count, itemL->Count);
		swap(itemR->Type, itemL->Type);

		return true;
	}

	FileManager::Get_Instance()->Append_Image(DC, itemR->itemObject, { itemR->Position.X + DistanceStackRX+ CameraOffset.X, itemR->Position.Y + DistanceStackRY + CameraOffset.Y }, 0.6f, 0.6f);
	FileManager::Get_Instance()->Append_Image(DC, itemL->itemObject, { itemL->Position.X + DistanceStackLX + CameraOffset.X, itemL->Position.Y + DistanceStackLY + CameraOffset.Y }, 0.6f, 0.6f);
	return false;
}