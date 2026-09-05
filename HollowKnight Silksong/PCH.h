#ifndef PCH_H
#define PCH_H

#include <vector>
#include <list>
#include <string>
#include <map>
#include <algorithm>
#include <ctime>
////////////////////////////////////////// STL
#include <Windows.h>

using namespace std;
#include <filesystem>
#include <Gdiplus.h>
#pragma comment(lib, "gdiplus")
#pragma comment(lib, "Msimg32.lib")
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")


#include "fmod.h"
#include "fmod.hpp"

#pragma comment(lib, "fmodex_vc.lib")
#include <io.h>
////////////////////////////////////////// WINAPI - GDI+
using namespace Gdiplus;
////////////////////////////////////////// NAMESPACE
#include "framework.h"
#include "ENUM.h"
#include "STRUCT.h"
#include "TEMPLATE.h"
#include "DEFINE.h"
using namespace SAFE_DELETE_NAMESPACE;
//////////////////////////////////////// Pre - Header
#include "AbstractFactory.h"
#include "GameObject.h"
#include "Enviroment.h"
#include "Tile.h"
#include "NPC.h"
#include "BitMap.h"
#include "Button.h"
#include "Inventory.h"
#include "SkillObject.h"
#include "MainUI.h"
#include "StoreUI.h"
#include "HitBox.h"
#include "Portal.h"
#include "Monster.h"
#include "Boss.h"
#include "Player.h"
//////////////////////////////////////// Game - Object
#include "Scene.h"
#include "Scene_Load.h"
#include "Scene_Start.h"
#include "Scene_Select.h"
#include "Scene_Exit.h"
#include "Scene_Village.h"
#include "Scene_Dungeon.h"
#include "Scene_Gate.h"
#include "Scene_Boss.h"
//////////////////////////////////////// Game - Scene
#include "KeyManager.h"
#include "TimeManager.h"
#include "FileManager.h"
#include "SoundManager.h"
#include "MapManager.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "TileManager.h"
//////////////////////////////////////// Game - Manager
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 



#endif
#endif
#endif
