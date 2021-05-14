#include "PlayerObjectStateJunpEndToRun.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateJunpEndToRun::PlayerObjectStateJunpEndToRun()
	: DecelerationForce(75.0f)
{
}

PlayerObjectStateJunpEndToRun::~PlayerObjectStateJunpEndToRun()
{
}

PlayerState PlayerObjectStateJunpEndToRun::Update(PlayerObject* _owner, float _deltaTime)
{

	// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// アニメーションの再生が終わっていたら
	if (!skeletalMeshComponent->IsPlaying())
	{
		// 移動入力があったら
		if (_owner->GetInputFlag())
		{
			// ステータスを走り出し状態にする
			state = PlayerState::PLAYER_STATE_RUN_START;
		}
		else
		{
			// ステータスを待機状態にする
			state = PlayerState::PLAYER_STATE_IDLE;
		}
	}

	// ジャンプフラグもしくはスイッチジャンプフラグがtrueだったら
	if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		// ステータスをジャンプ開始状態にする
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	// ジャンプフラグがfalseかつ接地状態でも無ければ
	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		// ステータスをジャンプループ状態にする
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	// 死亡フラグが立っていたら
	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	// タイムオーバーフラグがtrueだったら
	if (CountDownFont::timeOverFlag == true)
	{
		// ステータスをコンティニュー選択開始状態にする
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}

	// ownerの変数を更新
	_owner->SetMoveSpeed(moveSpeed);

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateJunpEndToRun::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// 入力可能状態かを見る
	if (_owner->GetIsAvailableInput())
	{
		//実際に動かしたい軸がずれているので補正
		Vector3 axis = ChackControllerAxis(_keyState);

		//入力があるか
		if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
		{
			// 前のフレームのキャラクターの前方ベクトルを保存
			Vector3 tmpForward = _owner->GetCharaForwardVec();

			// 方向キーの入力値とカメラの向きから、移動方向を決定
			Vector3 forward = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
			forward.Normalize();

			moveSpeed += _owner->GetMovePower();

			if (moveSpeed >= MaxMoveSpeed)
			{
				moveSpeed = MaxMoveSpeed;
			}

			velocity.x = forward.x * moveSpeed;
			velocity.y = forward.y * moveSpeed;

			RotationProcess(_owner, forward, tmpForward);

			_owner->SetMoveSpeed(moveSpeed);

		}
		else
		{
			if (moveSpeed >= 0.0f)
			{
				moveSpeed -= DecelerationForce;
			}

			velocity.x = _owner->GetCharaForwardVec().x * moveSpeed;
			velocity.y = _owner->GetCharaForwardVec().y * moveSpeed;

			_owner->SetInputFlag(false);
		}

		// ジャンプを割り当てられているコントローラーのボタンが離されたら
		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed)
		{
			_owner->SetJumpFlag(true);
		}
	}
}

void PlayerObjectStateJunpEndToRun::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPEND_TO_RUN));
	// stateを着地ローリング状態にして保存
	state = PlayerState::PLAYER_STATE_JUMPEND_TO_RUN;

	// ownerの移動速度をもらう
	moveSpeed = _owner->GetMoveSpeed();
	// ownerの移動ベクトルをもらう
	velocity = _owner->GetVelocity();
	// 着地状態なのでZ軸は0に固定
	velocity.z = 0.0f;
	// 入力が入らない値をもらう
	inputDeadSpace = _owner->GetDeadSpace();

	// ownerのジャンプ力をリセット
	_owner->SetJumpPower(_owner->GetFirstJumpPower());
	_owner->SetIsAvailableJumpKey(true);
	_owner->SetJumpFlag(false);
}
