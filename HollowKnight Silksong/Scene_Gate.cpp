#include "PCH.h"
#include "Scene_Gate.h"

Scene_Gate::Scene_Gate() : LiftValue(0.f), dwTime{ GetTickCount() }, StartPixelFrame{ 0 }, CarryOn(false) {}

Scene_Gate::~Scene_Gate() { Release(); }
FLOAT g_fVolume = 1.1f;
void Scene_Gate::Initialize() {
	if (ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->size() < 1) {
		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_PLAYER, AbstractFactory<PlayerObject>::Create());
	}
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Gate/Carrier.bmp", L"Carrier");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Gate/Chain.bmp", L"Gate_Chain");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Gate/Floor03.bmp", L"Ground");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Gate/BlackBoard.bmp", L"BlackBoard");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Gate/BackGround.bmp", L"Gate_BackGround");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Fleur/Gate_Interact_Anim.bmp", L"GateSign");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Walk/Gate_Walk.bmp", L"Gate_Walk");

	Player = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front();
	Player->Set_Pos(DEFAULT_WINDOW_CX / 2 + 520.f, DEFAULT_WINDOW_CY / 2 + 155);

	CameraManager::Get_Instance()->SetTarget(Player);

	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
	ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(600.f, DEFAULT_WINDOW_CY / 2 + 240.f, 1500, 50);
}

void Scene_Gate::Update() {
	FLOAT Angle = 0.f;
	if (KEY_COMMAND(KEY::H, KEY_STATE::DOWN) && Player->Get_Pos().X < DEFAULT_WINDOW_CX / 2 + 200.f && Player->Get_Pos().X > DEFAULT_WINDOW_CX / 2 - 200.f) {
			CarryOn = true;
			dwTime[0] = GetTickCount();

			SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_PLAYER);
			SoundManager::Get_Instance()->PlaySoundW(L"GateMove.WAV", CHANNELID::SOUND_PLAYER, 1.1f);
	}

	if (CarryOn && dwTime[0] + 5000 < GetTickCount()) {
		
		if (Angle < 90) { Angle += 0.5f; }
		LiftValue += 5 *  (sinf(Angle * PI / 180) + 1) * Angle;
		Player->Set_Pos(DEFAULT_WINDOW_CX / 2 + CameraManager::Get_Instance()->GetOffset().X, 
			DEFAULT_WINDOW_CY / 2 + CameraManager::Get_Instance()->GetOffset().Y - LiftValue + 100.f);
	}

	
	if (LiftValue > 450.f) {
		SceneManager::Get_Instance()->Set_NextScene(STAGE_TYPE::STAGE_BOSS);
		SceneManager::Get_Instance()->Scene_Transition(STAGE_TYPE::STAGE_LOAD);
	}
}

void Scene_Gate::Late_Update()	{}

void Scene_Gate::Render(HDC DC) {
	
	Vector2D COffset = CameraManager::Get_Instance()->GetOffset();

	FileManager::Get_Instance()->Append_Image(DC, L"Gate_BackGround", { DEFAULT_WINDOW_CX/2, DEFAULT_WINDOW_CY/2 });
	FileManager::Get_Instance()->Append_Image(DC, L"Carrier", { DEFAULT_WINDOW_CX / 2 + COffset.X, DEFAULT_WINDOW_CY / 2 + COffset.Y - LiftValue }, 0.5f, 0.5f);

	FileManager::Get_Instance()->Append_Image(DC, L"Gate_Chain", { DEFAULT_WINDOW_CX / 2 + COffset.X, DEFAULT_WINDOW_CY / 2 + COffset.Y - 325.f - LiftValue}, 0.7f, 0.7f);
	FileManager::Get_Instance()->Append_Image(DC, L"Gate_Chain", { DEFAULT_WINDOW_CX / 2 + COffset.X, DEFAULT_WINDOW_CY / 2 + COffset.Y - 480.f - LiftValue}, 0.7f, 0.7f);

	if (Player->Get_Pos().X < DEFAULT_WINDOW_CX / 2 + 200.f && Player->Get_Pos().X > DEFAULT_WINDOW_CX / 2 - 200.f && !CarryOn) {
		PlayAnimation_Once_Stable(DC, L"GateSign", &StartPixelFrame[0], 160, 50, { DEFAULT_WINDOW_CX / 2 , DEFAULT_WINDOW_CY / 2 - 30.f }, 0.7f, 0.7f);
	}
	else {
		PlayAnimation_Reverse(DC, L"GateSign", &StartPixelFrame[0], 160, 50, { DEFAULT_WINDOW_CX / 2 , DEFAULT_WINDOW_CY / 2 - 30.f }, 0.7f, 0.7f);
	}
	if (CarryOn) {
		PlayAnimation_Loop(DC, L"Gate_Walk", &StartPixelFrame[4], 210, 70, &dwTime[1], 29,{ DEFAULT_WINDOW_CX / 2 ,DEFAULT_WINDOW_CY / 2 - LiftValue + 150.f }, 0.6f, 0.6f);
		Player->Set_Pos(-100.f, 10000.f);
	}
	FileManager::Get_Instance()->Append_Image(DC, L"Ground", {  50.f,   DEFAULT_WINDOW_CY / 2 +	COffset.Y + 235.f }, 0.5f, 0.5f);
	FileManager::Get_Instance()->Append_Image(DC, L"Ground", { 150.f, DEFAULT_WINDOW_CY / 2 +	COffset.Y + 235.f }, 0.5f, 0.5f);
	FileManager::Get_Instance()->Append_Image(DC, L"Ground", { 250.f,  DEFAULT_WINDOW_CY / 2 +	COffset.Y + 235.f }, 0.5f, 0.5f);
	FileManager::Get_Instance()->Append_Image(DC, L"Ground", { 350.f, DEFAULT_WINDOW_CY / 2 +	COffset.Y + 235.f }, 0.5f, 0.5f);
	FileManager::Get_Instance()->Append_Image(DC, L"Ground", { 450.f,  DEFAULT_WINDOW_CY / 2 +	COffset.Y + 235.f }, 0.5f, 0.5f);
	FileManager::Get_Instance()->Append_Image(DC, L"Ground", { 550, DEFAULT_WINDOW_CY / 2 +		COffset.Y + 235.f }, 0.5f, 0.5f);
	FileManager::Get_Instance()->Append_Image(DC, L"Ground", { 650.f,  DEFAULT_WINDOW_CY / 2 +	COffset.Y + 235.f }, 0.5f, 0.5f);
	FileManager::Get_Instance()->Append_Image(DC, L"Ground", { 750.f, DEFAULT_WINDOW_CY / 2 +	COffset.Y + 235.f }, 0.5f, 0.5f);
	FileManager::Get_Instance()->Append_Image(DC, L"Ground", { 850.f, DEFAULT_WINDOW_CY / 2 +	COffset.Y + 235.f }, 0.5f, 0.5f);
	FileManager::Get_Instance()->Append_Image(DC, L"Ground", { 950.f, DEFAULT_WINDOW_CY / 2 +	COffset.Y + 235.f }, 0.5f, 0.5f);
	FileManager::Get_Instance()->Append_Image(DC, L"Ground", { 1050.f, DEFAULT_WINDOW_CY / 2 +	COffset.Y + 235.f }, 0.5f, 0.5f);
	FileManager::Get_Instance()->Append_Image(DC, L"Ground", { 1150.f, DEFAULT_WINDOW_CY / 2 +	COffset.Y + 235.f }, 0.5f, 0.5f);
	FileManager::Get_Instance()->Append_Image(DC, L"Ground", { 1250.f, DEFAULT_WINDOW_CY / 2 +	COffset.Y + 235.f }, 0.5f, 0.5f);

	FileManager::Get_Instance()->Append_Image(DC, L"BlackBoard", { 600.f, DEFAULT_WINDOW_CY / 2 + COffset.Y + 315.f }, 4.5f, 0.5f);
}

void Scene_Gate::Release()	{
	SAFE_DELETE_LIST<GameObject*>(*ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT));
}
void Scene_Gate::PlayAnimation_Once_Stable(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
	Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight) {
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	INT _FrameEndIndex = (INT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	GdiTransparentBlt(_SubWindowDC, StartLeft - CameraManager::Get_Instance()->GetOffset().X, StartTop - CameraManager::Get_Instance()->GetOffset().Y,
		Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		*_SPF * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));

	if (_AnimSpeed + dwTime[0] < GetTickCount() && *_SPF < _FrameEndIndex - 1) {
		*_SPF += 1;
		dwTime[0] = GetTickCount();
	}

	ReleaseDC(hWnd, MemDC);
}
void Scene_Gate::PlayAnimation_Reverse(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed,
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

	if (*_SPF <= 0) {
		*_SPF = -1;
	}

	if (_AnimSpeed + dwTime[0] < GetTickCount() && *_SPF <= _FrameEndIndex - 1) {
		*_SPF -= 1;
		dwTime[0] = GetTickCount();
	}
	
	ReleaseDC(hWnd, MemDC);
}
void Scene_Gate::PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer, INT LoopFrame,
	Vector2D _CenterPos, FLOAT _MultipleWidth, FLOAT _MultipleHeight) {
	HDC MemDC = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_SubDC();

	UINT Width = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPWidth();
	UINT Height = FileManager::Get_Instance()->Find_BMPFile(_KeyValue)->Get_BMPHeight();

	UINT _FrameEndIndex = (UINT)Width / _PixelPerFrame;

	FLOAT StartLeft = _CenterPos.X - (Width / _FrameEndIndex) * _MultipleWidth / 2.f;
	FLOAT StartTop = _CenterPos.Y - Height * _MultipleHeight / 2.f;

	if (_AnimSpeed + *Timer < GetTickCount()) {
		*_SPF += 1;
		*Timer = GetTickCount();

		if (*_SPF >= _FrameEndIndex) {
			*_SPF = LoopFrame;
		}
	}

	FLOAT OffsetX = CameraManager::Get_Instance()->GetOffset().X;
	FLOAT OffsetY = CameraManager::Get_Instance()->GetOffset().Y;

	GdiTransparentBlt(_SubWindowDC, StartLeft - OffsetX, StartTop - OffsetY, Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		*_SPF * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));

	ReleaseDC(hWnd, MemDC);
}