#pragma once
#include "GameObject.h"

/*
@file SecondStageUI.h
@brief SecondStageのUI表示を行う
*/

class SecondStageUI :
    public GameObject
{
public:
    /*
    @fn コンストラクタ
    @brief  objectの生成を行う
    */
    SecondStageUI();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~SecondStageUI();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

    // タイムオーバー判定用フラグ
    static bool timeOverFlag;

    // カウントスタート判定用フラグ
    static bool countStartFlag;

private:

};

