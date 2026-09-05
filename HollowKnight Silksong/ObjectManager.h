#pragma once
#include "GameObject.h"

class ObjectManager {
	COMPONENT_SINGLETON(ObjectManager)
public:
	void	Initialize();
	void	Update();
	void	Late_Update();
	void	Render(HDC DC);
	void	Release();

public:
	void						AddObject(OBJECT_TAG eID, GameObject* pObj = nullptr);
	GameObject*					Get_Target(OBJECT_TAG eID, GameObject* pObj);
	list< GameObject* >*		Get_ObjectList(OBJECT_TAG eObjID);
	GameObject*					Get_ObjectTile(OBJECT_TAG eObjID, FLOAT _X, FLOAT _Y);

private:
	list<GameObject*>	ObjectList[(LONG)OBJECT_TAG::OBJ_END];
};

