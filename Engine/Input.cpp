#include "Input.h"
#include <string>

namespace Input
{

	LPDIRECTINPUT8   pDInput_ = nullptr; //内部でポインタになってるからnullptr
	LPDIRECTINPUTDEVICE8 pKeyDevice_ = nullptr; //キーボードにアクセスするためのやつ
	BYTE keyState_[256] = { 0 }; //unsgind charを書くのがめんどくさかったらBYTEキーの数は一般的に109なので十分
	BYTE prevkeyState_[256];    //前フレームでの各キーの状態

	//マウス
	LPDIRECTINPUTDEVICE8	pMouseDevice_;	//デバイスオブジェクト
	DIMOUSESTATE mouseState_;				//マウスの状態
	DIMOUSESTATE prevMouseState_;			//前フレームのマウスの状態
	XMVECTOR mousePosition;

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput_, nullptr);
		pDInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice_, nullptr); //クリエイト
		pKeyDevice_->SetDataFormat(&c_dfDIKeyboard); //ここでn￥デバイスの種類を指定
		pKeyDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND); //他の実行中のアプリに対する優先度。ウィンドウが重なってても反応するかどうかみたいな
	
		//マウス
		pDInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	void Update()
	{
		//まとまったデータを丸っとコピーできる関数。割と使うかも
		memcpy(prevkeyState_, keyState_, sizeof(BYTE)*256);

		pKeyDevice_->Acquire();
		pKeyDevice_->GetDeviceState(sizeof(keyState_), &keyState_); //その瞬間のキーボードの状態を入手する

		//マウス
		pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);
	}

	bool IsKey(int keyCode)
	{
		if (keyState_[keyCode] & 0x80) //二進数で128。キーボードの数より多く余裕を持った7bit
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		if (prevkeyState_[keyCode] ^ keyState_[keyCode] && keyState_[keyCode] & 0x80)//(Iskey(keyCode) && !(prevkeyState_[keyCode] & 0x80))ってのもあり
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		if (prevkeyState_[keyCode] ^ keyState_[keyCode] && prevkeyState_[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	XMVECTOR GetMousePosition()
	{
		return mousePosition;
	}


	void SetMousePosition(int x, int y)
	{
		/*mousePosition.x = x;
		mousePosition.y = y;*/
		mousePosition = XMVectorSet((float)x, (float)y, 0, 0);
		std::string resStr = std::to_string(x) + "," + std::to_string(y) + "\n";

		OutputDebugString(resStr.c_str());
	}

	void Release()
	{
		SAFE_RELEASE(pDInput_);
		SAFE_RELEASE(pKeyDevice_);
	}
	bool IsMouseButton(int buttonCode)
	{
		//押してる
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}
	bool IsMouseButtonDown(int buttonCode)
	{
		//今は押してて、前回は押してない
		if (IsMouseButton(buttonCode) && !(prevMouseState_.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}
	bool IsMouseButtonUp(int buttonCode)
	{
		//今押してなくて、前回は押してる
		if (!IsMouseButton(buttonCode) && prevMouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}
	XMFLOAT3 GetMouseMove()
	{
		XMFLOAT3 result = XMFLOAT3((float)mouseState_.lX, (float)mouseState_.lY, (float)mouseState_.lZ);
		return result;
	}
}