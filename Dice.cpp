#include "Dice.h"

Dice::Dice()
{
	index_ = { 0,2,3, 0,1,2, 1,5,6, 1,6,2, 9,11,10, 9,8,11, 8,13,11, 8,12,13, 16,15,14, 16,17,15, 19,20,21, 19,18,20 };//���v���̏��Ԃɏ����Ă�����ɂ����`�悳���邩�猩�������������猩�Ď��v���ɂ���΂���
	//         ��O�@�@�@�@�@�E�ʁ@�@�@�@�@���ʁ@�@�@�@�@   ���ʁ@�@�@      �@��ʁ@�@�@�@�@       ����
}

Dice::~Dice()
{
}

void Dice::MakeVerBf()
{

	

	// ���_���
	VERTEX vertices[] =
	{
		//�Q�l�@https://gihyo.jp/dev/serial/01/as3/0049
		// https://shibuya24.info/entry/unity-mesh-dynamic-apply-texture
		//ping�̉摜���Ȃ���������킩��₷��
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) , XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	// �l�p�`�̒��_�i����j
		{XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f),   XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	// �l�p�`�̒��_�i�E��j
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	// �l�p�`�̒��_�i�E���j
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	// �l�p�`�̒��_�i�����j		
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),  XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//4  �g���ĂȂ�
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),   XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,1.0f, 0.0f) },	//5
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),  XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,1.0f, 0.0f) },	//6
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//7  �g���ĂȂ�
		//���ʗp
		//�Q�ƂU�̋��E�ƂU�ƂT�̋��E
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),  XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,1.0f, 0.0f) },	//8  4
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),   XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,1.0f, 0.0f) },	//9  5
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),  XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,1.0f, 0.0f) },	//10 6
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,1.0f, 0.0f) },	//11 7
		//�P�ƂT�̋��E
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//12 0
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//13 3
		//��ʗp
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//14 0
		{XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f),   XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//15 1
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),  XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,1.0f, 0.0f) },	//16 4
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),   XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,1.0f, 0.0f) },	//17 5
		//���ʗp
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//18 2
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//19 3
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),  XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,1.0f, 0.0f) },	//20 6
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,1.0f, 0.0f) },	//21 7
	};

	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr_ = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
}
