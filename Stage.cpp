#include "Stage.h"
#include "Engine/Model.h"
#include "resource.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"


//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"),hModel_{-1,-1,-1,-1,-1}
{
}

//������
void Stage::Initialize()
{

	srand(time(NULL));

	string modelname[] = {
		"BoxDefault.fbx",
		"BoxBrick.fbx",
		"BoxGrass.fbx",
		"BoxSand.fbx",
		"BoxWater.fbx"
	};

	string fname_Base = "assets/";
	//���f���f�[�^�̃��[�h
	for (int i = 0; i < MAX_COLOR; i++) {
		hModel_[i] = Model::Load(fname_Base + modelname[i]);
		assert(hModel_[i] >= 0);
	}

	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			table_[x][z].color = BRINK;
			table_[x][z].height = 0;
			
		}
	}

	SetBlockHeght(5, 5, 3);
	
}

//�X�V
void Stage::Update()
{

	if (Input::IsMouseButtonDown(0)) {

		float w = (float)(Direct3D::scrWidth / 2.0f);
		float h = (float)(Direct3D::scrHeight / 2.0f);
		float offsetX = 0;
		float offsetY = 0;
		float minZ = 0;
		float maxZ = 1;

		//�r���[�|�[�g�쐬
		XMMATRIX vp =
		{
			w                ,0                ,0           ,0,
			0                ,-h               ,0           ,0,
			0                ,0                ,maxZ - minZ ,0,
			offsetX + w      ,offsetY + h      ,minZ        ,1
		};

		//�r���[�|�[�g���t�s���
		XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
		//�v���W�F�N�V�����ϊ�
		XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
		//�т�[�ϊ�
		XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
		XMVECTOR mousePosVec = Input::GetMousePosition();
		XMFLOAT3 mousePosFront;
		XMStoreFloat3(&mousePosFront, mousePosVec);
		mousePosFront.z = 0.0;
		XMVECTOR mouseVec = Input::GetMousePosition();
		XMFLOAT3 mousePosBack;
		XMStoreFloat3(&mousePosBack, mouseVec);
		mousePosBack.z = 1.0f;

		//1,mousePosFront���x�N�g���ɕϊ�
		XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
		//2. 1��invVP,invPrj,invView��������
		vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
		//3,mousePosBack���x�N�g���ɕϊ�
		XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
		//4,3��invVP,invPrj,invVeew��������
		vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);
		//5,2����4�Ɍ������ă��C��łi�Ƃ肠�����j

		int changeX = 0;
		int	changeZ = 0;
		float minDist = 9999;
		for (int x = 0; x < 15; x++) {
			for (int z = 0; z < 15; z++) {
				for (int y = 0; y < table_[x][z].height + 1; y++) {

					RAYCASTDATA data;
					XMStoreFloat4(&data.start, vMouseFront);
					XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);
					Transform trans;
					trans.position_.x = x;
					trans.position_.y = y;
					trans.position_.z = z;
					Model::SetTransform(hModel_[0], trans);

					Model::RayCast(hModel_[0], data);

					if (data.hit) {
						if (data.dist > minDist)
							continue;
						changeX = x;
						changeZ = z;
						data.hit = false;
						continue;
					}
				}
			}
		}

		table_[changeX][changeZ].height++;
	}
}

//�`��
void Stage::Draw()
{

	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			for (int y = 0; y < table_[x][z].height + 1; y++) {
				int type = table_[x][z].color;
				Transform blockTrans;
				blockTrans.position_.z = z;
				blockTrans.position_.x = x;
				blockTrans.position_.y = y;
				Model::SetTransform(hModel_[type], blockTrans);
				Model::Draw(hModel_[type]);
				
			}
		}
	}
	
}

//�J��
void Stage::Release()
{
}

void Stage::SetBlock(int _x, int _z, COLOR _type)
{
	table_[_x][_z].color = _type;
	//�ꎟ���z��œ񎟌��z���\������Ȃ�
	//table_[_x * XSIZE +_z] = _type;
	//�|���Z�����ɂ��邩��Ax���W���O�̎���XSIZE���O�ɂȂ�z���W�������K�p�����Bx��2�Ƃ��Ȃ�30����ƂȂ�3�s�ڂ��炢�ɓ���
}

void Stage::SetBlockHeght(int _x, int _z, int _height)
{
	table_[_x][_z].height = _height;
}

//CALLBACK���������Ƃɂ���Ă����̃����o�֐��ɂ���
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		//�_�C�A���O���ł����Ƃ�
	case WM_INITDIALOG: {
		//���W�I�{�^���̏�����
		SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

		const char* modelname[] = {
		"�f�t�H���g",
		"��",
		"��",
		"��",
		"��"
		};
		//�R���{�{�b�N�X�̏�����
		for (int i = 0; i < 5; i++) {
			SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)modelname[i]);
		}
		mode_ = SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
		return TRUE;
	}

	/*case WM_COMMAND:
		mode_ = SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
		return TRUE;*/
	}
	return FALSE;
}