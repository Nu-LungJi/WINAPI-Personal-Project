#pragma once
class Scene_Dungeon : public Scene {
public:
	Scene_Dungeon();
	virtual ~Scene_Dungeon();

public:
	void	Initialize()		override;
	void	Update()			override;
	void	Late_Update()		override;
	void	Render(HDC DC)		override;
	void	Release()			override;

private:
	GameObject*		Player;
	GameObject*		Portal_Gate;
	GameObject*		Portal_VILLAGE;
};