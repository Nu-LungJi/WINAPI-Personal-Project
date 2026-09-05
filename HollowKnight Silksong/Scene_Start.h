#pragma once
class Scene_Start : public Scene {
public:
	Scene_Start();
	virtual ~Scene_Start();

public:
	void Initialize()			override;
	void Update()				override;
	void Late_Update()			override;
	void Render(HDC DC)			override;
	void Release()				override;

private:
	vector<GameObject*>		ButtonList;
	BOOL					PrevFrameState;
	BOOL					CurrFrameState;
};

