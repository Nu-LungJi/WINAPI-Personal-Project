#include "PCH.h"
#include "Flower.h"

void Flower::Initialize() {
	OBJINFO = { 0.f, 0.f, 10.f, 10.f };

	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Effect/Flower01.bmp", L"Flower01");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Effect/Flower02.bmp", L"Flower02");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Effect/Flower03.bmp", L"Flower03");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Effect/Flower04.bmp", L"Flower04");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Effect/Flower05.bmp", L"Flower05");
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/BossRes/Effect/Flower06.bmp", L"Flower06");

	index = rand() % 5 + 1;
}

int Flower::Update()
{
	Update_RECT();
    return 0;
}

void Flower::Late_Update()
{
}

void Flower::Render(HDC DC) {
	if (index == 1) {
		FileManager::Get_Instance()->Append_Image(DC, L"Flower01", { OBJINFO.CenterPosX , OBJINFO.CenterPosY }, 0.5f, 0.5f);
	}
	if (index == 2) {
		FileManager::Get_Instance()->Append_Image(DC, L"Flower02", { OBJINFO.CenterPosX , OBJINFO.CenterPosY }, 0.5f, 0.5f);
	}
	if (index == 3) {
		FileManager::Get_Instance()->Append_Image(DC, L"Flower03", { OBJINFO.CenterPosX , OBJINFO.CenterPosY }, 0.5f, 0.5f);
	}
	if (index == 4) {
		FileManager::Get_Instance()->Append_Image(DC, L"Flower04", { OBJINFO.CenterPosX , OBJINFO.CenterPosY }, 0.5f, 0.5f);
	}
	if (index == 5) {
		FileManager::Get_Instance()->Append_Image(DC, L"Flower05", { OBJINFO.CenterPosX , OBJINFO.CenterPosY }, 0.5f, 0.5f);
	}
	if (index == 6) {
		FileManager::Get_Instance()->Append_Image(DC, L"Flower06", { OBJINFO.CenterPosX , OBJINFO.CenterPosY }, 0.5f, 0.5f);
	}
}

void Flower::Collision_Update(GameObject* pObj, COLLISION_TYPE _TYPE, FLOAT _Value)
{
}

void Flower::Release()
{
}
