#include "PCH.h"
#include "SceneManager.h"
SceneManager* SceneManager::Instance = nullptr;
SceneManager::SceneManager()	{
	ZeroMemory(&SceneList, sizeof(SceneList));
}
SceneManager::~SceneManager()	{ Release(); }

void	SceneManager::Initialize(){	   
	FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Loading/Loading_Anim.bmp", L"Loading");

	PreviousScene	= STAGE_TYPE::STAGE_START;
	CurrentScene	= STAGE_TYPE::STAGE_START;
	
	SceneList[(LONG)STAGE_TYPE::STAGE_START] = new Scene_Start;
	SceneList[(LONG)STAGE_TYPE::STAGE_START]->Initialize();
}
void	SceneManager::Update(){
		SceneList[(LONG)CurrentScene]->Update();
}
void	SceneManager::Late_Update(){	
		SceneList[(LONG)CurrentScene]->Late_Update();
}
void	SceneManager::Render(HDC DC){  
		SceneList[(LONG)CurrentScene]->Render(DC);
}
void	SceneManager::Release(){
	for (auto& SceneActor : SceneList) {
		if (SceneActor) {
			delete SceneActor;
			SceneActor = nullptr;
		}
	}
}
void SceneManager::Scene_Transition(STAGE_TYPE _SceneType) {
	CurrentScene = _SceneType;

	if (PreviousScene != CurrentScene) {

		SAFE_DELETE(SceneList[(LONG)PreviousScene]);

		FileManager::Get_Instance()->FrameStartPoint_Reset();

		if (CurrentScene == STAGE_TYPE::STAGE_START) {
			SceneList[(LONG)STAGE_TYPE::STAGE_START] = new Scene_Start;
		}
		else if (CurrentScene == STAGE_TYPE::STAGE_SELECT) {
			SceneList[(LONG)STAGE_TYPE::STAGE_SELECT] = new Scene_Select;
		}
		else if (CurrentScene == STAGE_TYPE::STAGE_QUIT) {
			SceneList[(LONG)STAGE_TYPE::STAGE_QUIT] = new Scene_Exit;
		}

		else if (CurrentScene == STAGE_TYPE::STAGE_VILLAGE) {
			SceneList[(LONG)STAGE_TYPE::STAGE_VILLAGE] = new Scene_Village;
		}
		else if (CurrentScene == STAGE_TYPE::STAGE_DUNGEON) {
			SceneList[(LONG)STAGE_TYPE::STAGE_DUNGEON] = new Scene_Dungeon;
		}
		else if (CurrentScene == STAGE_TYPE::STAGE_GATE) {
			SceneList[(LONG)STAGE_TYPE::STAGE_GATE] = new Scene_Gate;
		}
		else if (CurrentScene == STAGE_TYPE::STAGE_BOSS) {
			SceneList[(LONG)STAGE_TYPE::STAGE_BOSS] = new Scene_Boss;
		}
		else if (CurrentScene == STAGE_TYPE::STAGE_LOAD) {
			SceneList[(LONG)STAGE_TYPE::STAGE_LOAD] = new Scene_Load;
		}
		//FileManager::Get_Instance()->FileMap_Reset();
		//FileManager::Get_Instance()->Insert_BMPFile(L"../Resource/Loading/Loading_Anim.bmp", L"Loading");

		SceneList[(LONG)CurrentScene]->Initialize();
		MapManager::Get_Instance()->Initialize();
		PreviousScene = CurrentScene;
	}
}
