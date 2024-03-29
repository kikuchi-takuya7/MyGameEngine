#include "Model.h"


namespace Model {

    vector<ModelData*>modelList;

    int Load(std::string _fileName)
    {
        //構造体のインスタンスを作成
        ModelData* pData = new ModelData;

        //そのメンバのファイル名に引数を代入
        pData->fileName_ = _fileName;
		// Fbxオブジェクトを作成し、ロード
		bool isUsed = false;	//使ったことのあるモデルか

		for (auto& e : modelList)
		{

			if (e != nullptr && e->fileName_ == _fileName) {
				pData->pFbx_ = e->pFbx_;
				isUsed = true;
				break;
			}
		}

		//使ったことのないファイルを開く
		if (isUsed == false) {
			pData->pFbx_ = new Fbx;
			if (FAILED(pData->pFbx_->Load(_fileName))) {
				//開けなかった
				SAFE_DELETE(pData->pFbx_);
				SAFE_DELETE(pData);
				return -1;
			}
			pData->fileName_ = _fileName;	//開けた
		}

		// 構造体の中身が埋まったので、動的配列に突っ込む
		modelList.push_back(pData);

		// 番号（配列の要素数-1）を返す
		return (int)modelList.size() - 1;
    }

    void SetTransform(int _hModel, Transform _t)
    {
		//モデル番号は、modelListのインデックス
		modelList[_hModel]->transform_ = _t;
    }

    void Draw(int _hModel)
    {
		//モデル番号は、modelListのインデックス
		modelList[_hModel]->pFbx_->Draw(modelList[_hModel]->transform_);
    }

    void Release()
    {
		bool isReffed = false;	//参照されたか
		for (int i = 0; i < modelList.size(); i++)
		{
			for (int j = i + 1; j < modelList.size(); j++)
			{
				if (modelList[i]->pFbx_ == modelList[j]->pFbx_) {	// どっちかが片方を参照してる
					isReffed = true;
					break;
				}
			}
			if (isReffed == false) {	// 参照してないならdelete
				SAFE_DELETE(modelList[i]->pFbx_);
			}
			SAFE_DELETE(modelList[i]);
		}
		modelList.clear();	// メモリに入ってるアドレスを消す(メモリリークを防ぐ)
    }

	void RayCast(int hModel, RAYCASTDATA& rayData)
	{

		//0、モデルのトランスフォームをカリキュレーション
		modelList[hModel]->transform_.Calclation();
		//1,ワールド行列の逆行列
		XMMATRIX invWM = XMMatrixInverse(nullptr, modelList[hModel]->transform_.GetWorldMatrix());

		//2,レイの通過点を求める(モデル空間でのレイの方向ベクトルを求める)
		XMVECTOR vpass{ rayData.start.x + rayData.dir.x,
						rayData.start.y + rayData.dir.y,
						rayData.start.z + rayData.dir.z, 
						rayData.start.w + rayData.dir.w };
		//3,rayData.startをモデル空間に変換（1をかける）
		XMVECTOR vstart = XMLoadFloat4(&rayData.start);
		vstart = XMVector3TransformCoord(vstart, invWM); //Transformcoodはw要素を無視してくれるらしい
		XMStoreFloat4(&rayData.start, vstart); //これ　値をセットすんの忘れてた。。。
		//4,（始点から方向ベクトルをちょい伸ばした先）通過点（２）に１をかける
		vpass = XMVector3TransformCoord(vpass, invWM);
		//5,rayData.dirを３から４に向かうベクトルにする（引き算）
		vpass = vpass - vstart;
		XMStoreFloat4(&rayData.dir, vpass);

		//指定したモデル番号のFBXにレイキャスト!
		modelList[hModel]->pFbx_->RayCast(rayData);

		
	}

    void AllRelease()
    {
    }

}
