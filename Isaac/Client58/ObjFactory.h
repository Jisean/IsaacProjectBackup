#pragma once
#include "Obj.h"

template<typename T>
class CObjFactory
{
public:
	static CObj*	CreateObj()
	{
		CObj*	pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	///////////////////////////////////
	static CObj*	CreateObj(D3DXVECTOR3 vPos)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos);

		return pObj;
	}

	static CObj*	CreateObj(float _fX, float _fY)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(_fX, _fY);

		return pObj;
	}
	////////일반 객체 생성용//////////

	//////////////////////////////////
	static CObj*	CreateObj(D3DXVECTOR3 vPos, FIREWAY _way)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos, _way);

		return pObj;
	}

	static CObj*	CreateObj(float _fX, float _fY, FIREWAY _way)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(_fX, _fY, _way);

		return pObj;
	}
	////////////눈물 생성용///////////


	//////////////////////////////////
	static CObj*	CreateObj(D3DXVECTOR3 vPos, HUDTYPE _type)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos, _type);

		return pObj;
	}

	static CObj*	CreateObj(D3DXVECTOR3 vPos, HUDNUMTYPE _type)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos, _type);

		return pObj;
	}
	///////////픽업ui 생성용/////////

	/////////////////////////////////

	static CObj*	CreateObj(D3DXVECTOR3 vPos, BOSSHP _type)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos, _type);

		return pObj;
	}

	/////////보스hp바 생성용/////////

	/////////////////////////////////

	static CObj*	CreateObj(D3DXVECTOR3 vPos, PICKUP _type)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos, _type);

		return pObj;
	}
	////////픽업아이템 생성용////////

	/////////////////////////////////
	static CObj*	CreateObj(D3DXVECTOR3 vPos, PASSIVEITEM _type)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos, _type);

		return pObj;
	}
	////////자동아이템 생성용///////

	////////////////////////////////


	///////수동아이템 생성용////////

	////////////////////////////////

	static CObj*	CreateObj2(float _fX, float _fY, PASSIVEITEM _type)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos2(_fX, _fY, _type);

		return pObj;
	}
	///////코스튬 생성용////////////

	////////////////////////////////
	static CObj*	CreateObj(float _fX, float _fY, D3DXVECTOR3 _vDir, float Angle)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(_fX,_fY,_vDir,Angle);

		return pObj;
	}
	////////적 총알 생성용//////////

	////////////////////////////////

	static CObj*	CreateObj(D3DXVECTOR3 vPos, EFFECT _type)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos, _type);

		return pObj;
	}
	///////이펙트 생성용////////////

public:
	CObjFactory(void){	}
	~CObjFactory(void){	}
};
