#include "PCH.h"
#include "CameraManager.h"

CameraManager* CameraManager::Instance = nullptr;
CameraManager::CameraManager()	: CameraTarget(nullptr), ChaseTime(1.f), CameraSpeed(0.f), TimeAccumaltion(0.f), CameraShakeTime(0.f), dwTime(GetTickCount()-2000),
	TempOffset{0.f, 0.f} { }
CameraManager::~CameraManager() { Release(); }

void CameraManager::Initialize() {
	
	
}
void CameraManager::Update(){
	if (CameraTarget) {
		CameraCenterPos.X = CameraTarget->Get_Pos().X + TempOffset.X;
		CameraCenterPos.Y = CameraTarget->Get_Pos().Y + TempOffset.Y;
	}
	else {
		CameraTarget = nullptr;
	}

	if (CameraCenterPos.X < DEFAULT_WINDOW_CX >> 1)
		CameraCenterPos.X = DEFAULT_WINDOW_CX >> 1;

	if (CameraCenterPos.Y < DEFAULT_WINDOW_CY >> 1)
		CameraCenterPos.Y = DEFAULT_WINDOW_CY >> 1;

	if (SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_VILLAGE) {
		if (CameraCenterPos.X > DEFAULT_WINDOW_CX / 2 + 2800) {
			CameraCenterPos.X = DEFAULT_WINDOW_CX / 2 + 2800;
		}
		if (CameraCenterPos.Y > DEFAULT_WINDOW_CY / 2 + 4200) {
			CameraCenterPos.Y = DEFAULT_WINDOW_CY / 2 + 4200;
		}
	}
	if (SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_DUNGEON) {
		if (CameraCenterPos.X > DEFAULT_WINDOW_CX / 2 + 2800) {
			CameraCenterPos.X = DEFAULT_WINDOW_CX / 2 + 2800;
		}
		if (CameraCenterPos.Y > DEFAULT_WINDOW_CY / 2 + 4200) {
			CameraCenterPos.Y = DEFAULT_WINDOW_CY / 2 + 4200;
		}
		if (CameraCenterPos.Y < DEFAULT_WINDOW_CY / 2 + 1500) {
			CameraCenterPos.Y = DEFAULT_WINDOW_CY / 2 + 1500;
		}
	}
	if (SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_GATE) {
		if (CameraCenterPos.X > DEFAULT_WINDOW_CX / 2 ) {
			CameraCenterPos.X = DEFAULT_WINDOW_CX / 2 ;
		}
		if (CameraCenterPos.Y > DEFAULT_WINDOW_CY / 2 ) {
			CameraCenterPos.Y = DEFAULT_WINDOW_CY / 2 ;
		}
	}
	if (SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_BOSS) {
		if (CameraCenterPos.X > DEFAULT_WINDOW_CX / 2 + 200) {
			CameraCenterPos.X = DEFAULT_WINDOW_CX / 2 + 200;
		}
		if (CameraCenterPos.Y > DEFAULT_WINDOW_CY / 2) {
			CameraCenterPos.Y = DEFAULT_WINDOW_CY / 2;
		}
	}
	Set_ShakePosition();

	CalDiff();
}
void CameraManager::Late_Update(){

}
void CameraManager::Render(HDC DC) {}
void CameraManager::Release(){

}

BOOL CameraManager::Set_ShakePosition()
{
	if (dwTime + CameraShakeTime >= GetTickCount()) {
		CameraCenterPos.X += (rand() % CameraShakeStrength - CameraShakeStrength / 2.f);
		CameraCenterPos.Y += (rand() % CameraShakeStrength - CameraShakeStrength / 2.f);
	}
	return true;
}

void CameraManager::Camera_FadeIn(HDC DC) {
}

void CameraManager::Camera_FadeOut(HDC DC) {

}

void CameraManager::CalDiff() {
	TimeAccumaltion += TimeManager::Get_Instance()->Get_DeltaTime();
	if (TimeAccumaltion >= ChaseTime) {
		CurrCameraPos = CameraCenterPos;
	}
	else {
		Vector2D Direction = CameraCenterPos - PrevCameraPos;
		CurrCameraPos = PrevCameraPos + Direction.Normalize() * CameraSpeed * TimeManager::Get_Instance()->Get_DeltaTime();
	}

	Vector2D Center = Vector2D(DEFAULT_WINDOW_CX / 2, DEFAULT_WINDOW_CY / 2);

	CameraOffset = CurrCameraPos - Center;
	PrevCameraPos = CurrCameraPos;
}