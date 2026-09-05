#include "PCH.h"
#include "CollisionManager.h"

void CollisionManager::Collision_Rect(list<GameObject*> _Dst, list<GameObject*> _Src) {

}

void CollisionManager::Collision_RectEx(list<GameObject*> _Dst, list<GameObject*> _Src) {
	float	fWidth(0.f), fHeight(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{
				// 상 하 충돌
				if (fWidth > fHeight)
				{
					// 상 충돌
					if (Dst->Get_Info()->CenterPosY < Src->Get_Info()->CenterPosY)
					{
						Dst->Collision_Update(Src, COLLISION_TYPE::COL_TOP, fHeight);
						Src->Collision_Update(Dst, COLLISION_TYPE::COL_TOP, fHeight);
					}
					// 하 충돌
					else
					{
						Dst->Collision_Update(Src, COLLISION_TYPE::COL_BOTTOM, -fHeight);
						Src->Collision_Update(Dst, COLLISION_TYPE::COL_BOTTOM, -fHeight);
					}
				}

				// 좌 우 충돌
				else
				{
					// 좌 충돌
					if (Dst->Get_Info()->CenterPosX < Src->Get_Info()->CenterPosX)
					{
						Dst->Collision_Update(Src, COLLISION_TYPE::COL_LEFT , fWidth);
						Src->Collision_Update(Dst, COLLISION_TYPE::COL_LEFT, fWidth);
					}
					// 우 충돌
					else
					{
						Dst->Collision_Update(Src, COLLISION_TYPE::COL_RIGHT, -fWidth);
						Src->Collision_Update(Dst, COLLISION_TYPE::COL_RIGHT, -fWidth);
					}
				}
			}
			else {

			}
		}
	}
}

bool CollisionManager::Check_Rect(GameObject* pDst, GameObject* pSrc, float* pX, float* pY)
{
	float		fWidth = fabsf(pDst->Get_Info()->CenterPosX - pSrc->Get_Info()->CenterPosX);
	float		fHeight = fabsf(pDst->Get_Info()->CenterPosY - pSrc->Get_Info()->CenterPosY);

	float		fRadiusX = (pDst->Get_Info()->Width + pSrc->Get_Info()->Width) * 0.5f;
	float		fRadiusY = (pDst->Get_Info()->Height + pSrc->Get_Info()->Height) * 0.5f;

	if (fRadiusX >= fWidth && fRadiusY >= fHeight)
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}

bool CollisionManager::Check_Circle(GameObject* pDst, GameObject* pSrc)
{
	float	fRadius = (pDst->Get_Info()->Width + pSrc->Get_Info()->Width) * 0.5f;

	float	fWidth = fabsf(pDst->Get_Info()->CenterPosX - pSrc->Get_Info()->CenterPosX);
	float	fHeight = fabsf(pDst->Get_Info()->CenterPosY - pSrc->Get_Info()->CenterPosY);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	return fRadius >= fDiagonal;
}

void CollisionManager::Collision_Circle(list<GameObject*> _Dst, list<GameObject*> _Src) {
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Circle(Dst, Src))
			{

			}
		}
	}
}

bool CollisionManager::Check_Collision(list<GameObject*> _Dst, list<GameObject*> _Src)
{
	float	fWidth(0.f), fHeight(0.f);
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{
				return true;
			}
		}
	}

	return false;

}

bool CollisionManager::Check_Collision(GameObject* _Dst, GameObject* _Src)
{
	float	fWidth(0.f), fHeight(0.f);
	if (Check_Rect(_Dst, _Src, &fWidth, &fHeight))
	{
		return true;
	}

	return false;
}
