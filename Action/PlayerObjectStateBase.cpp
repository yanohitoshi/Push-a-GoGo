#include "PlayerObjectStateBase.h"

void PlayerObjectStateBase::GroundMove(PlayerObject* _owner, const InputState& _keyState)
{
	// 入力情報チェック処理
	ChackInputProcess(_owner, _keyState);
}

void PlayerObjectStateBase::ChackInput(PlayerObject* _owner, const InputState& _keyState)
{

	// コントローラのアナログスティックの入力情報を計算する
	Vector3 axis = ChackControllerAxis(_keyState);

	// 取得した数値を見てデッドスペース外だったら入力処理を行う
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// 移動入力フラグをtrueにセット
		_owner->SetInputFlag(true);
	}
	else
	{
		// 移動入力フラグをfalseにセット
		_owner->SetInputFlag(false);
	}

	// 接地中でジャンプ中でもなければ
	if (_owner->GetOnGround() == true && _owner->GetJumpFlag() == false)
	{
		// ジャンプを割り当てられているコントローラーのボタンが押されたらもしくはジャンプスイッチが押されたら
		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
			_owner->GetSwitchJumpFlag() == true)
		{
			// ジャンプフラグをtrueにセット
			_owner->SetJumpFlag(true);
		}
	}
}

void PlayerObjectStateBase::RotationProcess(PlayerObject* _owner, Vector3 _forward, Vector3 _tmpForward)
{
	// 前方ベクトルが前のフレームから変わっていたら
	if (_tmpForward != _forward)
	{
		//前のフレームと今のフレームの前方ベクトルで線形補間を取る
		Vector3 rotatioin = Vector3::Lerp(_forward, _tmpForward, 0.01f);

		// 回転軸を求める
		_owner->RotateToNewForward(rotatioin);
		// 前方ベクトル更新
		_owner->SetCharaForwardVec(rotatioin);
	}

}

Vector3 PlayerObjectStateBase::ChackControllerAxis(const InputState& _keyState)
{
	//Axisの値をとる32700~-32700
	float ALX = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
	float ALY = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);

	//アナログスティックのキー入力を取得
	Vector2 Axis = Vector2(0.0f, 0.0f);
	Axis = _keyState.Controller.GetLAxisLeftVec();

	//実際に動かしたい軸がずれているので補正
	Vector3 axis = Vector3(Axis.y * -1.0f, Axis.x * -1.0f, 0.0f);

	// 軸を返す
	return axis;
}

void PlayerObjectStateBase::ChackInputProcess(PlayerObject* _owner, const InputState& _keyState)
{
	// コントローラのアナログスティックの入力情報を計算する
	Vector3 axis = ChackControllerAxis(_keyState);

	// 取得した数値を見てデッドスペース外だったら入力処理を行う
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// 入力がある場合の処理
		InputMovableProcess(_owner, axis);
	}
	else
	{
		// 入力がない場合の処理
		UninputMovableProcess(_owner);
	}

	// ジャンプを割り当てられているコントローラーのボタンが押されたらもしくはジャンプスイッチが押されたら
	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
		_owner->GetSwitchJumpFlag() == true)
	{
		// ジャンプ状態遷移準備
		JumpTransitionProcess(_owner);
	}
}

void PlayerObjectStateBase::InputMovableProcess(PlayerObject* _owner, Vector3 _axis)
{
	// 前のフレームのキャラクターの前方ベクトルを保存
	Vector3 tmpForward = _owner->GetCharaForwardVec();

	// 方向キーの入力値とカメラの向きから、移動方向を決定
	Vector3 forward = _owner->GetForwardVec() * _axis.x + _owner->GetRightVec() * _axis.y;
	forward.Normalize();

	// 移動速度に加速度を足す
	moveSpeed += _owner->GetMovePower();

	// 移動速度が最大値を超えていたら固定する
	if (moveSpeed >= MaxMoveSpeed)
	{
		// 移動速度の最大定数を代入
		moveSpeed = MaxMoveSpeed;
	}

	// 移動ベクトルに速度をかける
	velocity.x = forward.x * moveSpeed;
	velocity.y = forward.y * moveSpeed;

	// 回転処理
	RotationProcess(_owner, forward, tmpForward);

	// ownerの移動速度を更新
	_owner->SetMoveSpeed(moveSpeed);

}

void PlayerObjectStateBase::UninputMovableProcess(PlayerObject* _owner)
{
	// 移動入力フラグをfalseにセット
	_owner->SetInputFlag(false);
}

void PlayerObjectStateBase::JumpTransitionProcess(PlayerObject* _owner)
{
	// ジャンプフラグをtrueにセット
	_owner->SetJumpFlag(true);
}
