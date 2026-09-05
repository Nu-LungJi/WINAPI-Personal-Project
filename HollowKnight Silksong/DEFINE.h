#pragma once
/////////////////////////////// GLOBAL VARIABLE
extern HWND			hWnd;
extern INT			FrameIntervalTimeA;
extern INT			FrameIntervalTimeB;
/////////////////////////////// MACRO DEFINE
#define DEFAULT_WINDOW_CX	1280
#define DEFAULT_WINDOW_CY	720

#define PI 3.141592f

#define KEY_COMMAND(Key, State)     KeyManager::Get_Instance()->GetKeyState(Key) == State

#define OBJ_ALIVE	0
#define OBJ_DEAD	1

#define		TILECX 64		// 타일 한장의 크기 (작을 수록 겹쳐그리기 가능)
#define		TILECY 64		

#define		TILEX 300
#define		TILEY 300

#define		MAX_BOSS_HP	1000

#define COMPONENT_SINGLETON(MANAGER)		\
private:									\
	MANAGER();								\
	MANAGER& operator=(MANAGER&) = delete;	\
	MANAGER(const MANAGER& rhs) = delete;	\
	~MANAGER();								\
private:									\
	static MANAGER* Instance;				\
											\
public:										\
	static MANAGER* Get_Instance() {		\
		if (nullptr == Instance)			\
			Instance = new MANAGER;			\
		return Instance;					\
	}										\
	static void Destroy_Instance() {		\
		if (nullptr != Instance) {			\
			delete Instance;				\
			Instance = nullptr;				\
		}									\
	}
#define COMPONENT_FSM(STATE)								\
class StateMachine {										\
private:													\
	STATE	CurrentState;									\
public:														\
	void FSM_StateChange(STATE _State)						\
	{														\
		CurrentState = _State;								\
	}														\
	void FSM_StateEnter();									\
	void FSM_StateUpdate();									\
	void FSM_StateExit();									\
															\
	STATE	FSM_GetCurrentState()	{return CurrentState;}	\
};