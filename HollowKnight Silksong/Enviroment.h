#pragma once
#include "GameObject.h"

enum class ENV_TYPE {ENV_NORMAL, ENV_OBSTACLE};

class Enviroment : public GameObject {
public:
	Enviroment();
	virtual ~Enviroment();

public:
	void Initialize()																override;
	int Update()																	override;
	void Late_Update()																override;
	void Render(HDC DC)																override;
	void Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value)		override;
	void Release()																	override;

public:
	void		Set_EnvTag(ENV_TYPE _ET)	{ Enviroment_Type = _ET;  }
	ENV_TYPE	Get_EnvTag()				{ return Enviroment_Type; }

private:
	ENV_TYPE	Enviroment_Type;
	GameObject* Player;

	DWORD		dwTime;
};

