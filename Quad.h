#pragma once
#include "Direct3D.h"
#include "Camera.h"
#include <DirectXMath.h>
#include "Texture.h"
#include <array>

using namespace DirectX;
using std::array;

const int INDEXNUM = 6;

//コンスタントバッファー

struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

class Quad
{
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;
	HRESULT hr_;
	array<int,INDEXNUM> index_;

public:
	Quad();
	~Quad();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
	void MakeVerBf();
	void MakeIndBf();
	void MakeConBf();
	void SetTexture();
	void SetMap(XMMATRIX& worldMatrix);
	void SetPipeline();
};