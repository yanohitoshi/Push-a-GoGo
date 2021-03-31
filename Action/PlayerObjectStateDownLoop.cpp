#include "PlayerObjectStateDownLoop.h"
#include "SkeletalMeshComponent.h"
PlayerObjectStateDownLoop::PlayerObjectStateDownLoop()
{
}

PlayerObjectStateDownLoop::~PlayerObjectStateDownLoop()
{
}

PlayerState PlayerObjectStateDownLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	return state;
}

void PlayerObjectStateDownLoop::Input(PlayerObject* _owner, const InputState& _keyState)
{

	if (CountDownFont::timeOverFlag == true)
	{
		isAvailableInput = false;
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		downFlag = true;

		if (downUpFlag == false && downOverFlag == false)
		{
			if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
				_keyState.Keyboard.GetKeyDownValue(SDL_SCANCODE_C) == true)
			{
				downUpFlag = true;
			}
			else if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
				_keyState.Keyboard.GetKeyDownValue(SDL_SCANCODE_Z) == true)
			{
				downOverFlag = true;
			}
		}
	}

}

void PlayerObjectStateDownLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWN_LOOP));
	state = PlayerState::PLAYER_STATE_DOWN_LOOP;
}