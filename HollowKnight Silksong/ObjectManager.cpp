#include "PCH.h"
#include "ObjectManager.h"

ObjectManager* ObjectManager::Instance = nullptr;

ObjectManager::ObjectManager(){}
ObjectManager::~ObjectManager() {
	Release(); }

void ObjectManager::Initialize() {
}
void ObjectManager::Update() {
	for (size_t i = 0; i < (LONG)OBJECT_TAG::OBJ_END; ++i)
	{
		for (auto iter = ObjectList[i].begin();
			iter != ObjectList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (iResult == OBJ_DEAD)
			{
				SAFE_DELETE<GameObject*>(*iter);
				iter = ObjectList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}
void ObjectManager::Late_Update() {
	for (size_t i = 0; i < (LONG)OBJECT_TAG::OBJ_END; ++i)
	{
		for (auto& pObj : ObjectList[i])
		{
			pObj->Late_Update();

			if (ObjectList[i].empty())
				break;
		}
	}
	CollisionManager::Collision_RectEx(ObjectList[(LONG)OBJECT_TAG::OBJ_ENVIROMENT], ObjectList[(LONG)OBJECT_TAG::OBJ_PLAYER] );
	CollisionManager::Collision_RectEx(ObjectList[(LONG)OBJECT_TAG::OBJ_ENVIROMENT], ObjectList[(LONG)OBJECT_TAG::OBJ_MONSTER]);
	CollisionManager::Collision_RectEx(ObjectList[(LONG)OBJECT_TAG::OBJ_ENVIROMENT], ObjectList[(LONG)OBJECT_TAG::OBJ_BOSS]);

	CollisionManager::Collision_RectEx(ObjectList[(LONG)OBJECT_TAG::OBJ_BOSS], ObjectList[(LONG)OBJECT_TAG::OBJ_PLAYER_HITBOX]);
	CollisionManager::Collision_RectEx(ObjectList[(LONG)OBJECT_TAG::OBJ_MONSTER], ObjectList[(LONG)OBJECT_TAG::OBJ_PLAYER_HITBOX]);

	CollisionManager::Collision_RectEx(ObjectList[(LONG)OBJECT_TAG::OBJ_PLAYER], ObjectList[(LONG)OBJECT_TAG::OBJ_BOSS]);
	CollisionManager::Collision_RectEx(ObjectList[(LONG)OBJECT_TAG::OBJ_PLAYER], ObjectList[(LONG)OBJECT_TAG::OBJ_BOSS_HITBOX]);
	CollisionManager::Collision_RectEx(ObjectList[(LONG)OBJECT_TAG::OBJ_PLAYER], ObjectList[(LONG)OBJECT_TAG::OBJ_BOSS_HITBOX_CIRCLE]);

	CollisionManager::Collision_RectEx(ObjectList[(LONG)OBJECT_TAG::OBJ_PLAYER], ObjectList[(LONG)OBJECT_TAG::OBJ_MONSTER]);
	CollisionManager::Collision_RectEx(ObjectList[(LONG)OBJECT_TAG::OBJ_PLAYER], ObjectList[(LONG)OBJECT_TAG::OBJ_MONSTER_HITBOX]);

	CollisionManager::Collision_RectEx(ObjectList[(LONG)OBJECT_TAG::OBJ_PLAYER], ObjectList[(LONG)OBJECT_TAG::OBJ_NPC]);

	CollisionManager::Collision_RectEx(ObjectList[(LONG)OBJECT_TAG::OBJ_PLAYER], ObjectList[(LONG)OBJECT_TAG::OBJ_PORTAL]);
	CollisionManager::Collision_RectEx(ObjectList[(LONG)OBJECT_TAG::OBJ_ENVIROMENT], ObjectList[(LONG)OBJECT_TAG::OBJ_PLAYER_HITBOX]);
}
void ObjectManager::Render(HDC DC) {

	for (size_t i = 0; i < (LONG)OBJECT_TAG::OBJ_END; ++i)
	{
		for (auto& pObj : ObjectList[i])
		{
			pObj->Render(DC);
		}
		if (i == (LONG)OBJECT_TAG::OBJ_FRONT_ENVIROMENT) {
			MapManager::Get_Instance()->Render_Forward(DC);
		}
	}
	
}

void ObjectManager::AddObject(OBJECT_TAG eID, GameObject* pObj) {

	if (pObj == nullptr || eID >= OBJECT_TAG::OBJ_END) return;

	ObjectList[(LONG)eID].push_back(pObj);
}

GameObject* ObjectManager::Get_Target(OBJECT_TAG eID, GameObject* pObj) {
	if (ObjectList[(LONG)eID].empty())
		return nullptr;

	GameObject* pTarget = nullptr;

	float	fDistance = 0.f;

	for (auto& Dst : ObjectList[(LONG)eID])
	{
		float	fWidth = Dst->Get_Info()->CenterPosX - pObj->Get_Info()->CenterPosX;
		float	fHeight = Dst->Get_Info()->CenterPosY - pObj->Get_Info()->CenterPosY;

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = Dst;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}
list< GameObject* >* ObjectManager::Get_ObjectList(OBJECT_TAG eObjID)
{
	return &ObjectList[(LONG)eObjID];
}
GameObject* ObjectManager::Get_ObjectTile(OBJECT_TAG eObjID, FLOAT _X, FLOAT _Y) {
	for (list< GameObject* >::iterator iter = ObjectList[(LONG)eObjID].begin(); iter != ObjectList[(LONG)eObjID].end();) {
		if ((*iter)->Get_Pos().X == _X) {
			return *iter;
		}
		else {
			iter++;
		}
	}
}
void ObjectManager::Release() {
	for (size_t i = 0; i < (LONG)OBJECT_TAG::OBJ_END; ++i)
	{
		for_each(ObjectList[i].begin(), ObjectList[i].end(), SAFE_DELETE<GameObject*>);
		ObjectList[i].clear();
	}
}