#pragma once
#include "Direct3D.h"
#include "Camera.h"
#include <DirectXMath.h>
#include "Texture.h"
#include <array>

using namespace DirectX;
using std::array;

const int INDEXNUM = 6;

//�R���X�^���g�o�b�t�@�[

struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};

//���_���
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

class Quad
{
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
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