#pragma once
#include "NeedleObject.h"

class MoveNeedleObject :
    public NeedleObject
{
public:

	/*
	@fn コンストラクタ
	@param	親となるobjectのポインタ
	@param	親objectとの間隔
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	@param	速度
	*/
	MoveNeedleObject(GameObject* _owner, const Vector3& _offset, const Vector3& _size, const Tag& _objectTag, const float& _speed);
	~MoveNeedleObject();

	/*
	@fn 更新処理
	@param	フレームレート固定用deltaTime
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	
	// 3Dモデルの描画を行うクラス
	Mesh* mesh;
	MeshComponent* meshComponent;
	// 当たり判定を行うクラス
	BoxCollider* boxCollider;
	// 親となるクラスのポインタ保存用変数
	GameObject* owner;

	//初期位置
	Vector3 initPos;
	//移動先位置
	Vector3 goalPos;
	//移動開始フラグ
	bool moveFlag;
	//反転フラグ
	bool inversionFlag;
	//移動間隔カウント
	int intervalCount;
	//移動速度
	const float moveSpeed;
	//移動方向
	Vector3 direction;

};

