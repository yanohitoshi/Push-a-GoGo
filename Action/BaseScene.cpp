#include "BaseScene.h"
#include "Renderer.h"
#include "PlayerObject.h"

void BaseScene::StartSceneLightUpProcess()
{
	// ライトの数値を明るくする
	light += ChangeLightSpeed;
	// レンダラーに値をセット
	RENDERER->SetAmbientLight(light);

	// ライトの数値が一定以上になったら
	if (light.x >= MaxLight)
	{
		// シーン開始フラグをfalseに変更
		startScene = false;
		// 最終の値をセット
		RENDERER->SetAmbientLight(light);
	}
}

void BaseScene::SceneClearCountProcess(PlayerObject* _playerObject)
{
	if (_playerObject->GetClearFlag() == true)
	{
		++clearCount;
		light -= ChangeLightSpeed;
		RENDERER->SetAmbientLight(light);
	}
}

void BaseScene::ContinueSelectProcess(const InputState& state)
{
	// ライト固定
	light = TimeoversLight;
	RENDERER->SetAmbientLight(light);

	// Aボタンが押されたら
	if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed)
	{
		lightDownFlag = false;
		// コンテニュー遷移状態にする
		isContinueFlag = true;
	}

	// Bボタンが押されたら
	if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed)
	{
		lightDownFlag = false;
		// ゲームオーバー状態にする
		endFlag = true;
	}
}

void BaseScene::LightTransitionAtContinue()
{
	// 遷移カウント開始
	++changeCount;

	// コンティニュー選択後の
	if (changeCount >= ChoiceContinueCount)
	{
		// コンテニューだったら明るくゲームオーバーだったら暗くする
		if (isContinueFlag == true)
		{
			// ライトアップ
			light += ChangeLightSpeed;
			RENDERER->SetAmbientLight(light);
		}
		else if (endFlag == true)
		{
			// ライトダウン
			light -= ChangeLightSpeed;
			RENDERER->SetAmbientLight(light);
		}

	}
}

void BaseScene::SceneStateChangeAtContinue(SceneState _nowScene)
{
	// コンテニューだったらステージ最初へゲームオーバーだったらリザルト画面へ
	if (isContinueFlag == true)
	{
		// コンティニューされたらそのステージから始めるために
		// コンティニューされたかどうか判定するためのフラグを切り替える
		Game::SetContinueFlag(true);
		state = _nowScene;
	}
	else if (endFlag == true)
	{
		state = SceneState::RESULT_SCENE;
	}
}
