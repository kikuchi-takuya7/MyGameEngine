#pragma once
#include "Direct3D.h"
#include "Camera.h"
#include <DirectXMath.h>
#include "Texture.h"
#include <array>

using namespace DirectX;
using std::vector;

const UINT64 INDEXNUM = 36;

//コンスタントバッファー

struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMMATRIX	matW;
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal;
};

class Quad
{
protected:
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;
	HRESULT hr_;
	int indexNum_;//インデックス数
	vector<int> index_;
	int vertexNum_;
	vector<VERTEX> vertices_;

public:
	Quad();
	~Quad();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
	void MakeVerBf();
	virtual void SetVartices();
	virtual void SetIndex();
	void MakeIndBf();
	void MakeConBf();
	void SetTexture();
	void SetMap(XMMATRIX& worldMatrix);
	void SetPipeline();
};