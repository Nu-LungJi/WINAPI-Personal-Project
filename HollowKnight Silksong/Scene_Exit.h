#pragma once
#include "Scene.h"
class Scene_Exit : public Scene  {
public:
	Scene_Exit();
	virtual ~Scene_Exit();
public:
	void	Initialize()		override;
	void	Update()			override;
	void	Late_Update()		override;
	void	Render(HDC DC)		override;
	void	Release()			override;

private:
	vector<GameObject*>		ButtonList;
	DWORD					dwTime;
};

