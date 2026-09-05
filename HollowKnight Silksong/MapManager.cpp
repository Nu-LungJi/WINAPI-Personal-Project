#include "PCH.h"
#include "MapManager.h"

MapManager* MapManager::Instance = nullptr;
MapManager::MapManager() : XVALUE(0), YVALUE(0), Player(nullptr){}
MapManager::~MapManager() {}

void MapManager::Initialize() {

	MapGenerator_Village_Initialize();
	MapGenerator_Dungeon_Initialize();
	UI_Initialize();
	Player_Initialize();

	if (SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_START) {
		SoundManager::Get_Instance()->PlaySound(L"Title.WAV", CHANNELID::SOUND_BGM, 1.f);
	}
	if (SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_VILLAGE) {
 		SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_BGM);
		SoundManager::Get_Instance()->PlaySound(L"SongClave.WAV", CHANNELID::SOUND_BGM, 0.5f);
	}
	if (SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_BOSS) {
		SoundManager::Get_Instance()->StopSound(CHANNELID::SOUND_BGM);
		//SoundManager::Get_Instance()->PlayBGM(L"Boss_BGM.WAV", 0.6f);
		SoundManager::Get_Instance()->PlaySound(L"Boss_Entering03.WAV", CHANNELID::SOUND_BGM, 1.f);
	}
}
void MapManager::Update() {		}
void MapManager::Render_Backward(HDC DC) {


	if (Player == nullptr && SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_VILLAGE) {
		Player = ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_PLAYER)->front();
	}

	MapGenerator_Village_Back(DC);
	MapGenerator_Dungeon_Back(DC);
}
void MapManager::Render_Forward(HDC DC)	{
	MapGenerator_Village_Front(DC);
	MapGenerator_Dungeon_Front(DC);
}

void MapManager::MapGenerator_Village_Initialize() {
	if (SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_VILLAGE) {

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Corner01.bmp", L"Corner01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Corner02.bmp", L"Corner02");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Corner03.bmp", L"Corner03");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Corner04.bmp", L"Corner04");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Corner05.bmp", L"Corner05");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Corner04_Flip.bmp", L"Corner04_Flip");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Wall01.bmp", L"Wall01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Wall02.bmp", L"Wall02");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Wall03.bmp", L"Wall03");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Wall04.bmp", L"Wall04");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Wall05.bmp", L"Wall05");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Wall06.bmp", L"Wall06");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Wall05_Flip.bmp", L"Wall05_Flip");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Curtain01.bmp", L"Curtain01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Curtain02.bmp", L"Curtain02");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Curtain04.bmp", L"Curtain03");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Floor01.bmp", L"Floor01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Floor02.bmp", L"Floor02");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Floor03.bmp", L"Floor03");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Floor04.bmp", L"Floor04");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Floor05.bmp", L"Floor05");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Floor06.bmp", L"Floor06"); // 200
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Floor07.bmp", L"Floor07"); // 163
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Floor08.bmp", L"Floor08"); // 163
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Floor09.bmp", L"Floor09"); // 169

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Floor_Wide01.bmp", L"Floor_Wide01"); // 163
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Floor_Wide02.bmp", L"Floor_Wide02"); // 169

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Float_Floor01.bmp", L"Float_Floor01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Float_Floor02.bmp", L"Float_Floor02");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Float_Floor03.bmp", L"Float_Floor03");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Float_Floor04.bmp", L"Float_Floor04");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Bell_Corner01.bmp", L"Bell_Corner01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Bell_Corner02.bmp", L"Bell_Corner02");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Bell_Corner03.bmp", L"Bell_Corner03");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Bell_Corner04.bmp", L"Bell_Corner04");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Sign01.bmp", L"Sign01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Sign02.bmp", L"Sign02");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/SignBoard.bmp", L"Sign03");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Table.bmp", L"Table");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Star01.bmp", L"Star01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Star02.bmp", L"Star02");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Chain.bmp", L"Chain");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Bell_Chain.bmp", L"Bell_Chain");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Deco03.bmp", L"Deco01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Deco04.bmp", L"Deco02");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Deco05.bmp", L"Deco03");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Ceiling01.bmp", L"Ceiling01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Ceiling02.bmp", L"Ceiling02");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Ceiling_Corner01.bmp", L"Ceiling_Corner01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Ceiling_Corner02.bmp", L"Ceiling_Corner02");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Ceiling_Corner03.bmp", L"Ceiling_Corner03");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Ceiling_Corner04.bmp", L"Ceiling_Corner04");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Ceiling_Corner05.bmp", L"Ceiling_Corner05");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Side_Corner01.bmp", L"Side_Corner01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Side_Corner02.bmp", L"Side_Corner02");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/BlackBoard.bmp", L"Village_BlackBoard");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Back_Bar01.bmp", L"Back_Bar01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Back_Bar03.bmp", L"Back_Bar02");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Fore_Bar01.bmp", L"Fore_Bar01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Fore_Bar02.bmp", L"Fore_Bar02");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Deco02.bmp", L"Chair");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Village/Right_Side.bmp", L"RSide");

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(100 + 180 * 15, 4794, 200 + 180 * 30, 90);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(5000, 4794 - 300, 50, 2000);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(25, 4794 - 300, 50, 2000);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(400, 4450, 50, 600);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(200, 4170, 400, 50);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(780, 4300, 50, 230);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(830, 4300, 50, 230);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(910, 4160, 340, 50);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(700, 3775, 1300, 50);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(1400, 4480, 400, 50);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(2300, 4280, 400, 50);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3300, 4380, 280, 50);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3040, 4080, 280, 50);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3830, 3860, 560, 20);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3950, 4260, 360, 20);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3740, 4080, 20, 400);

		ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
		ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(4100, 4060, 50, 2000);
	}
}
void MapManager::MapGenerator_Dungeon_Initialize()	{
	if (SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_DUNGEON) {
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/BlackBoard.bmp", L"BlackBoard");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Corner_Arch01.bmp", L"Corner_Arch01");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Wall01.bmp", L"Dungeon_Wall01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Wall01_Flip.bmp", L"Wall01_Flip");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Ceiling01.bmp", L"Dungeon_Ceiling01");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Ceiling_Corner01.bmp", L"Dungeon_Ceiling_Corner01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Ceiling_Corner02.bmp", L"Dungeon_Ceiling_Corner02");
		
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Floor_Long.bmp", L"Floor_Long");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Float_Floor01.bmp", L"Dungeon_Float_Floor01");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Floor01.bmp", L"Floor01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Floor02.bmp", L"Floor02");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Floor03.bmp", L"Floor03");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Floor04.bmp", L"Floor04");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Floor_Wide01.bmp", L"Dungeon_Floor_Wide01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Floor_Wide02.bmp", L"Dungeon_Floor_Wide02");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Chain.bmp", L"Dungeon_Chain");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Star01.bmp", L"Dungeon_Star01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Star02.bmp", L"Dungeon_Star02");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Spear_Field01.bmp", L"Spear_Field01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Spear_Field01_Flip.bmp", L"Spear_Field01_Flip");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Spear_Ceiling01.bmp", L"Spear_Ceiling01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Spear_Ceiling01_Flip.bmp", L"Spear_Ceiling01_Flip");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/WorldWall01.bmp", L"Spear_Wall01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/WorldWall02.bmp", L"Spear_Wall02");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/SpongeWall.bmp", L"SpongeWall");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/WorldWall01_Flip.bmp", L"Spear_Wall01_Flip");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/WorldWall02_Flip.bmp", L"Spear_Wall02_Flip");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/SpongeWall_Flip.bmp", L"SpongeWall_Flip");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Bell_Corner.bmp", L"Bell_Corner");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Bell_SideWall.bmp", L"SideWall99");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Chain.bmp", L"Dungeon_Chain");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Room01.bmp", L"Room01");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Room02.bmp", L"Room02");

		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Chair.bmp", L"Dungeon_Chair");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Gate.bmp", L"Gate");
		FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Arch/Dungeon/Sign.bmp", L"Dungeon_Sign");
		///////////////////////////////////////////// COLLISION //////////////////////////////////////////////////
		{
			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(10, 3000, 20, 4000);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(4050, 3000, 20, 4000);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(2720, 3570, 20, 700);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(2820, 2205, 20, 1400);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(420, 3880, 20, 1500);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(2970, 3185, 590, 50);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3035, 2930, 440, 50);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3235, 3060, 40, 205);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(460, 20, 20, 2000);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(1800, 4810, 3000, 20);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(2880, 4650, 20, 300);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(2720, 4510, 300, 20);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(2590, 4330, 340, 20);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(2580, 4420, 20, 160);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(1125, 3120, 500, 50);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(290, 3150, 540, 60);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(235, 2810, 430, 20);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(1325, 4270, 360, 50);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(1750, 3675, 500, 50);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(2075, 3290, 360, 50);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(900, 3920, 360, 50);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3880, 4120, 350, 20);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3890, 3795, 350, 20);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3720, 4180, 20, 100);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(1900, 4520, 170, 20);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(2960, 3055, 20, 200);
		}
		///////////////////////////////////////////// OBSTACLE ///////////////////////////////////////////////////
		{
			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(2800, 4360, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(2850, 4360, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(2900, 4360, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(2950, 4340, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3000, 4360, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3050, 4350, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3100, 430, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3150, 4335, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3200, 4290, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3250, 4275, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3300, 4250, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3350, 4220, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3400, 4195, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3450, 4190, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3500, 4160, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3550, 4180, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3600, 4180, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3650, 4180, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);

			ObjectManager::Get_Instance()->AddObject(OBJECT_TAG::OBJ_ENVIROMENT, AbstractFactory<Enviroment>::Create());
			ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back()->Set_Info(3700, 4200, 50, 100);
			dynamic_cast<Enviroment*>(ObjectManager::Get_Instance()->Get_ObjectList(OBJECT_TAG::OBJ_ENVIROMENT)->back())->Set_EnvTag(ENV_TYPE::ENV_OBSTACLE);
		}
		
	}
}

void MapManager::MapGenerator_Village_Back(HDC DC) {

	if (SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_VILLAGE) {

		////////////////////////////////////////// SIDE ////////////////////////////////////////////////
		FileManager::Get_Instance()->Append_Image(DC, L"Village_BlackBoard", { 2600, 4850 }, 15.f, 0.5f);			// ¹Ù´Ú

		if (Player->Get_Pos().X < 1760) {																	// ÁÂ »çÀÌµå ·»´õ
			FileManager::Get_Instance()->Append_Image(DC, L"Village_BlackBoard", { 170, 4600 }, 1.5f, 3.f);
			FileManager::Get_Instance()->Append_Image(DC, L"Village_BlackBoard", { 900, 4180 }, 1, 0.25f);

			FileManager::Get_Instance()->Append_Image(DC, L"Floor04", { 900, 4162 }, 0.5f, 0.5f);
			FileManager::Get_Instance()->Append_Image(DC, L"Corner03", { 955, 4312 }, 0.7f, 0.7f);
			FileManager::Get_Instance()->Append_Image(DC, L"Wall05", { 803, 4315 }, 0.8f, 0.8f);
			FileManager::Get_Instance()->Append_Image(DC, L"Corner04", { 820, 4190 }, 0.7f, 0.7f);
			FileManager::Get_Instance()->Append_Image(DC, L"Corner05", { 1025, 4170 }, 0.7f, 0.7f);
			FileManager::Get_Instance()->Append_Image(DC, L"Wall06", { 390, 4600 });
			FileManager::Get_Instance()->Append_Image(DC, L"Wall05_Flip", { 370, 4310 }, 0.7f, 0.7f);
			FileManager::Get_Instance()->Append_Image(DC, L"Floor05", { 100, 4145 }, 0.7f, 0.7f);
			FileManager::Get_Instance()->Append_Image(DC, L"Corner04_Flip", { 347, 4190 }, 0.7f, 0.7f);

			//FileManager::Get_Instance()->Append_Image(DC, L"Bell_Corner04", { 500, 4600 }, 0.8f, 0.8f);
			//FileManager::Get_Instance()->Append_Image(DC, L"Bell_Corner03", { 570, 4660 });
		}

		if (Player->Get_Pos().Y < 4300.f && Player->Get_Pos().X < 1760.f) {									//  ÁÂ »çÀÌµå ÃµÀå ·»´õ
			FileManager::Get_Instance()->Append_Image(DC, L"Village_BlackBoard", { 500, 3600 }, 4, 1);
			FileManager::Get_Instance()->Append_Image(DC, L"Village_BlackBoard", { 800, 3300 }, 5, 1);
			FileManager::Get_Instance()->Append_Image(DC, L"Village_BlackBoard", { 1200, 3460 }, 1, 1);

			FileManager::Get_Instance()->Append_Image(DC, L"Curtain01", { 600, 3850 });
			FileManager::Get_Instance()->Append_Image(DC, L"Curtain02", { 750, 3850 });
			FileManager::Get_Instance()->Append_Image(DC, L"Curtain03", { 100, 3850 });

			FileManager::Get_Instance()->Append_Image(DC, L"Ceiling_Corner02", { 1180, 3700 }, 1.7f, 1.7f);
			FileManager::Get_Instance()->Append_Image(DC, L"Ceiling_Corner02", { 1550, 3600 }, 1.7f, 1.7f);
			FileManager::Get_Instance()->Append_Image(DC, L"Ceiling02", { 100, 3750 });
			FileManager::Get_Instance()->Append_Image(DC, L"Ceiling02", { 290, 3750 });
			FileManager::Get_Instance()->Append_Image(DC, L"Ceiling02", { 480, 3750 });
			FileManager::Get_Instance()->Append_Image(DC, L"Ceiling02", { 670, 3750 });
			FileManager::Get_Instance()->Append_Image(DC, L"Ceiling02", { 860, 3750 });
		}

		if (Player->Get_Pos().X > 2860.f)					// ¿ì »çÀÌµå ·»´õ
			FileManager::Get_Instance()->Append_Image(DC, L"RSide", { 3800, 4100 }, 0.7f, 0.7f);

		//	////////////////////////////////////////// FLOOR ////////////////////////////////////////////////

		for (float i = 800; i < 4000.f; i += 800.f) {
			FileManager::Get_Instance()->Append_Image(DC, L"Back_Bar01", { i, 4630 });
			if (i > 800)
				FileManager::Get_Instance()->Append_Image(DC, L"Back_Bar02", { i - 400.f, 4550 });
		}

		FileManager::Get_Instance()->Append_Image(DC, L"Floor06", { 470, 4775 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor06", { 600, 4775 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor07", { 775, 4770 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor08", { 930, 4770 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor06", { 1100, 4775 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor07", { 1245, 4770 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor06", { 1400, 4775 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor09", { 1555, 4773 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor06", { 1710, 4775 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor07", { 1865, 4770 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor09", { 2020, 4773 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor07", { 2175, 4770 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor06", { 2330, 4775 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor09", { 2485, 4773 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor07", { 2645, 4770 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor09", { 2800, 4773 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor07", { 2955, 4770 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor06", { 3110, 4775 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor09", { 3265, 4773 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor06", { 3420, 4775 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor06", { 3575, 4775 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor07", { 3730, 4770 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor08", { 3885, 4770 });
		FileManager::Get_Instance()->Append_Image(DC, L"Floor06", { 4040, 4775 });
		//FileManager::Get_Instance()->Append_Image(DC, L"Floor07", { 4195, 4770 });

		////////////////////////////////////////// DECOR ////////////////////////////////////////////////

		FileManager::Get_Instance()->Append_Image(DC, L"Sign01", { 1500, 4663 });
		//FileManager::Get_Instance()->Append_Image(DC, L"Sign02", { 2570, 4660 });
		FileManager::Get_Instance()->Append_Image(DC, L"Sign03", { 3570, 4630 }, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"Bell_Chain", { 1950, 3950 }, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"Bell_Chain", { 2500, 3300 }, 0.8f, 0.8f);
		FileManager::Get_Instance()->Append_Image(DC, L"Bell_Chain", { 3040, 3800 }, 0.65f, 0.65f);
		FileManager::Get_Instance()->Append_Image(DC, L"Bell_Chain", { 1600, 3200 }, 0.8f, 0.8f);

		FileManager::Get_Instance()->Append_Image(DC, L"Chair", { 3250, 4710 });
		FileManager::Get_Instance()->Append_Image(DC, L"Deco02", { 2588, 4780 }, 0.8f, 0.8f);


		////////////////////////////////////////// FLOAT ////////////////////////////////////////////////
		if (Player->Get_Pos().X < 2325.f) {			// °øÁß 1ÁöÇü ·»´õ
			FileManager::Get_Instance()->Append_Image(DC, L"Star02", { 1400, 4400 }, 0.8f, 0.8f);
			FileManager::Get_Instance()->Append_Image(DC, L"Floor_Wide01", { 1400, 4480 }, 0.4f, 0.4f);
			FileManager::Get_Instance()->Append_Image(DC, L"Chain", { 1400, 3780 });
		}
		if (Player->Get_Pos().X < 3270.f) {			// °øÁß 2ÁöÇü ·»´õ
			FileManager::Get_Instance()->Append_Image(DC, L"Star02", { 2300, 4200 }, 0.8f, 0.8f);
			FileManager::Get_Instance()->Append_Image(DC, L"Floor_Wide01", { 2300, 4280 }, 0.4f, 0.4f);
			FileManager::Get_Instance()->Append_Image(DC, L"Chain", { 2300, 3580 });
		}
		if (Player->Get_Pos().X > 2275.f) {			// °øÁß 3, 4ÁöÇü ·»´õ
			FileManager::Get_Instance()->Append_Image(DC, L"Star01", { 3040, 4000 }, 0.6f, 0.6f);
			FileManager::Get_Instance()->Append_Image(DC, L"Floor_Wide02", { 3040, 4080 }, 0.4f, 0.4f);

			FileManager::Get_Instance()->Append_Image(DC, L"Star02", { 3300, 4300 }, 0.8f, 0.8f);
			FileManager::Get_Instance()->Append_Image(DC, L"Floor_Wide02", { 3300, 4380 }, 0.4f, 0.4f);
			FileManager::Get_Instance()->Append_Image(DC, L"Chain", { 3300, 3680 });
		}
	}
}
void MapManager::MapGenerator_Village_Front(HDC DC) {
	if (SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_VILLAGE) {
		FileManager::Get_Instance()->Append_Image(DC, L"Fore_Bar01", { 1000, 4600 }, 1.75f, 1.75f);
		FileManager::Get_Instance()->Append_Image(DC, L"Fore_Bar02", { 1400, 4600 }, 1.75f, 1.75f);
		FileManager::Get_Instance()->Append_Image(DC, L"Fore_Bar01", { 2500, 4600 }, 1.75f, 1.75f);
		FileManager::Get_Instance()->Append_Image(DC, L"Fore_Bar02", { 2900, 4600 }, 1.75f, 1.75f);
		FileManager::Get_Instance()->Append_Image(DC, L"Fore_Bar01", { 3600, 4600 }, 1.75f, 1.75f);
	}
}

void MapManager::MapGenerator_Dungeon_Back(HDC DC)	{
	if (SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_DUNGEON) {
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Ceiling_Corner02", { 2590, 4420 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Bell_Corner", { 2600, 4700 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"SideWall99", { 2820, 4670 }, 0.75f, 0.75f);
		FileManager::Get_Instance()->Append_Image(DC, L"BlackBoard", { 3480, 4800 }, 4.f, 2.f);
		FileManager::Get_Instance()->Append_Image(DC, L"BlackBoard", { 1600, 4900 }, 10.f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"BlackBoard", { 3500, 3460 }, 5.f, 1.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"BlackBoard", { 200, 1900 }, 1.5f, 6.f);
		FileManager::Get_Instance()->Append_Image(DC, L"BlackBoard", { 3560, 1760 }, 5.f, 8.f);
		FileManager::Get_Instance()->Append_Image(DC, L"BlackBoard", { 3750, 2950}, 3.f, 2.f);	
		FileManager::Get_Instance()->Append_Image(DC, L"BlackBoard", { 100, 3980 }, 2.f, 1.f);

		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Float_Floor01", { 1900, 4550 }, 0.5f, 0.5f);

		FileManager::Get_Instance()->Append_Image(DC, L"Floor_Long", { 2000, 4820 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Floor_Long", { 1200, 4820 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Floor_Long", { 400, 4820 }, 0.7f, 0.7f);

		FileManager::Get_Instance()->Append_Image(DC, L"BlackBoard", { -100, 4000 }, 3.5f, 6.f);

		FileManager::Get_Instance()->Append_Image(DC, L"Corner_Arch01", { 3900 , 4285  }, 0.7f, 0.7f);

		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Ceiling01", { 3900, 3735 }); 

		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Wall01", { 340, 3430 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Wall01", { 340, 3840 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Wall01", { 340, 4250 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Wall01", { 340, 4660 }, 0.7f, 0.7f);

		FileManager::Get_Instance()->Append_Image(DC, L"Spear_Field01_Flip", { 3160, 4320 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Spear_Field01", { 3880, 4300 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Spear_Ceiling01", { 3160, 3820 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Spear_Ceiling01", { 3880, 3640 }, 0.7f, 0.7f);

		FileManager::Get_Instance()->Append_Image(DC, L"SpongeWall_Flip", { 2790, 3690 });
		FileManager::Get_Instance()->Append_Image(DC, L"SpongeWall_Flip", { 2790, 3390 });
		//FileManager::Get_Instance()->Append_Image(DC, L"SpongeWall_Flip", { 2790, 3090 });
		//FileManager::Get_Instance()->Append_Image(DC, L"SpongeWall_Flip", { 2790, 2790 });

		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Floor_Wide02", { 1325, 4280 }, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Chain", { 1325, 4100 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Chain", { 1325, 3525 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Star02", { 1325, 4200 }, 0.7f, 0.7f);

		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Floor_Wide01", { 1750, 3685 }, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Chain", { 1750, 3200 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Chain", { 1750, 2625 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Star01", { 1750, 3600 }, 0.7f, 0.7f);

		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Floor_Wide02", { 900, 3930 }, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Chain", { 900, 3550 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Star01", { 900, 3850 }, 0.5f, 0.5f);

		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Floor_Wide01", { 1125, 3130 }, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Chain", { 1125, 2750 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Chain", { 1125, 2175 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Star01", { 1125, 3050 }, 0.7f, 0.7f);

		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Floor_Wide02", { 2075, 3300 }, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Chain", { 2075, 2920 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Chain", { 2075, 2345 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Star02", { 2075, 3220 }, 0.5f, 0.5f);

		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Wall01", { 385, 1330 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Wall01", { 385, 1740 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Wall01", { 385, 2150 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Wall01", { 385, 2560 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Room01", { 250, 3000 }, 0.5f, 0.5f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Sign", { 400, 2930 });

		FileManager::Get_Instance()->Append_Image(DC, L"Wall01_Flip", {	2900, 1430 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Wall01_Flip", {	2900, 1840 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Wall01_Flip", {	2900, 2250 }, 0.7f, 0.7f);
		FileManager::Get_Instance()->Append_Image(DC, L"Wall01_Flip", { 2900, 2660 }, 0.7f, 0.7f);

		FileManager::Get_Instance()->Append_Image(DC, L"Gate", { 2960 , 3060 }, 0.6f, 0.6f);
		FileManager::Get_Instance()->Append_Image(DC, L"Dungeon_Chair", { 3120 , 3100 }, 0.5f, 0.5f);

		FileManager::Get_Instance()->Append_Image(DC, L"Room02", { 3000 , 3140 }, 0.5f, 0.5f);
	}
}
void MapManager::MapGenerator_Dungeon_Front(HDC DC)
{
	if (SceneManager::Get_Instance()->Get_CurrentScene() == STAGE_TYPE::STAGE_DUNGEON) {

	}
}

void MapManager::UI_Initialize() {
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/UI/Lose_HP_Anim.bmp", L"LoseHP");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/UI/HP01.bmp", L"HP");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/UI/HP_BackBar.bmp", L"HP_BackBar");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/UI/Thread.bmp", L"Thread");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/UI/Silk.bmp", L"Silk");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/UI/MukJu.bmp", L"MukJu");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/UI/Stone.bmp", L"Stone");
}

void MapManager::Player_Initialize() {
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Idle/Idle_L_Anim.bmp", L"Idle_L");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Idle/Idle_R_Anim.bmp", L"Idle_R");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Run/Running_L_Anim.bmp", L"Run_L");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Run/Running_R_Anim.bmp", L"Run_R");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Run/Dash_L_Anim.bmp", L"DashL");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Run/Dash_R_Anim.bmp", L"DashR");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Attack/Attack_L_Anim.bmp", L"Attack_L");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Attack/Attack_R_Anim.bmp", L"Attack_R");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Slash/Slash_L_Anim.bmp", L"SlashL");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Slash/Slash_R_Anim.bmp", L"SlashR");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Turn/LeftToRight.bmp", L"LTR");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Turn/RightToLeft.bmp", L"RTL");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Jump/Jump_L_Anim.bmp", L"JumpL");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Jump/Jump_R_Anim.bmp", L"JumpR");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Fly/Double_Jump_L_Anim.bmp", L"DBJumpL");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Fly/Double_Jump_R_Anim.bmp", L"DBJumpR");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Jump/Fall_L_Anim.bmp", L"FallL");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Jump/Fall_R_Anim.bmp", L"FallR");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Jump/Flow_L_Anim.bmp", L"FlowL");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Jump/Flow_R_Anim.bmp", L"FlowR");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Jump/ParaBoom_R_Anim.bmp", L"ParaR");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Jump/ParaBoom_L_Anim.bmp", L"ParaL");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Damaged.bmp", L"Damaged");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Hornet/Death_Anim.bmp", L"Death");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Skill/Silk_Thread_L_Anim.bmp", L"Silk_Thread_L");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Skill/Silk_Thread_R_Anim.bmp", L"Silk_Thread_R");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Skill/Heal_L_Anim.bmp", L"Heal_L");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Skill/Heal_R_Anim.bmp", L"Heal_R");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Skill/Drill_L_Anim.bmp", L"Drill_L");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Skill/Drill_R_Anim.bmp", L"Drill_R");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Skill/Skill_Drill01.bmp", L"Drill_Image");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Skill/Drill_L_Effect_Anim.bmp", L"Drill_Effect_L");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Skill/Drill_R_Effect_Anim.bmp", L"Drill_Effect_R");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Skill/Throw_L_Anim.bmp", L"Throw_L");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Skill/Throw_R_Anim.bmp", L"Throw_R");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Skill/OnHit_Effect_Anim.bmp", L"OnHit_Effect");

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Effects/Dash_L_Effect.bmp", L"Dash_Effect_L");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Effects/Dash_R_Effect.bmp", L"Dash_Effect_R");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Effects/Slash/Slash_Effect_B_Anim.bmp", L"Slash_Effect_R");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Effects/Damage_Effect_Anim.bmp", L"Damage_Effect");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Effects/DBJump_Effect.bmp", L"DBJump_Effect");
}
