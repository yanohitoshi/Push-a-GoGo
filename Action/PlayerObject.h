#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "PlayerObjectStateBase.h"

// クラスの前方宣言
class SkeletalMeshComponent;
class Animation;
class BoxCollider;
class Mesh;
class SphereCollider;
enum class PlayerState;


/*
@file PlayerObject.h
@brief ゲーム中のプレイヤー
	   ゲーム中のプレイヤーの初期化と更新処理を行う
*/
class PlayerObject : public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	再利用するかフラグ
	@param	オブジェクト判別用tag
	*/
	PlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~PlayerObject();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;
	
	/*
	@fn 入力処理
	@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	*/
	void GameObjectInput(const InputState& _keyState)override;
	
	/*
	@fn めり込み判定
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB);
	
	/*
	@fn 押し戻し処理
	*/
	void playerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox,Vector3& _calcFixVec);
	
	/*
	@fn 前方ベクトルを用いてキャラクターを回転させる関数
	*/
	void RotateToNewForward(const Vector3& forward);



private:

	/*
	@fn クリアしている状態かをチェックする関数
	*/
	void ClearChack(Tag _tag);
	
	/*
	@fn クリアに必要なスイッチをチェックする関数
	@param	_chackVector チェックするスイッチが格納されている可変長コンテナ
	*/
	void SwitchChackProcess(std::vector<GameObject*> _chackVector);

	/*
	@fn ひるむ可能性のある壁に当たった際にひるむ速度なのかチェックする関数
	*/
	void ChackFlinchSpeedProcess();

	/*
	@fn スイッチジャンプアクティブ関数
	*/
	void ActiveSwitchJumpProcess();

	/*
	@fn リスタートチェック関数
	*/
	void ChackRestartProcess();

	// 3Dモデルの描画を行うクラス
	SkeletalMeshComponent* skeltalMeshComponent;
	// Meshの読み込みを行うクラス
	Mesh* mesh;
	// AABBの当たり判定を行うクラス
	BoxCollider* boxCollider;
	// 球体の当たり判定を行うクラス
	SphereCollider* groundChackSphereCol;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/	
	void OnCollision(const GameObject& _hitObject)override;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数(足元判定用)
	@param	当たったGameObject
	*/
	void OnCollisionGround(const GameObject& _hitObject);

	// 着地effectを発生させる際に使用するフラグ
	// JumpFlagチェック用
	static bool chackJumpFlag;
	// isJumpingチェック用（ジャンプ中かどうか）
	static bool chackIsJumping;
	//重力
	static const float Gravity;

	// リスタートをかける時間
	const int RestartTime;
	// 入力値のdeadスペース
	const float DeadSpace;
	//加速度の定数
	const float MovePower;
	// 空中での加速定数
	const float AirMovePower;
	// 減速する力
	const float DecelerationForce;
	// 初速度
	const float FirstMovePower;
	//初期ジャンプ力定数
	const float FirstJumpPower;
	// プレイヤーが落下したかどうかを判定する位置
	//（※現状ステージに落下がないのでもしすり抜けてしまった場合）
	const float FallPpsitionZ;
	// 生成されるときのポジションをずらす
	const float FirstPositionZ;
	// ひるむ速度定数
	const float FlinchSpeed;

	//押し戻しに使うプレイヤーのAABB
	AABB playerBox;
	//右方向ベクトル
	Vector3 rightVec;
	//キャラクターの前方ベクトル
	Vector3 charaForwardVec;
	//方向に合わせて回転させるためのベクトル
	Vector3 rotateVec;
	// 生成されたときのポジションを保存するためのvector3変数
	Vector3 firstPos;
	// リスポーンする場所
	Vector3 respownPos;
	// 他のオブジェクトから押されている時の速度
	Vector3 pushedVelocity;

	// 死んだ際にすぐリスポーンさせないためのカウント
	int respawnCount;
	// 入力がない間カウント
	int reStartCount;
	//ジャンプボタンが押されている間のフレームカウント
	int jumpFrameCount;
	// 振り返りディレイ用カウント変数
	int turnDelayCount;

	// 速度
	float moveSpeed;
	//ジャンプ力
	float jumpPower;

	// 最終ステージ用のクリアフラグ
	bool clearFlag;
	// 最終ステージ以外での次のシーンへ遷移するフラグ
	bool nextSceneFlag;
	// 一定時間以上入力がなかった際にタイトルへ戻るフラグ
	bool restartFlag;
	//入力があったかどうか判定するためのフラグ
	bool inputFlag;
	//引き続きジャンプボタンが利用可能かフラグ
	bool isAvailableJumpKey;
	//ジャンプできるかフラグ
	bool jumpFlag;
	//ジャンプスイッチを押したかどうか
	bool switchJumpFlag;
	//接地フラグ
	bool onGround;
	//走り状態かどうか
	bool runFlag;
	// 入力が可能かどうか
	bool isAvailableInput;
	// ダウン状態かどうか
	bool downFlag;
	// ダウン時コンティニュー選択でYESが選択されたかどうか
	bool downUpFlag;
	// ダウン時コンティニュー選択でNOが選択されたかどうか
	bool downOverFlag;
	// リスポーン用フラグ
	bool respawnFlag;
	// dead状態かそうじゃないか確認用フラグ
	bool deadFlag;
	// 壁と押し戻しを行ったか
	bool isHitWall;
	
	// 今のプレーヤーのstate状態を保存するための変数
	PlayerState nowState;
	// 変更された次のプレーヤーのstate状態を保存するための変数
	PlayerState nextState;

	// Animationプール
	std::vector<const Animation*> animTypes;
	// stateプール
	std::vector<class PlayerObjectStateBase*> statePools;
	
public:// ゲッターセッター

	/*
	@fn skeltalMeshComponentのgetter関数
	@return SkeletalMeshComponent　SkeletalMeshComponentクラスのポインタを返す
	*/
	SkeletalMeshComponent* GetSkeletalMeshComponent() { return skeltalMeshComponent; }

	/*
	@fn Animationのgetter関数
	@param _state 現在のプレイヤーのステータス
	@return Animation Animationクラスのポインタを返す
	*/
	const Animation* GetAnimation(PlayerState _state);

	/*
	@fn 重力のgetter関数
	@return Gravity 重力定数
	*/
	static const float GetGravity() { return Gravity; }

	/*
	@fn chackJumpFlagのgetter関数
	@return chackJumpFlagを返す
	*/
	static bool GetChackJumpFlag() { return chackJumpFlag; }
	
	/*
	@fn chackIsJumpingのgetter関数
	@return chackIsJumpingを返す
	*/
	static bool GetChackIsJumpingFlag() { return chackIsJumping; }

	/*
	@fn forwardVecのgetter関数
	@return forwardVecを返す
	*/
	Vector3 GetForwardVec() { return forwardVec; }
	
	/*
	@fn rightVecのgetter関数
	@return rightVecを返す
	*/
	Vector3 GetRightVec() { return rightVec; }
	
	/*
	@fn charaForwardVecのgetter関数
	@return charaForwardVecを返す
	*/
	Vector3 GetCharaForwardVec() { return charaForwardVec; }
	
	/*
	@fn rotateVecのgetter関数
	@return rotateVecを返す
	*/
	Vector3 GetRotateVec() { return rotateVec; }
	
	/*
	@fn velocityのgetter関数
	@return velocityを返す
	*/
	Vector3 GetVelocity() { return velocity; }
	
	/*
	@fn respownPosのgetter関数
	@return respownPosを返す
	*/
	Vector3 GetRespownPos() { return respownPos; }

	/*
	@fn DeadSpaceのgetter関数
	@return DeadSpaceを返す
	*/
	const float GetDeadSpace() { return DeadSpace; }
	
	/*
	@fn FirstMovePowerのgetter関数
	@return FirstMovePowerを返す
	*/
	const float GetFirstMovePower() { return FirstMovePower; }
	
	/*
	@fn MovePowerのgetter関数
	@return MovePowerを返す
	*/
	const float GetMovePower() { return MovePower; }
	
	/*
	@fn AirMovePowerのgetter関数
	@return AirMovePowerを返す
	*/
	const float GetAirMovePower() { return AirMovePower; }
	
	/*
	@fn FirstJumpPowerのgetter関数
	@return FirstJumpPowerを返す
	*/
	const float GetFirstJumpPower() { return FirstJumpPower; }
	
	/*
	@fn DecelerationForceのgetter関数
	@return DecelerationForceを返す
	*/
	const float GetDecelerationForce() { return DecelerationForce; }

	/*
	@fn moveSpeedのgetter関数
	@return moveSpeedを返す
	*/
	float GetMoveSpeed() { return moveSpeed; }
	
	/*
	@fn jumpPowerのgetter関数
	@return jumpPowerを返す
	*/
	float GetJumpPower() { return jumpPower; }

	/*
	@fn turnDelayCountのgetter関数
	@return turnDelayCountを返す
	*/	
	int GetTurnDelayCount() { return turnDelayCount; }

	/*
	@fn onGroundのgetter関数
	@return onGroundを返す
	*/
	bool GetOnGround() { return onGround; }
	
	/*
	@fn jumpFlagのgetter関数
	@return jumpFlagを返す
	*/
	bool GetJumpFlag() { return jumpFlag; }
	
	/*
	@fn switchJumpFlagのgetter関数
	@return switchJumpFlagを返す
	*/
	bool GetSwitchJumpFlag() { return switchJumpFlag; }
	
	/*
	@fn isAvailableJumpKeyのgetter関数
	@return isAvailableJumpKeyを返す
	*/
	bool GetIsAvailableJumpKey() { return isAvailableJumpKey; }
	
	/*
	@fn inputFlagのgetter関数
	@return inputFlagを返す
	*/
	bool GetInputFlag() { return inputFlag; }
	
	/*
	@fn runFlagのgetter関数
	@return runFlagを返す
	*/
	bool GetRunFlag() { return runFlag; }
	
	/*
	@fn deadFlagのgetter関数
	@return deadFlagを返す
	*/
	bool GetDeadFlag() { return deadFlag; };
	
	/*
	@fn respawnFlagのgetter関数
	@return respawnFlagを返す
	*/
	bool GetRespawnFlag() { return respawnFlag; };
	
	/*
	@fn isAvailableInputのgetter関数
	@return isAvailableInputを返す
	*/
	bool GetIsAvailableInput() { return isAvailableInput; };
	
	/*
	@fn isHitWallのgetter関数
	@return isHitWallを返す
	*/
	bool GetIsHitWall() { return isHitWall; };

	/*
	@fn clearFlagのgetter関数
	@return clearFlagを返す
	*/
	bool GetClearFlag() { return clearFlag; }
	
	/*
	@fn nextSceneFlagのgetter関数
	@return nextSceneFlagを返す
	*/
	bool GetNextSceneFlag() { return nextSceneFlag; }

	/*
	@fn restartFlagのgetter関数
	@return restartFlagを返す
	*/
	bool GetRestartFlag() { return restartFlag; }

	/*
	@fn jumpFrameCountのgetter関数
	@return jumpFrameCountを返す
	*/
	int GetJumpFrameCount() { return jumpFrameCount; }

	/*
	@fn nowStateのgetter関数
	@return nowStateを返す
	*/
	PlayerState GetNowState() { return nowState; }

	/*
	@fn charaForwardVecのsetter関数
	@param	Vector3 _charaForwardVec キャラクターの前方ベクトル
	*/
	void SetCharaForwardVec(Vector3 _charaForwardVec) { charaForwardVec = _charaForwardVec; }
	
	/*
	@fn velocityのsetter関数
	@param	Vector3 _velocity キャラクターの速度ベクトル
	*/
	void SetVelocity(Vector3 _velocity) { velocity = _velocity; }
	
	/*
	@fn respownPosのsetter関数
	@param	Vector3 _respownPos キャラクターのリスポーンするポジション
	*/
	void SetRespownPos(Vector3 _respownPos) { respownPos = _respownPos; }

	/*
	@fn moveSpeedのsetter関数
	@param	float _moveSpeed キャラクターのスピード
	*/
	void SetMoveSpeed(float _moveSpeed) { moveSpeed = _moveSpeed; }

	/*
	@fn jumpPowerのsetter関数
	@param	float _jumpPower キャラクターのジャンプ力
	*/
	void SetJumpPower(float _jumpPower) { jumpPower = _jumpPower; }

	/*
	@fn turnDelayCountのsetter関数
	@param	int _turnDelayCount キャラクターの振り返りディレイカウント
	*/
	void SetTurnDelayCount(int _turnDelayCount) { turnDelayCount = _turnDelayCount; }

	/*
	@fn jumpFlagのsetter関数
	@param	bool _jumpFlag ジャンプ可能かの状態をセット
	*/
	void SetJumpFlag(bool _jumpFlag) { jumpFlag = _jumpFlag; }
	
	/*
	@fn switchJumpFlagのsetter関数
	@param	bool _switchJumpFlag スイッチジャンプ状態のセット
	*/
	void SetSwitchJumpFlag(bool _switchJumpFlag) { switchJumpFlag = _switchJumpFlag; }
	
	/*
	@fn isAvailableJumpKeyのsetter関数
	@param	bool _isAvailableJumpKey ジャンプ利用可能かの状態をセット
	*/
	void SetIsAvailableJumpKey(bool _isAvailableJumpKey) { isAvailableJumpKey = _isAvailableJumpKey; }
	
	/*
	@fn inputFlagのsetter関数
	@param	bool _inputFlag 入力されているかをセット
	*/
	void SetInputFlag(bool _inputFlag) { inputFlag = _inputFlag; }
	
	/*
	@fn runFlagのsetter関数
	@param	bool _runFlag 走り状態かどうかをセット
	*/
	void SetRunFlag(bool _runFlag) { runFlag = _runFlag; }
	
	/*
	@fn jumpFrameCountのsetter関数
	@param	bool _jumpFrameCount ジャンプ中のカウントをセット
	*/
	void SetJumpFrameCount(bool _jumpFrameCount) { jumpFrameCount = _jumpFrameCount; }
	
	/*
	@fn deadFlagのsetter関数
	@param	bool _deadFlag 死亡状態かどうかをセット
	*/
	void SetDeadFlag(bool _deadFlag) { deadFlag = _deadFlag; }
	
	/*
	@fn respawnFlagのsetter関数
	@param	bool _respawnFlag リスポーンフラグをセット
	*/
	void SetRespawnFlag(bool _respawnFlag) { respawnFlag = _respawnFlag; }
	
	/*
	@fn isAvailableInputのsetter関数
	@param	bool _isAvailableInput 入力可能かどうかをセット
	*/
	void SetIsAvailableInput(bool _isAvailableInput) { isAvailableInput = _isAvailableInput; }
	
	/*
	@fn isHitWallのsetter関数
	@param	bool _isHitWall 怯みモーションを行う壁にヒットしたかどうかをセット
	*/
	void SetIsHitWall(bool _isHitWall) { isHitWall = _isHitWall; }

};

