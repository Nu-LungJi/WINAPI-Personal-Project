#pragma once
class Scene_Village :  public Scene {
public:
	Scene_Village();
	virtual ~Scene_Village();

public:
	void	Initialize()		override;
	void	Update()			override;
	void	Late_Update()		override;
	void	Render(HDC DC)		override;
	void	Release()			override;

private:
	GameObject*		Player;
	GameObject*		Portal01;
	GameObject*		Portal02;
	list<GameObject*>*		NPCList;

	DWORD		dwTime;
};

