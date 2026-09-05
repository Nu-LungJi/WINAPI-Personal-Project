#pragma once
class CollisionManager
{
public:
	static void Collision_Rect(list<GameObject*> _Dst, list<GameObject*> _Src);

	static void Collision_RectEx(list<GameObject*> _Dst, list<GameObject*> _Src);
	static bool	Check_Rect(GameObject* pDst, GameObject* pSrc, float* pX, float* pY);

	static bool Check_Circle(GameObject* pDst, GameObject* pSrc);
	static void Collision_Circle(list<GameObject*> _Dst, list<GameObject*> _Src);

	static bool	Check_Collision(list<GameObject*> _Dst, list<GameObject*> _Src);
	static bool	Check_Collision(GameObject* _Dst, GameObject* _Src);
};

