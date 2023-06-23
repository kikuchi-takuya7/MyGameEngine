//�C���N���[�h
#include <Windows.h>
#include <assert.h>
#include "Direct3D.h"
#include "dice.h"
#include "Sprite.h"
#include "Fbx.h"

const char* WIN_CLASS_NAME = "SanpleGame";
const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���

Sprite* sprite;
Quad* dice;
Fbx* fbx;

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	
	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;            //�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R���@�@�@�@�@�@�@�@�@�@�@���R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R���@�@�@�@�@�@�@�@�@�ύX
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\���@�@�@�@�@�@�@�@�@�@�\
	wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j

	RegisterClassEx(&wc);  //�N���X��o�^


	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //�E�B���h�E��
	int winH = winRect.bottom - winRect.top;     //�E�B���h�E����


	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //�E�B���h�E�N���X��
		"�T���v���Q�[��",     //�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j �X�^�C����ς���ƃE�B���h�E�̑傫���ύX����������ł��Ȃ��ł���
		CW_USEDEFAULT,       //�\���ʒu���i���܂����j
		CW_USEDEFAULT,       //�\���ʒu��i���܂����j
		winW,                 //�E�B���h�E��
		winH,                 //�E�B���h�E����
		NULL,                //�e�E�C���h�E�i�Ȃ��j
		NULL,                //���j���[�i�Ȃ��j
		hInstance,           //�C���X�^���X
		NULL                 //�p�����[�^�i�Ȃ��j
	);

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);
	HRESULT hr;
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr)) {
		PostQuitMessage(0);
	}

	Camera::Initialize();
	Camera::SetTarget(XMFLOAT3 (0, 0, 0));
	Camera::SetPosition(XMFLOAT3(0, 3, -10));

	dice = new Dice;
	sprite = new Sprite;
	fbx = new Fbx;

	hr = dice->Initialize();
	if (FAILED(hr)) {
		PostQuitMessage(0);
	}

	hr = sprite->Initialize();
	if (FAILED(hr)) {
		PostQuitMessage(0);
	}

	hr = fbx->Load("Assets\\oden.fbx");
	if (FAILED(hr)) {
		PostQuitMessage(0);
	}
	
	//Transform mat;
	//
	//Transform matR;
	//
	//Transform matRX;

	//Transform matRY;

	//Transform matRZ;

	//Transform matT;

	//Transform matS;

	////matR = XMMatrixRotationZ(XMConvertToRadians(-30));
	//matT.position_.y = 2.5f;
	////matS = XMMatrixScaling(1.0f, 2.0f, 1.0f);
	////matRX = XMMatrixRotationX(XMConvertToRadians(45));

	//mat = matS * matR * matT;
	//���b�Z�[�W���[�v�i�����N����̂�҂j
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ�
		else
		{
			
			//�Q�[���̏���
			Camera::Update();

			Direct3D::BeginDraw();

#if 0
			Transform spriteTransform;
			spriteTransform.scale_.x = 512.0f / 800.0f;
			spriteTransform.scale_.y = 256.0f / 600.0f;

			sprite->Draw(spriteTransform);

			static float angle = 0;
			angle += 0.05;
			//XMMATRIX mat = XMMatrixRotationY(XMConvertToRadians(angle)) * XMMatrixTranslation(0,3,0);

			Transform diceTransform;
			diceTransform.position_.y = 3.0f;
			diceTransform.position_.z = 3.0f;
			diceTransform.rotate_.y = angle;
			
			dice->Draw(diceTransform);

#endif
			Transform fbxTransform;
			fbxTransform.rotate_.y += 1;
			fbx->Draw(fbxTransform);
			
			Direct3D::EndDraw();

			

		}
	}

	//SAFE_RELEASE(dice);
	SAFE_DELETE(dice);
	SAFE_DELETE(sprite);
	SAFE_DELETE(fbx);


	Direct3D::Release();
	
	return 0;
}


//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)//���b�Z�[�W
	{
	case WM_CLOSE:
		PostQuitMessage(0);  //�v���O�����I��
		return 0;

	case WM_DESTROY://�E�B���h�E������ꂽ��
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

