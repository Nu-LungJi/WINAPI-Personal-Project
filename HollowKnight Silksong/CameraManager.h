#pragma once
class CameraManager {
	COMPONENT_SINGLETON(CameraManager)
public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC DC);
	void Release();

private:
	Vector2D			CameraCenterPos;		// 카메라가 보고있는 중심 좌표
	Vector2D			CurrCameraPos;			// 이전위치와 현재위치 보정 위치
	Vector2D			PrevCameraPos;			// 카메라가 보는 이전프레임 위치
	GameObject*			CameraTarget;			// 카메라 타겟 오브젝트
	Vector2D			CameraOffset;			// 해상도 중심위치와, 카메라 LookAt 간의 차이값
			
	FLOAT		ChaseTime;						// 타겟을 따라가는데 걸리는 시간
	FLOAT		CameraSpeed;						// 타겟을 따라가는 속도
	FLOAT		TimeAccumaltion;						// 누적 시간

	FLOAT		dwTime;
	FLOAT		CameraShakeTime;
	INT			CameraShakeStrength;

	GameObject* PlayerMainUI;
	Vector2D	TempOffset;

	HDC MemDC;

public:
	void Set_TempOffset(Vector2D _vec) { TempOffset = _vec; }

	void Set_CameraCenterPos(Vector2D _vLook)
	{
		CameraCenterPos = _vLook;
		FLOAT fMoveDist = sqrtf((CameraCenterPos.X - PrevCameraPos.X) * (CameraCenterPos.X - PrevCameraPos.X) +
			(CameraCenterPos.X - PrevCameraPos.X) * (CameraCenterPos.X - PrevCameraPos.X));
		CameraSpeed = fMoveDist / ChaseTime;
		TimeAccumaltion = 0.f;
	}
	void SetTarget(GameObject* _CameraTarget)		{ CameraTarget = _CameraTarget; }

	Vector2D GetLookAt() const						{ return CurrCameraPos; }
	Vector2D GetRenderPos(Vector2D _vObjPos)		{ return _vObjPos - CameraOffset; }
	Vector2D GetRealPos(Vector2D _vRenderPos)		{ return _vRenderPos + CameraOffset; }

	RECT GetRenderRect(INFO _INFO)
	{
		Vector2D RenderPos = GetRenderPos(Vector2D(_INFO.CenterPosX, _INFO.CenterPosY));
		RECT rRect;
		rRect.left =	RenderPos.X - _INFO.Width / 2;
		rRect.top =		RenderPos.Y - _INFO.Height / 2;
		rRect.right =	RenderPos.X + _INFO.Width / 2;
		rRect.bottom =	RenderPos.Y + _INFO.Height / 2;
		return rRect;
	}

	INFO GetRenderInfo(INFO _INFO)
	{
		INFO renderInfo = { _INFO.CenterPosX - CameraOffset.X, _INFO.CenterPosY - CameraOffset.Y, _INFO.Width, _INFO.Height};
		return renderInfo;
	}

	Vector2D GetOffset() const { return CameraOffset; }
	BOOL	Set_ShakePosition();
	void	CameraShake(FLOAT _Time, UINT _Str) {
		dwTime = GetTickCount(); 
		CameraShakeTime = _Time;
		CameraShakeStrength = _Str;
	}

	void Camera_FadeIn(HDC DC);
	void Camera_FadeOut(HDC DC);
private:
	void CalDiff();
};

