#include "Input.h"
#include <string>

namespace Input
{

	LPDIRECTINPUT8   pDInput_ = nullptr; //�����Ń|�C���^�ɂȂ��Ă邩��nullptr
	LPDIRECTINPUTDEVICE8 pKeyDevice_ = nullptr; //�L�[�{�[�h�ɃA�N�Z�X���邽�߂̂��
	BYTE keyState_[256] = { 0 }; //unsgind char�������̂��߂�ǂ�����������BYTE�L�[�̐��͈�ʓI��109�Ȃ̂ŏ\��
	BYTE prevkeyState_[256];    //�O�t���[���ł̊e�L�[�̏��

	//�}�E�X
	LPDIRECTINPUTDEVICE8	pMouseDevice_;	//�f�o�C�X�I�u�W�F�N�g
	DIMOUSESTATE mouseState_;				//�}�E�X�̏��
	DIMOUSESTATE prevMouseState_;			//�O�t���[���̃}�E�X�̏��
	XMVECTOR mousePosition;

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput_, nullptr);
		pDInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice_, nullptr); //�N���G�C�g
		pKeyDevice_->SetDataFormat(&c_dfDIKeyboard); //������n���f�o�C�X�̎�ނ��w��
		pKeyDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND); //���̎��s���̃A�v���ɑ΂���D��x�B�E�B���h�E���d�Ȃ��ĂĂ��������邩�ǂ����݂�����
	
		//�}�E�X
		pDInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	void Update()
	{
		//�܂Ƃ܂����f�[�^���ۂ��ƃR�s�[�ł���֐��B���Ǝg������
		memcpy(prevkeyState_, keyState_, sizeof(BYTE)*256);

		pKeyDevice_->Acquire();
		pKeyDevice_->GetDeviceState(sizeof(keyState_), &keyState_); //���̏u�Ԃ̃L�[�{�[�h�̏�Ԃ���肷��

		//�}�E�X
		pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);
	}

	bool IsKey(int keyCode)
	{
		if (keyState_[keyCode] & 0x80) //��i����128�B�L�[�{�[�h�̐���葽���]�T��������7bit
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		if (prevkeyState_[keyCode] ^ keyState_[keyCode] && keyState_[keyCode] & 0x80)//(Iskey(keyCode) && !(prevkeyState_[keyCode] & 0x80))���Ă̂�����
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
		//�����Ă�
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}
	bool IsMouseButtonDown(int buttonCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsMouseButton(buttonCode) && !(prevMouseState_.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}
	bool IsMouseButtonUp(int buttonCode)
	{
		//�������ĂȂ��āA�O��͉����Ă�
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