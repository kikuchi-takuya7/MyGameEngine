#include "Dice.h"

Dice::Dice()
{
	index_ = { 0,2,3, 0,1,2, 1,5,6, 1,6,2, 5,7,6, 5,4,7, 4,9,7, 4,8,9, 12,11,10, 12,13,11, 3,14,15, 3,2,14 };//時計回りの順番に書いてる方向にだけ描画させるから見せたい方向から見て時計回りにすればいい
	//        手前　　　　　右面　　　　　裏面　　　　　左面　　　　　上面　　　　　      下面
}

Dice::~Dice()
{
}

void Dice::MakeVerBf()
{

	

	// 頂点情報
	VERTEX vertices[] =
	{
		//参考　https://gihyo.jp/dev/serial/01/as3/0049
		// https://shibuya24.info/entry/unity-mesh-dynamic-apply-texture
		//pingの画像見ながらやったらわかりやすい
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },	// 四角形の頂点（左上）
		{XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f),   XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) },	// 四角形の頂点（右上）
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },	// 四角形の頂点（右下）
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) },	// 四角形の頂点（左下）		
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),  XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) },	//4
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),   XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) },	//5
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),  XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },	//6
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) },	//7
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	//8(頂点０とxy座標はおなじだけどuv座標だけ違う)  |テクスチャ一周したところでUV座標が被るから新しく作る必要あり
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f) },	//9(頂点3と)                                     |
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },	//10(頂点0)                                      |テクスチャの形的に上面のテクスチャUV座標を完全に新しく作成
		{XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f),   XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },	//11(1)                                          |
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),  XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) },	//12(頂点4)　　　　　　　　　　　　　　　　　　　|
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),   XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f) },	//13(頂点5)　　　　　　　　　　　　　　　　　　　|
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),  XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) },	//14(頂点6と同じxy座標)　　　　　　　　　　　　　|下面用
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },	//15(頂点7)                                      |
	};

	// 頂点データ用バッファの設定
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
