#include "PCH.h"
#include "Scene_Select.h"
Scene_Select::Scene_Select() : dwTime{ GetTickCount() }, StartPixelIndex{0}, AnimationIndex(0){ LoadingTime = GetTickCount(); }
Scene_Select::~Scene_Select() { Release(); }

void Scene_Select::Initialize() {

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BackLowScale2.bmp", L"Back");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/GameSlot01.bmp", L"GameSlot_Image01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/GameSlot02.bmp", L"GameSlot_Image02");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/GameSlot03.bmp", L"GameSlot_Image03");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/GameSlot04.bmp", L"GameSlot_Image04");
	
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/MenuPointer09L.bmp", L"PointerL");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/MenuPointer09R.bmp", L"PointerR");
	
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/GameSlot_TRoot_Anim.bmp", L"TRoot");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/GameSlot_BRoot_Anim.bmp", L"BRoot");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/GameSlot_Wing.bmp", L"Wing");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/Replay.bmp", L"Replay");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/MainMenu/BMPComplete/TrashBin03.bmp", L"TrashBin");

	ButtonList.push_back(new ButtonObject(DEFAULT_WINDOW_CX / 2.f, DEFAULT_WINDOW_CY / 2.f + 250.f, 68.f, 30.f, L"뒤로", BTN_TAG::BTN_BACK));
	ButtonList.push_back(new ButtonObject(DEFAULT_WINDOW_CX / 2.f - 418.f, 70.f, 353.f, 640.f, L"", BTN_TAG::BTN_ENTERSTAGE));
	ButtonList.push_back(new ButtonObject(DEFAULT_WINDOW_CX / 2.f, 70.f, 150.f, 60.f, L"프로필 선택", BTN_TAG::BTN_END));


	FileManager::Get_Instance()->FrameStartPoint_Reset();

	for (auto& btn : ButtonList) {
		btn->Initialize();
	}
}
void Scene_Select::Update(){

	for (auto& btn : ButtonList) {
		if (btn) { btn->Update(); }

		if (dynamic_cast<ButtonObject*>(btn)->Get_BTNTAG() == BTN_TAG::BTN_BACK && 
			dynamic_cast<ButtonObject*>(btn)->ButtonEvent() == BTN_EVENT::BTN_ONCLICK) {
			SceneManager::Get_Instance()->Scene_Transition(STAGE_TYPE::STAGE_START);
			return;
		}

		if (dynamic_cast<ButtonObject*>(btn)->Get_BTNTAG() == BTN_TAG::BTN_ENTERSTAGE &&
			dynamic_cast<ButtonObject*>(btn)->ButtonEvent() == BTN_EVENT::BTN_ONCLICK) {
			SceneManager::Get_Instance()->Set_NextScene(STAGE_TYPE::STAGE_VILLAGE);
			SceneManager::Get_Instance()->Scene_Transition(STAGE_TYPE::STAGE_LOAD);
			return;
		}
	}
}
void Scene_Select::Late_Update(){
	for (auto& btn : ButtonList) {
		if (btn) {
			btn->Late_Update();
		}
	}
}
void Scene_Select::Render(HDC DC){

	FileManager::Get_Instance()->Append_Image(DC, L"Back", { DEFAULT_WINDOW_CX / 2.f, DEFAULT_WINDOW_CY / 2.f });
	
	FileManager::Get_Instance()->Append_Image(DC, L"GameSlot_Image01",{ DEFAULT_WINDOW_CX / 2.f - 418.f,			DEFAULT_WINDOW_CY / 2.f - 45.f},		  0.6f, 0.6f);
	FileManager::Get_Instance()->Append_Image(DC, L"Replay",			{ DEFAULT_WINDOW_CX / 2.f - 418.f - 30.f,	DEFAULT_WINDOW_CY / 2.f + 190.f}, 0.35f, 0.35f);
	FileManager::Get_Instance()->Append_Image(DC, L"TrashBin",		{ DEFAULT_WINDOW_CX / 2.f - 418.f + 40.f,	DEFAULT_WINDOW_CY / 2.f + 190.f }, 0.5f, 0.5f);

	FileManager::Get_Instance()->Append_Image(DC, L"GameSlot_Image02",{ DEFAULT_WINDOW_CX / 2.f - 140.f,			DEFAULT_WINDOW_CY / 2.f - 45.f},		  0.6f, 0.6f);
	FileManager::Get_Instance()->Append_Image(DC, L"Replay",			{ DEFAULT_WINDOW_CX / 2.f - 140.f - 30.f,	DEFAULT_WINDOW_CY / 2.f + 190.f }, 0.35f, 0.35f);
	FileManager::Get_Instance()->Append_Image(DC, L"TrashBin",		{ DEFAULT_WINDOW_CX / 2.f - 140.f + 40.f,	DEFAULT_WINDOW_CY / 2.f + 190.f }, 0.5f, 0.5f);

	FileManager::Get_Instance()->Append_Image(DC, L"GameSlot_Image03",{ DEFAULT_WINDOW_CX / 2.f + 140.f,			DEFAULT_WINDOW_CY / 2.f - 45.f},		  0.6f, 0.6f);
	FileManager::Get_Instance()->Append_Image(DC, L"Replay",			{ DEFAULT_WINDOW_CX / 2.f + 140.f - 30.f,	DEFAULT_WINDOW_CY / 2.f + 190.f }, 0.35f, 0.35f);
	FileManager::Get_Instance()->Append_Image(DC, L"TrashBin",		{ DEFAULT_WINDOW_CX / 2.f + 140.f + 40.f,	DEFAULT_WINDOW_CY / 2.f + 190.f }, 0.5f, 0.5f);

	FileManager::Get_Instance()->Append_Image(DC, L"GameSlot_Image04",{ DEFAULT_WINDOW_CX / 2.f + 418.f,			DEFAULT_WINDOW_CY / 2.f - 45.f},		  0.6f, 0.6f);
	FileManager::Get_Instance()->Append_Image(DC, L"Replay",			{ DEFAULT_WINDOW_CX / 2.f + 418.f - 30.f,	DEFAULT_WINDOW_CY / 2.f + 190.f }, 0.35f, 0.35f);
	FileManager::Get_Instance()->Append_Image(DC, L"TrashBin",		{ DEFAULT_WINDOW_CX / 2.f + 418.f + 40.f,	DEFAULT_WINDOW_CY / 2.f + 190.f }, 0.5f, 0.5f);

	if (PlayAnimation_Once(DC, L"TRoot", &StartPixelIndex[0], 300, 25, &dwTime[0], { DEFAULT_WINDOW_CX / 2.f - 418.f - 30.f,	DEFAULT_WINDOW_CY / 2.f - 45.f - 50.f }, 0.6f, 0.6f)
		&& PlayAnimation_Once(DC, L"BRoot", &StartPixelIndex[1], 253, 25, &dwTime[1], { DEFAULT_WINDOW_CX / 2.f - 418.f + 35.f,	DEFAULT_WINDOW_CY / 2.f - 45.f + 140.f }, 0.6f, 0.6f)) {

	}


	if (PlayAnimation_Once(DC, L"TRoot", &StartPixelIndex[2], 300, 25, &dwTime[0],    	{ DEFAULT_WINDOW_CX / 2.f - 140.f - 30.f,	DEFAULT_WINDOW_CY / 2.f - 45.f - 50.f },  0.6f, 0.6f)
		&& PlayAnimation_Once(DC, L"BRoot", &StartPixelIndex[3], 253, 25, &dwTime[1], 	{ DEFAULT_WINDOW_CX / 2.f - 140.f + 35.f,	DEFAULT_WINDOW_CY / 2.f - 45.f + 140.f }, 0.6f, 0.6f)) {

	}


	if (PlayAnimation_Once(DC, L"TRoot", &StartPixelIndex[4], 300, 25, &dwTime[0],    { DEFAULT_WINDOW_CX / 2.f + 140.f - 30.f,	DEFAULT_WINDOW_CY / 2.f - 45.f - 50.f },  0.6f, 0.6f)
		&& PlayAnimation_Once(DC, L"BRoot", &StartPixelIndex[5], 253, 25, &dwTime[1], { DEFAULT_WINDOW_CX / 2.f + 140.f + 35.f,	DEFAULT_WINDOW_CY / 2.f - 45.f + 140.f }, 0.6f, 0.6f)) {

	}


	if (PlayAnimation_Once(DC, L"TRoot", &StartPixelIndex[6], 300, 25, &dwTime[0],   { DEFAULT_WINDOW_CX / 2.f + 418.f - 30.f,	DEFAULT_WINDOW_CY / 2.f - 45.f - 50.f },  0.6f, 0.6f)
		&& PlayAnimation_Once(DC, L"BRoot", &StartPixelIndex[7], 253, 25, &dwTime[1],{ DEFAULT_WINDOW_CX / 2.f + 418.f + 35.f,	DEFAULT_WINDOW_CY / 2.f - 45.f + 140.f }, 0.6f, 0.6f)) {
	}
	
	

	if (dwTime[2] + 200 < GetTickCount()) {
		FileManager::Get_Instance()->PlayAnimation_Once(DC, L"Wing", 750, 50, { DEFAULT_WINDOW_CX / 2.f, 100 }, 0.5f, 0.5f);
	}
	
	for (auto& btn : ButtonList) {
		if (btn) { btn->Render(DC);	}
	}
	if (dynamic_cast<ButtonObject*>(ButtonList[0])->Get_BTNTAG() == BTN_TAG::BTN_BACK && dynamic_cast<ButtonObject*>(ButtonList[0])->ButtonEvent() == BTN_EVENT::BTN_HOVER) {
		FileManager::Get_Instance()->Append_Image(DC, L"PointerL", { DEFAULT_WINDOW_CX / 2.f - 58.f, DEFAULT_WINDOW_CY / 2.f + 250.f }, 0.375f, 0.375f);
		FileManager::Get_Instance()->Append_Image(DC, L"PointerR", { DEFAULT_WINDOW_CX / 2.f + 58.f, DEFAULT_WINDOW_CY / 2.f + 250.f }, 0.375f, 0.375f);
	}
}
void Scene_Select::Release(){
	
	SAFE_DELETE_VEC(ButtonList);
}
BOOL Scene_Select::PlayAnimation_Once(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer,
	Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight)
{
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	UINT _FrameEndIndex = (UINT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	GdiTransparentBlt(_SubWindowDC, StartLeft - CameraManager::Get_Instance()->GetOffset().X,
		StartTop - CameraManager::Get_Instance()->GetOffset().Y, Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		*_SPF * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));

	if (*_SPF >= _FrameEndIndex - 1) {
		*_SPF = _FrameEndIndex - 1;
		return true;
	}

	if (_AnimSpeed + *Timer < GetTickCount() && *_SPF < _FrameEndIndex - 1) {
		*_SPF += 1;
		*Timer = GetTickCount();
	}

	ReleaseDC(hWnd, MemDC);

	return false;
}