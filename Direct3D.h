#pragma once
#include <d3d11.h>

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//�萔�錾
//const char* WIN_CLASS_NAME = "SanpleGame";
//extern const char* WIN_CLASS_NAME;



namespace Direct3D

{
	//������
	void Initialize(int winW, int winH, HWND hWnd);
	
	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();

};