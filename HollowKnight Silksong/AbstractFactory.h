#pragma once
#include "GameObject.h"

template<typename T>
class AbstractFactory
{
public:
	AbstractFactory() {}
	~AbstractFactory() {}

public:
	static GameObject* Create()
	{
		GameObject* GObject = new T;
		GObject->Initialize();

		return GObject;
	}
	static GameObject* Create(FLOAT _CX, FLOAT _CY)
	{
		GameObject* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_CX, _CY);

		return pObj;
	}
	static GameObject* Create(FLOAT _CX, FLOAT _CY, FLOAT _WDT, FLOAT _HGT)
	{
		GameObject* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_CX, _CY);
		pObj->Set_Scale(_WDT, _HGT);

		return pObj;
	}
};

