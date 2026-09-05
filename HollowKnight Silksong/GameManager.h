#pragma once
class GameManager {
public:
	GameManager();
	~GameManager();

public:
	void	Initialize()		;
	void	Update()			;
	void	LateUpdate()		;
	void	Render()			;
	void	Release()			;

	
public:
	void	DoubleBuffering();

private:
	HDC			MainWindowDC;
	HDC			SubWindowDC;
	HBITMAP		SubBitMap;

	Scene* TestScene;
	DWORD		dwTime;
};