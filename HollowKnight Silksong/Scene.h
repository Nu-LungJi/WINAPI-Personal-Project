#pragma once
class Scene abstract {
public:
	Scene() {};
	virtual ~Scene() {};

public:
	virtual void	Initialize()		= 0;
	virtual void	Update()			= 0;
	virtual void	Late_Update()		= 0;
	virtual void	Render(HDC DC)		= 0;
	virtual void	Release()			= 0;

protected:
	DWORD		LoadingTime;
};