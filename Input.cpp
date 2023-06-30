#include "Input.h"

namespace Input
{

	LPDIRECTINPUT8   pDInput = nullptr; //内部でポインタになってるからnullptr
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr; //キーボードにアクセスするためのやつ
	BYTE keyState[256] = { 0 }; //unsgind charを書くのがめんどくさかったらBYTEキーの数は一般的に109なので十分

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr); //クリエイト
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard); //ここでn￥デバイスの種類を指定
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND); //他の実行中のアプリに対する優先度。ウィンドウが重なってても反応するかどうかみたいな
	}

	void Update()
	{
		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState); //その瞬間のキーボードの状態を入手する
	}

	bool IsKey(int keyCode)
	{
		if (keyState[DIK_ESCAPE] | 0)
		{
			return true;
		}
		return false;
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);
		SAFE_RELEASE(pKeyDevice);
	}
}