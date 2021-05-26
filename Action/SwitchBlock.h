#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include <glew.h>

// クラスの前方宣言
class BoxCollider;
class Mesh;
class ChangeColorMeshComponent;

/*
@file SwitchBlock.h
@brief スイッチの生成と更新処理を行う
*/
class SwitchBlock : public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	*/
	SwitchBlock(GameObject* _owner, const Vector3& _size, const Tag& _objectTag);
	
	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~SwitchBlock();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn 可動処理関数	
	*/
	void MovableProcess();
	
	/*
	@fn 色変更処理
	*/
	void ColorChangeProcess();
	
	/*
	@fn 色セット処理
	*/
	void SetColorProcess();

	/*
	@fn タグごとのスイッチの状態チェック関数
	@param _Tag チェックするスイッチのTag
	*/	void ChackOnFlag(Tag& _Tag);

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
		動く床と接している時にその速度をもらうための
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;
	
	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
		プレイヤーの足元判定とのOnCollision
	@param	当たったGameObject
	*/
	void PlayerFootOnCollision(const GameObject& _hitObject);

	// 色変更機能付きMeshComponent
	ChangeColorMeshComponent* meshComponent;
	// 動く床と接している時にその速度をもらうためのCollider
	BoxCollider* boxCollider;
	// プレイヤーとの足元判定用Collider
	BoxCollider* PlayerFootBoxCollider;
	// メッシュからAABBの最大点最小点を得るときに使う
	Mesh* mesh;
	// Switchが利用可能か
	bool isAvailableSwitch;
	// Switchの初期ポジション保存用
	Vector3 initPosition;
	// playerがswitchに乗っているかどうか
	bool isOnPlayer;
	bool isHitPlayer;
	// 押すのを止めるかどうか
	bool pushStop;
	// 色を変えるかどうか
	bool changeColorFlag;
	// 前のフレームで色変更が行われたかどうか
	bool tmpChangeColorFlag;
	// switchの停止位置
	float stopPoint;

	// 停止ポジションを定めるための定数
	const float ShiftStopPosition;
	// 上昇速度
	const float MoveUpSpeed;
	// 下降速度
	const float MoveDownSpeed;
	// 全スイッチがONの時の色
	const Vector3 AllClearColer;
	// スイッチがONの時の色
	const Vector3 OnColor;
	// スイッチがOFFの時の色
	const Vector3 OffColor;
};
