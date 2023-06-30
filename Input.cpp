#include "Input.h"

namespace Input
{

	LPDIRECTINPUT8   pDInput = nullptr; //�����Ń|�C���^�ɂȂ��Ă邩��nullptr
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr; //�L�[�{�[�h�ɃA�N�Z�X���邽�߂̂��
	BYTE keyState[256] = { 0 }; //unsgind char�������̂��߂�ǂ�����������BYTE�L�[�̐��͈�ʓI��109�Ȃ̂ŏ\��

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr); //�N���G�C�g
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard); //������n���f�o�C�X�̎�ނ��w��
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND); //���̎��s���̃A�v���ɑ΂���D��x�B�E�B���h�E���d�Ȃ��ĂĂ��������邩�ǂ����݂�����
	}

	void Update()
	{
		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState); //���̏u�Ԃ̃L�[�{�[�h�̏�Ԃ���肷��
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