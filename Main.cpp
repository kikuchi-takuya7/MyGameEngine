//インクルード
#include <Windows.h>
#include"Direct3D.h"
#include"dice.h"
#include"Sprite.h"

const char* WIN_CLASS_NAME = "SanpleGame";
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

Sprite* sprite;
Quad* dice;

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン　　　　　　　　　　　自由に
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン　　　　　　　　　変更
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル　　　　　　　　　　可能
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）

	RegisterClassEx(&wc);  //クラスを登録


	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ


	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //ウィンドウクラス名
		"サンプルゲーム",     //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ） スタイルを変えるとウィンドウの大きさ変更だったりをできなくできる
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,                 //ウィンドウ幅
		winH,                 //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);
	HRESULT hr;
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr)) {
		PostQuitMessage(0);
	}

	Camera::Initialize();

	Camera::SetTarget(XMFLOAT3 (0, 0, 0));
	Camera::SetPosition(XMFLOAT3(0, 3, -10));

	dice = new Quad;
	sprite = new Sprite;

	hr = dice->Initialize();
	if (FAILED(hr)) {
		PostQuitMessage(0);
	}

	hr = sprite->Initialize();
	if (FAILED(hr)) {
		PostQuitMessage(0);
	}

	XMMATRIX mat   = XMMatrixIdentity();

	XMMATRIX matR  = XMMatrixIdentity();
	
	XMMATRIX matRX = XMMatrixIdentity();

	XMMATRIX matRY = XMMatrixIdentity();

	XMMATRIX matRZ = XMMatrixIdentity();

	XMMATRIX matT  = XMMatrixIdentity();

	XMMATRIX matS  = XMMatrixIdentity();

	//matR = XMMatrixRotationZ(XMConvertToRadians(-30));
	matT = XMMatrixTranslation(0, 2.5f, -1);
	//matS = XMMatrixScaling(1.0f, 2.0f, 1.0f);
	//matRX = XMMatrixRotationX(XMConvertToRadians(45));

	//mat = matS * matR * matT;
	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else
		{
			
			//ゲームの処理
			Camera::Update();

			Direct3D::BeginDraw();

			XMMATRIX matSs = XMMatrixScaling(512.0f / 800.0f, 400.0f / 600.0f, 1);
			XMMATRIX matTs = XMMatrixTranslation(0, -0.25f, 0);
			XMMATRIX spritemat =matSs * matTs;
			sprite->Draw(spritemat);

			static float i = 0;
			i += 0.03f;

			matRY = XMMatrixRotationY(XMConvertToRadians(i));
			matRZ = XMMatrixRotationY(XMConvertToRadians(i));

			matR = matRX * matRY * matRZ;

			mat = matT * matR * matS;
			dice->Draw(mat);

			

			Direct3D::EndDraw();

			

		}
	}

	//SAFE_RELEASE(dice);
	SAFE_DELETE(dice);
	SAFE_DELETE(sprite);


	Direct3D::Release();
	
	return 0;
}


//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)//メッセージ
	{
	case WM_CLOSE:
		PostQuitMessage(0);  //プログラム終了
		return 0;

	case WM_DESTROY://ウィンドウが閉じられたら
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

