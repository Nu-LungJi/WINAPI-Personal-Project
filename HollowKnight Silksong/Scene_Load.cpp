#include "PCH.h"
#include "Scene_Load.h"

Scene_Load::Scene_Load()  :  dwTime( GetTickCount() ), SceneTransitionTime( GetTickCount() ), StartPixelFrame(0) {}
Scene_Load::~Scene_Load()	{ Release(); }

void Scene_Load::Initialize()	{}
void Scene_Load::Update()		{}
void Scene_Load::Late_Update()	{}
void Scene_Load::Release()		{}

void Scene_Load::Render(HDC DC) {
	if (SceneTransitionTime + 2000 >= GetTickCount()) {
		PlayAnimation_Loop(DC, L"Loading", &StartPixelFrame, 1280, 50, &dwTime, 0, { DEFAULT_WINDOW_CX / 2 + CameraManager::Get_Instance()->GetOffset().X,
		DEFAULT_WINDOW_CY / 2 + CameraManager::Get_Instance()->GetOffset().Y });
	}
	if (SceneTransitionTime + 2000 < GetTickCount()) {
		SceneManager::Get_Instance()->Scene_Transition(SceneManager::Get_Instance()->Get_NextScene());
	}
}

void Scene_Load::PlayAnimation_Loop(HDC _SubWindowDC, const TCHAR* _KeyValue, INT* _SPF, UINT _PixelPerFrame, UINT _AnimSpeed, DWORD* Timer, INT LoopFrame,
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

		if (*_SPF >= _FrameEndIndex) {	*_SPF = LoopFrame; }
	}

	FLOAT OffsetX = CameraManager::Get_Instance()->GetOffset().X;
	FLOAT OffsetY = CameraManager::Get_Instance()->GetOffset().Y;

	GdiTransparentBlt(_SubWindowDC, StartLeft - OffsetX, StartTop - OffsetY, Width * _MultipleWidth / _FrameEndIndex, Height * _MultipleHeight, MemDC,
		*_SPF * _PixelPerFrame, 0, _PixelPerFrame, Height, RGB(255, 0, 255));

	ReleaseDC(hWnd, MemDC);

}