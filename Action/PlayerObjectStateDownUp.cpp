#include "PlayerObjectStateDownUp.h"
#include "SkeletalMeshComponent.h"
PlayerObjectStateDownUp::PlayerObjectStateDownUp()
{
}

PlayerObjectStateDownUp::~PlayerObjectStateDownUp()
{
}

PlayerState PlayerObjectStateDownUp::Update(PlayerObject* _owner, float _deltaTime)
{

	// 更新されたstateを返す
    return state;
}

void PlayerObjectStateDownUp::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateDownUp::Enter(PlayerObject* _owner, float _deltaTime)
{
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWN_UP));
	state = PlayerState::PLAYER_STATE_DOWN_UP;
}
