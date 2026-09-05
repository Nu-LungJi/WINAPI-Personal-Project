#include "PCH.h"
#include "Scene_Start.h"

Scene_Start::Scene_Start()	: PrevFrameState(false), CurrFrameState(false) {			 }
Scene_Start::~Scene_Start() { Release(); }

void Scene_Start::Initialize()
{
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BackLowScale2.bmp", L"Back");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/HollowKnight_SilkSong_Title_copy.bmp",	L"MainTitle"			);
	
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/MainMenu_Ground01_copy.bmp",				L"StartScene_Ground01"	);
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/MainMenu_Ground02_copy.bmp",				L"StartScene_Ground02"	);
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/MainMenu_Ground03_copy.bmp",				L"StartScene_Ground03"	);
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/MainMenu_Needle_copy.bmp",				L"StartScene_Needle"	);
	
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/MenuPointer09L.bmp",						L"PointerL"				);
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/MenuPointer09R.bmp",						L"PointerR"				);

	ButtonList.push_back(new ButtonObject(DEFAULT_WINDOW_CX / 2.f, DEFAULT_WINDOW_CY / 2.f + 45.f,  135.f, 30.f, L"게임 시작",	BTN_TAG::BTN_START));
	ButtonList.push_back(new ButtonObject(DEFAULT_WINDOW_CX / 2.f, DEFAULT_WINDOW_CY / 2.f + 87.f,  135.f, 30.f, L"설정",		BTN_TAG::BTN_SETTING));
	ButtonList.push_back(new ButtonObject(DEFAULT_WINDOW_CX / 2.f, DEFAULT_WINDOW_CY / 2.f + 130.f, 135.f, 30.f, L"업적",		BTN_TAG::BTN_RECORD));
	ButtonList.push_back(new ButtonObject(DEFAULT_WINDOW_CX / 2.f, DEFAULT_WINDOW_CY / 2.f + 170.f, 135.f, 30.f, L"더 보기",	BTN_TAG::BTN_STAFF));
	ButtonList.push_back(new ButtonObject(DEFAULT_WINDOW_CX / 2.f, DEFAULT_WINDOW_CY / 2.f + 215.f, 135.f, 30.f, L"게임 종료",	BTN_TAG::BTN_EXIT));

	for (auto& btn : ButtonList) {
		btn->Initialize();
	}
}

void Scene_Start::Update()
{
	for (auto& btn : ButtonList) {
		if (btn) {
			btn->Update();
		}
	}

	if (dynamic_cast<ButtonObject*>(ButtonList[(LONG)BTN_TAG::BTN_START])->ButtonEvent() == BTN_EVENT::BTN_ONCLICK) {
		SceneManager::Get_Instance()->Scene_Transition(STAGE_TYPE::STAGE_SELECT);
		return;
	}
	
	if (dynamic_cast<ButtonObject*>(ButtonList[(LONG)BTN_TAG::BTN_EXIT])->ButtonEvent() == BTN_EVENT::BTN_ONCLICK) {
		SceneManager::Get_Instance()->Scene_Transition(STAGE_TYPE::STAGE_QUIT);
		return;
	}
	if (KEY_COMMAND(KEY::F10, KEY_STATE::DOWN)) {
		SceneManager::Get_Instance()->Set_NextScene(STAGE_TYPE::STAGE_DUNGEON);
		SceneManager::Get_Instance()->Scene_Transition(STAGE_TYPE::STAGE_LOAD);
		return;
	}
}

void Scene_Start::Late_Update()
{
	for (auto& btn : ButtonList) {
		if (btn) {
			btn->Late_Update();
		}
	}
}

void Scene_Start::Render(HDC DC)
{
	//SetBkMode(DC, TRANSPARENT);
	SetTextColor(DC, RGB(255, 255, 255));

	FileManager::Get_Instance()->Append_Image(DC, L"Back",				{ DEFAULT_WINDOW_CX / 2.f,			DEFAULT_WINDOW_CY / 2.f });
	FileManager::Get_Instance()->Append_Image(DC, L"MainTitle",			{ DEFAULT_WINDOW_CX / 2.f,			DEFAULT_WINDOW_CY / 4.f + 30.f }, 0.5f, 0.5f);
	FileManager::Get_Instance()->Append_Image(DC, L"StartScene_Ground01", { DEFAULT_WINDOW_CX / 2.f + 360.f,	DEFAULT_WINDOW_CY - 60.f}, 0.65f, 0.65f);
	FileManager::Get_Instance()->Append_Image(DC, L"StartScene_Ground01", { DEFAULT_WINDOW_CX / 2.f + 435.f,	DEFAULT_WINDOW_CY - 60.f }, 0.65f, 0.65f);
	FileManager::Get_Instance()->Append_Image(DC, L"StartScene_Ground03", { DEFAULT_WINDOW_CX / 2.f + 190.f,	DEFAULT_WINDOW_CY - 82.f }, 0.65f, 0.65f);
	FileManager::Get_Instance()->Append_Image(DC, L"StartScene_Needle",	{ DEFAULT_WINDOW_CX / 2.f + 390.f,	DEFAULT_WINDOW_CY / 2.f + 25.f}, 0.65f, 0.65f);
	FileManager::Get_Instance()->Append_Image(DC, L"StartScene_Ground02", { DEFAULT_WINDOW_CX / 2.f + 250.f,	DEFAULT_WINDOW_CY - 100.f}, 0.65f, 0.65f);


	if (dynamic_cast<ButtonObject*>(ButtonList[(LONG)BTN_TAG::BTN_START])->ButtonEvent() == BTN_EVENT::BTN_HOVER) {
		CurrFrameState = true;
		FileManager::Get_Instance()->Append_Image(DC, L"PointerL", { DEFAULT_WINDOW_CX / 2.f - 80.f, DEFAULT_WINDOW_CY / 2.f + 45.f }, 0.375f, 0.375f);
		FileManager::Get_Instance()->Append_Image(DC, L"PointerR", { DEFAULT_WINDOW_CX / 2.f + 80.f, DEFAULT_WINDOW_CY / 2.f + 45.f },  0.375f, 0.375f);
	}
	if (dynamic_cast<ButtonObject*>(ButtonList[(LONG)BTN_TAG::BTN_SETTING])->ButtonEvent() == BTN_EVENT::BTN_HOVER) {
		CurrFrameState = true;
		FileManager::Get_Instance()->Append_Image(DC, L"PointerL", { DEFAULT_WINDOW_CX / 2.f - 60.f, DEFAULT_WINDOW_CY / 2.f + 87.f },  0.375f, 0.375f);
		FileManager::Get_Instance()->Append_Image(DC, L"PointerR", { DEFAULT_WINDOW_CX / 2.f + 60.f, DEFAULT_WINDOW_CY / 2.f + 87.f },  0.375f, 0.375f);
	}
	if (dynamic_cast<ButtonObject*>(ButtonList[(LONG)BTN_TAG::BTN_RECORD])->ButtonEvent() == BTN_EVENT::BTN_HOVER) {
		CurrFrameState = true;
		FileManager::Get_Instance()->Append_Image(DC, L"PointerL", { DEFAULT_WINDOW_CX / 2.f - 60.f, DEFAULT_WINDOW_CY / 2.f + 130.f }, 0.375f, 0.375f);
		FileManager::Get_Instance()->Append_Image(DC, L"PointerR", { DEFAULT_WINDOW_CX / 2.f + 60.f, DEFAULT_WINDOW_CY / 2.f + 130.f }, 0.375f, 0.375f);
	}
	if (dynamic_cast<ButtonObject*>(ButtonList[(LONG)BTN_TAG::BTN_STAFF])->ButtonEvent() == BTN_EVENT::BTN_HOVER) {
		CurrFrameState = true;
		FileManager::Get_Instance()->Append_Image(DC, L"PointerL", { DEFAULT_WINDOW_CX / 2.f - 70.f, DEFAULT_WINDOW_CY / 2.f + 170.f }, 0.375f, 0.375f);
		FileManager::Get_Instance()->Append_Image(DC, L"PointerR", { DEFAULT_WINDOW_CX / 2.f + 70.f, DEFAULT_WINDOW_CY / 2.f + 170.f }, 0.375f, 0.375f);
	}
	if (dynamic_cast<ButtonObject*>(ButtonList[(LONG)BTN_TAG::BTN_EXIT])->ButtonEvent() == BTN_EVENT::BTN_HOVER) {
		CurrFrameState = true;
		FileManager::Get_Instance()->Append_Image(DC, L"PointerL", { DEFAULT_WINDOW_CX / 2.f - 80.f, DEFAULT_WINDOW_CY / 2.f + 215.f }, 0.375f, 0.375f);
		FileManager::Get_Instance()->Append_Image(DC, L"PointerR", { DEFAULT_WINDOW_CX / 2.f + 80.f, DEFAULT_WINDOW_CY / 2.f + 215.f }, 0.375f, 0.375f);
	}

	for (auto& btn : ButtonList) {
		if (btn) {
			btn->Render(DC);
		}
	}
}

void Scene_Start::Release() {
	SAFE_DELETE_VEC(ButtonList);
}
