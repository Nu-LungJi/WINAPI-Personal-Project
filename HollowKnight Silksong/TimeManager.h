#pragma once
class TimeManager {
	COMPONENT_SINGLETON(TimeManager)
public:
	void	Initialize()		{};
	void	Update()			  ;
	void	LateUpdate()		{};
	void	Render(HDC DC)		  ;
	void	Release()			{};

	void	Change_WindowTitle();
	FLOAT	Get_DeltaTime() { return DeltaTime; }

private:
	WCHAR		FPS[100];
	INT			FPS_Value;
	DWORD		Time;
	FLOAT		DeltaTime;
	FLOAT		CurrentTime;
};

