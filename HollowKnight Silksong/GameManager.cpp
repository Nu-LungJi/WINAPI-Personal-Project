#include "PCH.h"
#include "GameManager.h"
#include "TimeManager.h"

GameManager::GameManager() {  }
GameManager::~GameManager()	{   Release();	}

void GameManager::Initialize()	{
	MainWindowDC = GetDC(hWnd);
	
	DoubleBuffering();
	SoundManager::Get_Instance()->Initialize();
	CameraManager::Get_Instance()->Initialize();
	SceneManager::Get_Instance()->Initialize();
	KeyManager::Get_Instance()->Initialize();
	ObjectManager::Get_Instance()->Initialize();
	MapManager::Get_Instance()->Initialize();
}
void GameManager::Update()		{
	CameraManager::Get_Instance()->Update();
	KeyManager::Get_Instance()->Update();
	TimeManager::Get_Instance()->Update();
	SceneManager::Get_Instance()->Update();
	FileManager::Get_Instance()->Update();
	ObjectManager::Get_Instance()->Update();

}
void GameManager::LateUpdate()	{
	SceneManager::Get_Instance()->Late_Update();
	ObjectManager::Get_Instance()->Late_Update();
}
void GameManager::Render()		{
	SceneManager::Get_Instance()->Render(SubWindowDC);
	TimeManager::Get_Instance()->Render(SubWindowDC);
	if (SceneManager::Get_Instance()->Get_CurrentScene() != STAGE_TYPE::STAGE_LOAD) {
		MapManager::Get_Instance()->Render_Backward(SubWindowDC);
		ObjectManager::Get_Instance()->Render(SubWindowDC);
	}
	CameraManager::Get_Instance()->Render(SubWindowDC);
	BitBlt(MainWindowDC, 0, 0, DEFAULT_WINDOW_CX + 8, DEFAULT_WINDOW_CY + 8, SubWindowDC, 0, 0, SRCCOPY);
}
void GameManager::Release()		{

	FileManager::Destroy_Instance();
	TimeManager::Destroy_Instance();
	//TileManager::Destroy_Instance();
	MapManager::Destroy_Instance();
	KeyManager::Destroy_Instance();
	SceneManager::Destroy_Instance();
	ObjectManager::Destroy_Instance();
	CameraManager::Destroy_Instance();
	SoundManager::Destroy_Instance();
	DeleteObject(SubBitMap);
	DeleteDC(SubWindowDC);
	ReleaseDC(hWnd, MainWindowDC);
}

void GameManager::DoubleBuffering() {

	RECT DCArea = { 0, 0, DEFAULT_WINDOW_CX, DEFAULT_WINDOW_CY };

	GetClientRect(hWnd, &DCArea);

	SubBitMap = CreateCompatibleBitmap(MainWindowDC, DCArea.right, DCArea.bottom);
	SubWindowDC = CreateCompatibleDC(MainWindowDC);

	HBITMAP PastBitMap = (HBITMAP)::SelectObject(SubWindowDC, SubBitMap);
	DeleteObject(PastBitMap);
}
