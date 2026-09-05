#pragma once

class KeyManager {
	COMPONENT_SINGLETON(KeyManager)

public:
	void	Initialize()		  ;
	void	Update()			  ;
	void	Late_Update()		  ;
	void	Render(HDC DC)		{};
	void	Release()			{};

public:
	BOOL	KEY_HOLD(INT _KEY) { return GetAsyncKeyState(_KEY) & 0x8000; }
	BOOL	KEY_DOWN(INT _KEY);
	BOOL	KEY_UP	(INT _KEY);

	KEY_STATE GetKeyState(KEY key) { return KeySet[(int)key].Current_KeyState; };

private:
	bool		KEY_STATE[VK_OEM_CLEAR];
	vector<KeyINFO>				 KeySet;
};

