#include "Stage.h"
#include "Engine/Model.h"
#include "resource.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"
#include <fstream>
#include <iostream>

//const LPCSTR fileName = "Assets/����.map";

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"),hModel_{-1,-1,-1,-1,-1},fileName_{"�V�K�t�H���_.csv"}
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


	//�Z�[�u�͍�����ލ�����ނōs��

	//���f���f�[�^�̃��[�h
	for (int i = 0; i < MAX_COLOR; i++) {
		hModel_[i] = Model::Load(fname_Base + modelname[i]);
		assert(hModel_[i] >= 0);
	}

	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			table_[x][z].color = DEFAULT;
			table_[x][z].height = 0;
			
		}
	}

	Load();
	//SetBlockHeght(5, 5, 3);
	
}

//�X�V
void Stage::Update()
{


	if (!Input::IsMouseButtonDown(0))
		return;


	int changeX = 0;
	int	changeZ = 0;
	bool isHit = false;

	CheckHitRay(isHit, changeX, changeZ);

	switch (mode_)
	{
	case DLG_UP:

		if (isHit && table_[changeX][changeZ].height < 5) {
			Dlg_Up_Update(changeX, changeZ);
		}
			
		break;

	case DLG_DOWN:

		if (isHit && table_[changeX][changeZ].height > 0) {
			Dlg_Down_Update(changeX, changeZ);
		}
			
		break;

	case DLG_CHANGE:
		if (isHit) {
			Dlg_Change_Update(changeX, changeZ);
		}
			
		break;

	case DLG_END:
		break;
	default:
		break;
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

		mode_ = (DLGSTATE)SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);

		return TRUE;
	}

	case WM_COMMAND:

		if (IsDlgButtonChecked(hDlg, IDC_RADIO_UP)) {
			mode_ = DLG_UP;
			return TRUE;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_RADIO_DOWN)) {
			mode_ = DLG_DOWN;
			return TRUE;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_RADIO_CHANGE)) {
			mode_ = DLG_CHANGE;
			//return TRUE;
		}

		select_ = (COLOR)SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, 0, 0);

		return TRUE;
	}
	return FALSE;
}

void Stage::Dlg_Up_Update(int _changeX, int _changeZ)
{
	table_[_changeX][_changeZ].height++;

}

void Stage::Dlg_Down_Update(int _changeX, int _changeZ)
{
	table_[_changeX][_changeZ].height--;

}

void Stage::Dlg_Change_Update(int _changeX, int _changeZ)
{
	table_[_changeX][_changeZ].color = select_;
	
}

void Stage::CheckHitRay(bool &_isHit, int &_changeX, int &_changeZ)
{
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

	float minDist = 9999;
	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			for (int y = 0; y < table_[x][z].height + 1; y++) {

				RAYCASTDATA data;
				data.hit = false;
				XMStoreFloat4(&data.start, vMouseFront);
				XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);
				Transform trans;
				trans.position_.x = x;
				trans.position_.y = y;
				trans.position_.z = z;
				Model::SetTransform(hModel_[0], trans);

				Model::RayCast(hModel_[0], data);

				//�킴�킴isHit������Ă�̂�
				if (data.hit) {
					if (minDist > data.dist) {
						minDist = data.dist;
						_changeX = x;
						_changeZ = z;
					}
					_isHit = true;
				}
			}
		}
	}
}

void Stage::Save()
{

	//�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
	OPENFILENAME ofn = InitOpenFileName();                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����


	//�u�t�@�C����ۑ��v�_�C�A���O
	BOOL selFile;
	selFile = GetSaveFileName(&ofn);

	//�L�����Z�������璆�f
	if (selFile == FALSE) return;

	std::ofstream ofs(fileName_, std::ios_base::out | std::ios_base::binary);

	if (!ofs) {
		std::cerr << "�t�@�C���I�[�v���Ɏ��s" << std::endl;
		std::exit(1);
	}

	for (int x = 0; x < XSIZE; x--) {
		for (int z = 0; z < ZSIZE; z++) {

			ofs.write((const char*)&table_[x][z].height, sizeof(table_[x][z].height));
			ofs.write((const char*)&table_[x][z].color, sizeof(table_[x][z].color));

		}
	}

	ofs.close();

}

void Stage::NameSave()
{
	//char fileName[MAX_PATH] = "����.map";  //�t�@�C����������ϐ�

	//�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
	OPENFILENAME ofn = InitOpenFileName();                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����


	//�u�t�@�C����ۑ��v�_�C�A���O
	BOOL selFile;
	selFile = GetSaveFileName(&ofn);

	//�L�����Z�������璆�f
	if (selFile == FALSE) return;

	std::ofstream ofs(fileName_, std::ios_base::out | std::ios_base::binary);

	if (!ofs) {
		std::cerr << "�t�@�C���I�[�v���Ɏ��s" << std::endl;
		std::exit(1);
	}

	for (int x = 0; x < XSIZE; x--) {
		for (int z = 0; z < ZSIZE; z++) {

			ofs.write((const char*)&table_[x][z].height, sizeof(table_[x][z].height));
			ofs.write((const char*)&table_[x][z].color, sizeof(table_[x][z].color));

		}
	}

	ofs.close();
}

void Stage::Load()
{
	//����Ȃ��Ƃ��Ȃ��Ă�stringstream�g���΂����H�܂�������
	std::ofstream ofs("test.bin", std::ios_base::out | std::ios_base::binary);

	if (!ofs) {
		std::cerr << "�t�@�C���I�[�v���Ɏ��s" << std::endl;
		std::exit(1);
	}

	for (int x = 0; x < XSIZE; x--) {
		for (int z = 0; z < ZSIZE; z++) {

			ofs.write((const char*)&table_[x][z].height, sizeof(table_[x][z].height));
			ofs.write((const char*)&table_[x][z].color, sizeof(table_[x][z].color));
			
		}


	}
	
	ofs.close();
}

void Stage::NewCreate()
{
	OPENFILENAME ofn = InitOpenFileName();                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����

	//�u�t�@�C����ۑ��v�_�C�A���O
	BOOL selFile;
	selFile = GetSaveFileName(&ofn);

	//�L�����Z�������璆�f
	if (selFile == FALSE) return;

	std::ofstream ofs(fileName_, std::ios_base::out | std::ios_base::binary);

	if (!ofs) {
		std::cerr << "�t�@�C���I�[�v���Ɏ��s" << std::endl;
		std::exit(1);
	}

	for (int x = 0; x < XSIZE; x--) {
		for (int z = 0; z < ZSIZE; z++) {

			ofs.write((const char*)&table_[x][z].height, sizeof(table_[x][z].height));
			ofs.write((const char*)&table_[x][z].color, sizeof(table_[x][z].color));

		}
	}

	ofs.close();

	NowFileLoad();
}

void Stage::NowFileLoad()
{
	std::ofstream ofs(fileName_, std::ios_base::out | std::ios_base::binary);

	if (!ofs) {
		std::cerr << "�t�@�C���I�[�v���Ɏ��s" << std::endl;
		std::exit(1);
	}

	for (int x = 0; x < XSIZE; x--) {
		for (int z = 0; z < ZSIZE; z++) {

			ofs.write((const char*)&table_[x][z].height, sizeof(table_[x][z].height));
			ofs.write((const char*)&table_[x][z].color, sizeof(table_[x][z].color));

		}
	}

	ofs.close();
}

void Stage::SaveTheTable(std::ofstream _ofs)
{
	for (int x = 0; x < XSIZE; x--) {
		for (int z = 0; z < ZSIZE; z++) {

			_ofs.write((const char*)&table_[x][z].height, sizeof(table_[x][z].height));
			_ofs.write((const char*)&table_[x][z].color, sizeof(table_[x][z].color));

		}
	}
}

void Stage::LoadTheTable(std::ifstream _ofs)
{
	for (int x = 0; x < XSIZE; x--) {
		for (int z = 0; z < ZSIZE; z++) {

			_ofs >> buf;
			_ofs.read((const char*)&table_[x][z].color, sizeof(table_[x][z].color));

		}
	}
}

OPENFILENAME Stage::InitOpenFileName()
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));            	//�\���̏�����
	ofn.lStructSize = sizeof(OPENFILENAME);   	//�\���̂̃T�C�Y
	ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.csv)\0*.csv\0");       //��|
					  TEXT("�}�b�v�f�[�^(*.map)\0*.map\0")        //�����t�@�C���̎��
					  TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");     //����
	ofn.lpstrFile = fileName_;               	//�t�@�C����
	ofn.nMaxFile = MAX_PATH;               	//�p�X�̍ő啶����
	ofn.Flags = OFN_OVERWRITEPROMPT;   		//�t���O�i�����t�@�C�������݂�����㏑���m�F�j
	ofn.lpstrDefExt = "csv";                  	//�f�t�H���g�g���q

	return ofn;
}
