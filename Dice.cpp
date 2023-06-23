#include "Dice.h"

Dice::Dice()
{
}

Dice::~Dice()
{
}

void Dice::SetVartices()
{
	// 頂点情報
	vertices_ =
	{
		//参考　https://gihyo.jp/dev/serial/01/as3/0049
		// https://shibuya24.info/entry/unity-mesh-dynamic-apply-texture
		//pingの画像見ながらやったらわかりやすい
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) , XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },	// 四角形の頂点（左上）
		{XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f),   XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },	// 四角形の頂点（右上）
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },	// 四角形の頂点（右下）
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },	// 四角形の頂点（左下）		
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),  XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//4  使ってない
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),   XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//5
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),  XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//6
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//7  使ってない
		//側面用
		//２と６の境界と６と５の境界
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),  XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//8  4
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),   XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//9  5
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),  XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//10 6
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//11 7
		//１と５の境界
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },	//12 0
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },	//13 3
		//上面用
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },	//14 0
		{XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f),   XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },	//15 1
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),  XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//16 4
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),   XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//17 5
		//下面用
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },	//18 2
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },	//19 3
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),  XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//20 6
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f,-1.0f, 0.0f) },	//21 7
	};

	vertexNum_ = vertices_.size();
}

void Dice::SetIndex()
{
	index_ = { 0,2,3, 0,1,2, 1,5,6, 1,6,2, 9,11,10, 9,8,11, 8,13,11, 8,12,13, 16,15,14, 16,17,15, 19,20,21, 19,18,20 };//時計回りの順番に書いてる方向にだけ描画させるから見せたい方向から見て時計回りにすればいい
	//         手前　　　　　右面　　　　　裏面　　　　　   左面　　　      　上面　　　　　       下面

	indexNum_ = index_.size();
}