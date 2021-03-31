#include "PlayerObjectStateIdle.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateIdle::PlayerObjectStateIdle()
{
}

PlayerObjectStateIdle::~PlayerObjectStateIdle()
{
}

PlayerState PlayerObjectStateIdle::Update(PlayerObject* _owner, float _deltaTime)
{

	state = PlayerState::PLAYER_STATE_IDLE;
	
	_owner->SetVelocity(velocity);

	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}
	else if (_owner->GetInputFlag())
	{
		if (_owner->GetRunFlag())
		{
			state = PlayerState::PLAYER_STATE_RUN;
		}
		else if (_owner->GetRunFlag())
		{
			state = PlayerState::PLAYER_STATE_WALK;
		}
	}
	else if (_owner->GetIsJumping() || _owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	if (CountDownFont::timeOverFlag == true)
	{
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}

	return state;
}

void PlayerObjectStateIdle::Input(PlayerObject* _owner, const InputState& _keyState)
{
	if (_owner->GetIsAvailableInput())
	{
		//Axis�̒l���Ƃ�32700~-32700
		float ALX = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
		float ALY = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);

		//�A�i���O�X�e�B�b�N�̃L�[���͂��擾
		Vector2 Axis = Vector2(0.0f, 0.0f);
		Axis = _keyState.Controller.GetLAxisLeftVec();

		//���ۂɓ�����������������Ă���̂ŕ␳
		Vector3 axis = Vector3(Axis.y * -1.0f, Axis.x * -1.0f, 0.0f);

		//���͂����邩
		if (Math::Abs(axis.x) > 0.0f || Math::Abs(axis.y) > 0.0f)
		{
			_owner->SetInputFlag(true);
			//�A�i���O�X�e�B�b�N�̓��͏�Ԃŕ��������肩�𔻒�
			if (ALX >= 28000.0f || ALX <= -28000.0f || ALY >= 28000.0f || ALY <= -28000.0f)
			{
				_owner->SetRunFlag(true);
			}
			else
			{
				_owner->SetRunFlag(false);
			}
		}
		else
		{
			_owner->SetInputFlag(false);
		}

		if (_owner->GetOnGround() == true && _owner->GetJumpFlag() == false)
		{
			if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
				_owner->GetSwitchJumpFlag() == true)
			{
				//jumpFlag = true;
				_owner->SetJumpFlag(true);
				//isJumping = true;
				_owner->SetIsJumping(true);
			}
		}
	}

}

void PlayerObjectStateIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_IDLE));
	state = PlayerState::PLAYER_STATE_IDLE;
}