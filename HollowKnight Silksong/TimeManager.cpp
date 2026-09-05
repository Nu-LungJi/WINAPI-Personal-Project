#include "PCH.h"
#include "TimeManager.h"
TimeManager* TimeManager::Instance = nullptr;
TimeManager::TimeManager()	: Time(GetTickCount()), FPS_Value(0), DeltaTime(0){				}
TimeManager::~TimeManager() {	Release();	}

void TimeManager::Update() {
	CurrentTime = GetTickCount();
}
void TimeManager::Render(HDC DC){
	++FPS_Value;

	if (Time + 1000 < GetTickCount())	{
		swprintf_s(FPS, L"FPS : %d || DeltaTime : %lf", FPS_Value, DeltaTime);
		SetWindowText(hWnd, FPS);

		FPS_Value = 0;
		DeltaTime = (CurrentTime - Time) / 1000;
		Time = GetTickCount();

	}
	else {
		CurrentTime = GetTickCount();
	}
}

void TimeManager::Change_WindowTitle()
{
}
