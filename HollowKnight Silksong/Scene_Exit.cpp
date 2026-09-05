#include "PCH.h"
#include "Scene_Exit.h"

Scene_Exit::Scene_Exit() : dwTime(GetTickCount()) {}
Scene_Exit::~Scene_Exit() { Release(); }

void Scene_Exit::Initialize()
{
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BackLowScale2.bmp", L"Back");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/GameSlot_Wing.bmp", L"Wing");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/MenuPointer09L.bmp", L"PointerL");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/MenuPointer09R.bmp", L"PointerR");

	ButtonList.push_back(new ButtonObject(DEFAULT_WINDOW_CX / 2.f, DEFAULT_WINDOW_CY / 2.f - 50.f, 500.f, 30.f, L"게임을 종료 합니까?  ", BTN_TAG::BTN_BACK));
	ButtonList.push_back(new ButtonObject(DEFAULT_WINDOW_CX / 2.f, DEFAULT_WINDOW_CY / 2.f + 20.f, 68.f, 30.f, L"예",					BTN_TAG::BTN_YES));
	ButtonList.push_back(new ButtonObject(DEFAULT_WINDOW_CX / 2.f, DEFAULT_WINDOW_CY / 2.f + 70.f, 68.f, 30.f, L"아니오",				BTN_TAG::BTN_NO));

	for (auto& btn : ButtonList) {
		btn->Initialize();
	}
}

void Scene_Exit::Update()
{
	for (auto& btn : ButtonList) {

		if (btn) { btn->Update(); }

		if (dynamic_cast<ButtonObject*>(btn)->Get_BTNTAG() == BTN_TAG::BTN_YES && dynamic_cast<ButtonObject*>(btn)->ButtonEvent() == BTN_EVENT::BTN_ONCLICK) {
			DestroyWindow(hWnd);
			return;
		}
		if (dynamic_cast<ButtonObject*>(btn)->Get_BTNTAG() == BTN_TAG::BTN_NO && dynamic_cast<ButtonObject*>(btn)->ButtonEvent() == BTN_EVENT::BTN_ONCLICK) {
			SceneManager::Get_Instance()->Scene_Transition(STAGE_TYPE::STAGE_START);
			return;
		}
	}
}

void Scene_Exit::Late_Update()
{
	for (auto& btn : ButtonList) {
		if (btn) {
			btn->Late_Update();
		}
	}
}

void Scene_Exit::Render(HDC DC)	{
	FileManager::Get_Instance()->Append_Image(DC, L"Back", { DEFAULT_WINDOW_CX / 2.f, DEFAULT_WINDOW_CY / 2.f });

	if (dwTime + 200 < GetTickCount()) {
		FileManager::Get_Instance()->PlayAnimation_Once(DC, L"Wing", 750, 50, { DEFAULT_WINDOW_CX / 2.f, 250 }, 0.75f, 0.75f);
	}
	for (auto& btn : ButtonList) {
		if (btn) { btn->Render(DC); }
		if (dynamic_cast<ButtonObject*>(btn)->Get_BTNTAG() == BTN_TAG::BTN_YES && dynamic_cast<ButtonObject*>(btn)->ButtonEvent() == BTN_EVENT::BTN_HOVER) {
			FileManager::Get_Instance()->Append_Image(DC, L"PointerL", { DEFAULT_WINDOW_CX / 2.f - 40.f, DEFAULT_WINDOW_CY / 2.f + 20.f }, 0.375f, 0.375f);
			FileManager::Get_Instance()->Append_Image(DC, L"PointerR", { DEFAULT_WINDOW_CX / 2.f + 40.f, DEFAULT_WINDOW_CY / 2.f + 20.f }, 0.375f, 0.375f);
		}
		if (dynamic_cast<ButtonObject*>(btn)->Get_BTNTAG() == BTN_TAG::BTN_NO && dynamic_cast<ButtonObject*>(btn)->ButtonEvent() == BTN_EVENT::BTN_HOVER) {
			FileManager::Get_Instance()->Append_Image(DC, L"PointerL", { DEFAULT_WINDOW_CX / 2.f - 60.f, DEFAULT_WINDOW_CY / 2.f + 70.f }, 0.375f, 0.375f);
			FileManager::Get_Instance()->Append_Image(DC, L"PointerR", { DEFAULT_WINDOW_CX / 2.f + 60.f, DEFAULT_WINDOW_CY / 2.f + 70.f }, 0.375f, 0.375f);
		}
	}
}

void Scene_Exit::Release() {	SAFE_DELETE_VEC(ButtonList);	}
