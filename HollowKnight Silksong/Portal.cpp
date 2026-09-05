#include "PCH.h"
#include "Portal.h"

void Portal::Initialize() {
	if(SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_VILLAGE)
		OBJINFO = { 0.f, 0.f, 50.f, 200.f };
}

int Portal::Update()
{
	Update_RECT();
	return 0;
}

void Portal::Late_Update()	{ }

void Portal::Render(HDC DC) {
	//FLOAT OffsetX = CameraManager::Get_Instance()->GetOffset().X;
	//FLOAT OffsetY = CameraManager::Get_Instance()->GetOffset().Y;
	//
	//HPEN myPen = CreatePen(PS_SOLID, 0, RGB(255, 0, 255));
	//HGDIOBJ oldPen = SelectObject(DC, myPen);
	//
	//HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	//HBRUSH oldBrush = (HBRUSH)SelectObject(DC, myBrush);
	//
	//Rectangle(DC, OBJRECT.left - OffsetX, OBJRECT.top - OffsetY, OBJRECT.right - OffsetX, OBJRECT.bottom - OffsetY);
	//
	//SelectObject(DC, oldBrush);
	//DeleteObject(myBrush);
	//
	//SelectObject(DC, oldPen);
	//DeleteObject(myPen);z

	if (KEY_COMMAND(KEY::F9, KEY_STATE::DOWN)) {
		SceneManager::Get_Instance()->Set_NextScene(STAGE_TYPE::STAGE_GATE);
		SceneManager::Get_Instance()->Scene_Transition(STAGE_TYPE::STAGE_LOAD);
		return;
	}
	if (KEY_COMMAND(KEY::F10, KEY_STATE::DOWN)) {
		SceneManager::Get_Instance()->Set_NextScene(STAGE_TYPE::STAGE_DUNGEON);
		SceneManager::Get_Instance()->Scene_Transition(STAGE_TYPE::STAGE_LOAD);
		return;
	}
	if (KEY_COMMAND(KEY::F8, KEY_STATE::DOWN)) {
		SceneManager::Get_Instance()->Set_NextScene(STAGE_TYPE::STAGE_BOSS);
		SceneManager::Get_Instance()->Scene_Transition(STAGE_TYPE::STAGE_LOAD);
		return;
	}
}

void Portal::Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value) {
	if (pObj->Get_Tag() == OBJECT_TAG::OBJ_PLAYER && PortalTag == PTAG::VILLAGE_TO_DUNGEON) {
		SceneManager::Get_Instance()->Set_NextScene(STAGE_TYPE::STAGE_DUNGEON);
		SceneManager::Get_Instance()->Scene_Transition(STAGE_TYPE::STAGE_LOAD);
		return;
	}
	if (pObj->Get_Tag() == OBJECT_TAG::OBJ_PLAYER && PortalTag == PTAG::DUNGEON_TO_VILLAGE) {
		SceneManager::Get_Instance()->Set_NextScene(STAGE_TYPE::STAGE_VILLAGE);
		SceneManager::Get_Instance()->Scene_Transition(STAGE_TYPE::STAGE_LOAD);
		return;
	}
	if (pObj->Get_Tag() == OBJECT_TAG::OBJ_PLAYER && PortalTag == PTAG::DUNGEON_TO_GATE) {
		SceneManager::Get_Instance()->Set_NextScene(STAGE_TYPE::STAGE_GATE);
		SceneManager::Get_Instance()->Scene_Transition(STAGE_TYPE::STAGE_LOAD);
		return;
	}
}
void Portal::Release()	{ }
