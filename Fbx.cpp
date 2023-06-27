#include "Fbx.h"



Fbx::Fbx(): pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), vertexCount_(0),polygonCount_(0)
{
}

Fbx::~Fbx()
{
	//SAFE_RELEASE(pTexture_);
	//SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}



HRESULT Fbx::Load(std::string fileName)
{
	//マネージャを生成
	FbxManager* pFbxManager = FbxManager::Create();

	//インポーターを生成
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp"); //シーンをロードするためのやつ
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//シーンオブジェクトにFBXファイルの情報を流し込む
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene"); //シーンを丸っと読み込む為のやつ
	fbxImporter->Import(pFbxScene); //インポート
	fbxImporter->Destroy();

	//メッシュ情報を取得
	FbxNode* rootNode = pFbxScene->GetRootNode(); //一つ一つのノードを保存（ノードとはfbxオブジェクトの子供のようなもの）
	FbxNode* pNode = rootNode->GetChild(0); //第一子（一番最初の子供）を取得。全て結合を選択したから第一子しかいないためこれが大事
	FbxMesh* mesh = pNode->GetMesh(); // メッシュの中に頂点情報とか入ってたりする

	//各情報の個数を取得

	vertexCount_ = mesh->GetControlPointsCount();	//頂点の数
	polygonCount_ = mesh->GetPolygonCount();	//ポリゴンの数
	materialCount_ = pNode->GetMaterialCount(); //マテリアルの数　一つのノード（子供）の中から情報をとってくる

	InitVertex(mesh);		//頂点バッファ準
	InitIndex(mesh);
	InitConstantBuffer();	//コンスタントバッファ準備
	InitMaterial(pNode); //マテリアル準備

	
	//マネージャ解放
	pFbxManager->Destroy();
	return S_OK;
}

//頂点バッファ準備
void Fbx::InitVertex(fbxsdk::FbxMesh* mesh)
{
	//頂点情報を入れる配列
	VERTEX* vertices = new VERTEX[vertexCount_];

	//全ポリゴン
	for (DWORD poly = 0; poly < polygonCount_; poly++)
	{
		//3頂点分
		for (int vertex = 0; vertex < 3; vertex++)
		{
			//調べる頂点の番号
			int index = mesh->GetPolygonVertex(poly, vertex);

			//頂点の位置
			FbxVector4 pos = mesh->GetControlPointAt(index);
			vertices[index].position = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);
		}
	}

	//頂点バッファ作成
	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexCount_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	HRESULT hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr)) {
		MessageBox(nullptr, "頂点バッファの作成に失敗しました", "エラー", MB_OK);

		//return E_FAIL;
	}

	delete[] vertices;
}


//インデックスバッファ準備
void Fbx::InitIndex(fbxsdk::FbxMesh* mesh)
{
	int* index = new int[polygonCount_ * 3];
	int count = 0;

	//全ポリゴン
	for (DWORD poly = 0; poly < polygonCount_; poly++)
	{
		//3頂点分
		for (DWORD vertex = 0; vertex < 3; vertex++)
		{
			index[count] = mesh->GetPolygonVertex(poly, vertex);
			count++;
		}
	}


	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * count;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	HRESULT hr;
	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr)) {
		MessageBox(nullptr, "インデックスバッファの作成に失敗しました", "エラー", MB_OK);

		//return E_FAIL;
	}

	delete[] index;
}

void Fbx::InitConstantBuffer()
{
	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	HRESULT hr;
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr)) {
		MessageBox(nullptr, "コンストラクトバッファの作成に失敗しました", "エラー", MB_OK);

		//return E_FAIL;
	}
}

void Fbx::InitMaterial(fbxsdk::FbxNode* pNode)
{
	pMaterialList_ = new MATERIAL[materialCount_];

	for (int i = 0; i < materialCount_; i++)
	{
		//i番目のマテリアル情報を取得
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		//テクスチャ情報
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse); //mayaでテクスチャ表示させるボタンあるやん？あの情報らしいで

		//テクスチャの数数
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>(); //テクスチャ貼ってあれば１出なければ０

		//テクスチャあり
		if (fileTextureCount)
		{

			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			const char* textureFilePath = textureInfo->GetRelativeFileName();

			//ファイル名+拡張だけにする
			char name[_MAX_FNAME];	//ファイル名
			char ext[_MAX_EXT];	//拡張子
			_splitpath_s(textureFilePath, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT); //今回ドライブとディレクトリ名はいらないので、ファイルの名前と拡張子だけ
			wsprintf(name, "%s%s", name, ext);

			//ファイルからテクスチャ作成
			pMaterialList_[i].pTexture = new Texture;
			pMaterialList_[i].pTexture->Load(name);

			//ID3D11SamplerState* pSampler = pMaterialList_[i].pTexture->GetSampler();
			//Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

			//ID3D11ShaderResourceView* pSRV = pMaterialList_[i].pTexture->GetSRV();
			//Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

			//Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

		}

		//テクスチャ無し
		else
		{
			pMaterialList_[i].pTexture = nullptr;
		}
	}
}

void Fbx::Draw(Transform& transform)
{

	Direct3D::SetShader(SHADER_TYPE::SHADER_3D);

	transform.Calclation();//トランスフォームを計算
	SetMap(transform);

	//SetTexture();

	//Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

	SetPipeline();


	Direct3D::pContext_->DrawIndexed(polygonCount_ * 3, 0, 0); //インデックス情報の数は何個数字を入れてるか
}

void Fbx::SetMap(Transform& transform)
{
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matNormal = XMMatrixTranspose(transform.GetNormalMatrix());

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
}

void Fbx::SetTexture()
{
	//ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	//Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	//ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	//Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	//Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開
}


void Fbx::SetPipeline()
{
	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int) * polygonCount_;
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

}

void Fbx::Release()
{
	//SAFE_RELEASE(pTexture_);
	//SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}
