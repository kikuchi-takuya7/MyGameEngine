#include "Model.h"


namespace Model {

    vector<ModelData*>modelList;

    int Load(std::string _fileName)
    {
        //�\���̂̃C���X�^���X���쐬
        ModelData* pData = new ModelData;

        //���̃����o�̃t�@�C�����Ɉ�������
        pData->fileName_ = _fileName;
		// Fbx�I�u�W�F�N�g���쐬���A���[�h
		bool isUsed = false;	//�g�������Ƃ̂��郂�f����

		for (auto& e : modelList)
		{

			if (e != nullptr && e->fileName_ == _fileName) {
				pData->pFbx_ = e->pFbx_;
				isUsed = true;
				break;
			}
		}

		//�g�������Ƃ̂Ȃ��t�@�C�����J��
		if (isUsed == false) {
			pData->pFbx_ = new Fbx;
			if (FAILED(pData->pFbx_->Load(_fileName))) {
				//�J���Ȃ�����
				SAFE_DELETE(pData->pFbx_);
				SAFE_DELETE(pData);
				return -1;
			}
			pData->fileName_ = _fileName;	//�J����
		}

		// �\���̂̒��g�����܂����̂ŁA���I�z��ɓ˂�����
		modelList.push_back(pData);

		// �ԍ��i�z��̗v�f��-1�j��Ԃ�
		return (int)modelList.size() - 1;
    }

    void SetTransform(int _hModel, Transform _t)
    {
		//���f���ԍ��́AmodelList�̃C���f�b�N�X
		modelList[_hModel]->transform_ = _t;
    }

    void Draw(int _hModel)
    {
		//���f���ԍ��́AmodelList�̃C���f�b�N�X
		modelList[_hModel]->pFbx_->Draw(modelList[_hModel]->transform_);
    }

    void Release()
    {
		bool isReffed = false;	//�Q�Ƃ��ꂽ��
		for (int i = 0; i < modelList.size(); i++)
		{
			for (int j = i + 1; j < modelList.size(); j++)
			{
				if (modelList[i]->pFbx_ == modelList[j]->pFbx_) {	// �ǂ��������Е����Q�Ƃ��Ă�
					isReffed = true;
					break;
				}
			}
			if (isReffed == false) {	// �Q�Ƃ��ĂȂ��Ȃ�delete
				SAFE_DELETE(modelList[i]->pFbx_);
			}
			SAFE_DELETE(modelList[i]);
		}
		modelList.clear();	// �������ɓ����Ă�A�h���X������(���������[�N��h��)
    }

	void RayCast(int hModel, RAYCASTDATA& rayData)
	{

		//0�A���f���̃g�����X�t�H�[�����J���L�����[�V����
		modelList[hModel]->transform_.Calclation();
		//1,���[���h�s��̋t�s��
		XMMATRIX invWM = XMMatrixInverse(nullptr, modelList[hModel]->transform_.GetWorldMatrix());

		//2,���C�̒ʉߓ_�����߂�(���f����Ԃł̃��C�̕����x�N�g�������߂�)
		XMVECTOR vpass{ rayData.start.x + rayData.dir.x,
						rayData.start.y + rayData.dir.y,
						rayData.start.z + rayData.dir.z, 
						rayData.start.w + rayData.dir.w };
		//3,rayData.start�����f����Ԃɕϊ��i1��������j
		XMVECTOR vstart = XMLoadFloat4(&rayData.start);
		vstart = XMVector3TransformCoord(vstart, invWM); //Transformcood��w�v�f�𖳎����Ă����炵��
		//4,�i�n�_��������x�N�g�������傢�L�΂�����j�ʉߓ_�i�Q�j�ɂP��������
		vpass = XMVector3TransformCoord(vpass, invWM);
		//5,rayData.dir���R����S�Ɍ������x�N�g���ɂ���i�����Z�j
		vpass = vpass - vstart;
		XMStoreFloat4(&rayData.dir, vpass);

		//�w�肵�����f���ԍ���FBX�Ƀ��C�L���X�g!
		modelList[hModel]->pFbx_->RayCast(rayData);
	}

    void AllRelease()
    {
    }

}
