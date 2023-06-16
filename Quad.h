#pragma once
#include "Direct3D.h"
#include "Camera.h"
#include <DirectXMath.h>
#include "Texture.h"
#include <array>

using namespace DirectX;
using std::array;

const UINT64 INDEXNUM = 36;

//�R���X�^���g�o�b�t�@�[

struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMMATRIX	matW;
};

//���_���
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal;
};

class Quad
{
protected:
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
	virtual void MakeVerBf();
	//VERTEX SetVartices();
	void MakeIndBf();
	void MakeConBf();
	void SetTexture();
	void SetMap(XMMATRIX& worldMatrix);
	void SetPipeline();
};