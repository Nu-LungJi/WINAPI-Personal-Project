#include "PCH.h"
#include "Scene_Village.h"

Scene_Village::Scene_Village()		{				}
Scene_Village::~Scene_Village()		{  Release();	}

void Scene_Village::Initialize() {

	if (ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->size() < 1) {
		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_PLAYER, AbstractFactory<PlayerObject>::Create());
	}
	
	Player = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front();
	Player->Set_Pos(4000, 4700);

	CameraManager::Get_Instance()->SetTarget(Player);
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/BackGround_R.bmp", L"BackGround_Village");

	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_PORTAL, AbstractFactory<Portal>::Create());
	Portal01 = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PORTAL)->front();
	Portal01->Set_Pos(25.f, 4050.f);
	dynamic_cast<Portal*>(Portal01)->Set_PortalTag(PTAG::VILLAGE_TO_DUNGEON);

	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_NPC, new NPC(1700, 4656, NPC_BIGPULP_PIXELFRAME, NPC_BIGPULP_PIXELFRAME, NPC_TAG::NPC_BIGPULP));

	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_NPC, new NPC(2785, 4706, NPC_SHERMA_PIXELFRAME, NPC_SHERMA_PIXELFRAME, NPC_TAG::NPC_SHERMA));
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_NPC, new NPC(2300, 4710, NPC_SPECIAL_SHERMA_PIXELFRAME, NPC_SPECIAL_SHERMA_PIXELFRAME, NPC_TAG::NPC_SPECIALSHERMA));
	//ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_NPC, new NPC(1400, 4720, NPC_BIGBUG_PIXELFRAME, NPC_BIGBUG_PIXELFRAME, NPC_TAG::NPC_BIGBUG));
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_NPC, new NPC(3650, 4718, NPC_GHOUL_PIXELFRAME, NPC_GHOUL_PIXELFRAME, NPC_TAG::NPC_GHOUL));
	
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_NPC, new NPC(1324, 4415, NPC_PULP_FAMILY_PIXELFRAME, NPC_PULP_FAMILY_PIXELFRAME, NPC_TAG::NPC_PULP_FAMILY));
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_NPC, new NPC(1524, 4420, NPC_PULP_PIXELFRAME, NPC_PULP_PIXELFRAME, NPC_TAG::NPC_PULP));
	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_NPC, new NPC(3215, 4687, NPC_FLEA_PIXELFRAME, NPC_FLEA_PIXELFRAME, NPC_TAG::NPC_FLEA));

	ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_UI, AbstractFactory<StoreUI>::Create());
	dynamic_cast<StoreUI*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_UI)->back())->
		Set_StoreManager(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_NPC)->front());

	NPCList = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_NPC);
	for (auto& NPC : *NPCList) {
		NPC->Initialize();
	}
}
void Scene_Village::Update()		{	}
void Scene_Village::Late_Update()	{	}
void Scene_Village::Render(HDC DC)  {
	Vector2D COffset = CameraManager::Get_Instance()->GetOffset();
	FileManager::Get_Instance()->Append_Image(DC, L"BackGround_Village", { DEFAULT_WINDOW_CX / 2 + COffset.X, DEFAULT_WINDOW_CY / 2 + COffset.Y });
}

void Scene_Village::Release() {
	SAFE_DELETE_LIST<GameObject*>(*ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_NPC));
	SAFE_DELETE_LIST<GameObject*>(*ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PORTAL));
	SAFE_DELETE(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_UI)->back());
	ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_UI)->pop_back();
	SAFE_DELETE_LIST<GameObject*>(*ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT));
}
