#pragma once
#include "ParticleEffectBase.h"
class LandingEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    */
    LandingEffect(const Vector3& _pos, const Vector3& _velocity);
    ~LandingEffect()override;
    void UpdateGameObject(float _deltaTime)override;

private:
    ParticleState particleState;
    GameObject* owner;
    float mScale;
    float mAlpha;
    bool ChackOnFlag;
    bool tmpChackOnFlag;
    bool generateFlag;

};

