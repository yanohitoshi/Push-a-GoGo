#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>
#include "InputSystem.h"


// クラスの前方宣言
class FPS;
class GameObject;
class InputSystem;
class GameScene;
class BaseScene;

/*
@enum　シーンの状態を示すタグ
*/
enum SceneState
{
	// タイトルシーン
	TITLE_SCENE,
	// 第一ステージシーン
	FIRST_SATGE_SCENE,
	// 第二ステージシーン
	SECOND_SATGE_SCENE,
	// 第三ステージシーン
	THIRD_SATGE_SCENE,
	// 最終ステージシーン
	FINAL_STAGE_SCENE,
	// リザルトシーン
	RESULT_SCENE
};

/*
@file Game.h
@brief ゲームの進行を行う
*/
class Game
{
public:

	/*
	@fn コンストラクタ
	*/
	Game();
	/*
	@fn デストラクタ
	*/
	~Game();

    /*
    @brief	初期化処理
    @return true : 成功, false : 失敗
    */
	bool Initialize();

	/*
	@brief  終了処理
	*/
	void Termination();

	/*
	@brief  ゲームループ
	*/
	void GameLoop();

	/*
	@brief  ゲームオブジェクトのアップデート処理
	*/
	friend void UpdateGameObjects(float _deltaTime);

	/*
	@brief  ゲームオブジェクトの入力処理
	*/
	friend void ProcessInputs(const InputState& _state);


	// シーン遷移が行われるかどうかフラグ
	static bool isChangeScene;

	static int debug;

private:

	// ゲームプレイ中のシーン
	BaseScene* nowScene;

	// シーンの状態を保存する変数
	SceneState nowSceneState;
	
	/*
	@brief  入力関連の処理
	*/
    void ProcessInput();
	
	/*
	@brief  描画関連の処理
	*/
    void GenerateOutput();

	/*
	@brief  ゲームのアップデート処理
	*/
	void UpdateGame();

	/*
	@brief   ロードしたデータの解放
	*/
	void UnloadData();

	/*
	@fn シーン変更関数
	@brief 前のシーンの解放と次のシーンの生成を行う
	@param _state シーンの状態
	@param _scene 進行中のシーンのポインタ
	*/
	void ChangeScene(SceneState _state,BaseScene* _scene);

	// FPS計測クラス
	FPS* fps;

    // 入力管理クラス
	InputSystem* inputSystem;

	//ゲームを続けるかどうか
    bool isRunning;

	// コンテニューされたかフラグ
	static bool continueFlag;

	// スクリーンの幅
	float screenWidth;

	// スクリーンの高さ
	float screenHeight;

	// フルスクリーンモードを使用するかどうかフラグ
	bool isFullScreen;

	// フルスクリーンモードの時のスクリーンの横幅定数
	const float FullScreenWidth;
	// フルスクリーンモードの時のスクリーンの縦幅定数
	const float FullScreenHeight;
	// ウィンドウモードの時のスクリーンの横幅定数
	const float WindowScreenWidth;
	// ウィンドウモードの時のスクリーンの横幅定数
	const float WindowScreenHeight;

public:

	/*
	@fn continueFlagのsetter関数
	@brief  continueFlagに値をセット
	@param  _continueFlag コンティニューされたかどうか
	*/
	static void SetContinueFlag(bool _continueFlag) { continueFlag = _continueFlag; }

	/*
	@fn continueFlagのgetter関数
	@brief  continueFlagを取得
	@return コンティニューされたかどうかフラグ
	*/
	static bool GetContinueFlag() { return continueFlag; }

};

