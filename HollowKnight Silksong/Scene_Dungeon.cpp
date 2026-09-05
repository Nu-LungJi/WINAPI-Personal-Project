#include "PCH.h"
#include "Scene_Dungeon.h"

Scene_Dungeon::Scene_Dungeon()	{				}
Scene_Dungeon::~Scene_Dungeon() { Release();	}

void Scene_Dungeon::Initialize() {

	if (ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->size() < 1) {
		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_PLAYER, AbstractFactory<PlayerObject>::Create());
	}
	//ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_PLAYER, AbstractFactory<PlayerObject>::Create());
	Player = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front();
	Player->Set_Pos(3800, 4050);

	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_PORTAL, AbstractFactory<Portal>::Create());
	Portal_Gate = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PORTAL)->back();
	Portal_Gate->Set_Info(20.f, 3000.f, 20.f, 250.f);
	dynamic_cast<Portal*>(Portal_Gate)->Set_PortalTag(PTAG::DUNGEON_TO_GATE);	
	
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_PORTAL, AbstractFactory<Portal>::Create());
	Portal_VILLAGE = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PORTAL)->back();
	Portal_VILLAGE->Set_Info(4040.f, 3985.f, 20.f, 250.f);
	dynamic_cast<Portal*>(Portal_VILLAGE)->Set_PortalTag(PTAG::DUNGEON_TO_VILLAGE);

	CameraManager::Get_Instance()->SetTarget(Player);

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/BackGround_R.bmp", L"BackGround_Dungeon");

	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_MONSTER, AbstractFactory<MonsterObject>::Create(2100.f, 3200.f));
	dynamic_cast<MonsterObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_MONSTER)->back())->Set_MonsterType(MONSTER_TYPE::MONSTER_ENVOY);
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_MONSTER, AbstractFactory<MonsterObject>::Create(1020.f, 4740.f));
	dynamic_cast<MonsterObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_MONSTER)->back())->Set_MonsterType(MONSTER_TYPE::MONSTER_CHAMBER);
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_MONSTER, AbstractFactory<MonsterObject>::Create(1735.f, 3590.f));
	dynamic_cast<MonsterObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_MONSTER)->back())->Set_MonsterType(MONSTER_TYPE::MONSTER_ENVOY);
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_MONSTER, AbstractFactory<MonsterObject>::Create(2224.f, 4740.f));
	dynamic_cast<MonsterObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_MONSTER)->back())->Set_MonsterType(MONSTER_TYPE::MONSTER_CHAMBER);
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_MONSTER, AbstractFactory<MonsterObject>::Create(2123.f, 4260.f));
	dynamic_cast<MonsterObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_MONSTER)->back())->Set_MonsterType(MONSTER_TYPE::MONSTER_ENVOY);
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_MONSTER, AbstractFactory<MonsterObject>::Create(1500.f, 3200.f));
	dynamic_cast<MonsterObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_MONSTER)->back())->Set_MonsterType(MONSTER_TYPE::MONSTER_ENVOY);
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_MONSTER, AbstractFactory<MonsterObject>::Create(1620.f, 4740.f));
	dynamic_cast<MonsterObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_MONSTER)->back())->Set_MonsterType(MONSTER_TYPE::MONSTER_CHAMBER);
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_MONSTER, AbstractFactory<MonsterObject>::Create(2135.f, 3590.f));

	//dynamic_cast<MonsterObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_MONSTER)->back())->Set_MonsterType(MONSTER_TYPE::MONSTER_ENVOY);
	//ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_MONSTER, AbstractFactory<MonsterObject>::Create(724.f, 3060.f));
	//dynamic_cast<MonsterObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_MONSTER)->back())->Set_MonsterType(MONSTER_TYPE::MONSTER_CHAMBER);
	//ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_MONSTER, AbstractFactory<MonsterObject>::Create(1323.f, 4260.f));
	//dynamic_cast<MonsterObject*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_MONSTER)->back())->Set_MonsterType(MONSTER_TYPE::MONSTER_ENVOY);
}
void Scene_Dungeon::Update()		{ }
void Scene_Dungeon::Late_Update()	{ }
void Scene_Dungeon::Render(HDC DC)  {
	Vector2D COffset = CameraManager::Get_Instance()->GetOffset();

	FileManager::Get_Instance()->Append_Image(DC, L"BackGround_Dungeon", { DEFAULT_WINDOW_CX / 2 + COffset.X, DEFAULT_WINDOW_CY / 2 + COffset.Y - 10 });
}
void Scene_Dungeon::Release() {
	SAFE_DELETE_LIST<GameObject*>(*ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_MONSTER));
	SAFE_DELETE_LIST<GameObject*>(*ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT));
	SAFE_DELETE_LIST<GameObject*>(*ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PORTAL));
}

