#include "PreCompile.h"
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>

#include "PlayerToolsAnimation.h"
#include "ContentsEnum.h"

APlayerToolsAnimation::APlayerToolsAnimation()
{
    {
        SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
        SpriteRenderer->SetComponentScale({ 220, 440 });
        SpriteRenderer->SetOrder(ERenderOrder::TOOLSANIMATION);
        SpriteRenderer->SetPivot({ 0.0, 7.0f });

        SpriteRenderer->SetSprite("Farmer_Right_Axe.png");
        SpriteRenderer->SetSprite("Farmer_Left_Axe.png");
    }

    // Axe
    {
        SpriteRenderer->CreateAnimation("Axe_Right", "Farmer_Right_Axe.png", { 93, 80, 81, 83 }, { 0.05f, 0.05f, 0.05f , 0.2f }, false);
        SpriteRenderer->CreateAnimation("Axe_Left", "Farmer_Left_Axe.png", { 93, 80, 81, 83 }, { 0.05f, 0.05f, 0.05f , 0.2f }, false);
        SpriteRenderer->CreateAnimation("Axe_Front", "Farmer_Right_Axe.png", { 47,48,90,91,0 }, { 0.05f , 0.05f, 0.05f , 0.25f, 0.05f }, false);
        SpriteRenderer->CreateAnimation("Axe_Back", "Farmer_Right_Axe.png", { 77,76,43,11 }, { 0.1f , 0.1f,  0.2f, 0.05f }, false);
    }
    {
        SpriteRenderer->CreateAnimation("Hoe_Right", "Farmer_Right_Hoe.png", { 93, 80, 81, 83 }, { 0.05f, 0.05f, 0.05f , 0.2f }, false);
        SpriteRenderer->CreateAnimation("Hoe_Left", "Farmer_Left_Hoe.png", { 93, 80, 81, 83 }, { 0.05f, 0.05f, 0.05f , 0.2f }, false);
        SpriteRenderer->CreateAnimation("Hoe_Front", "Farmer_Right_Hoe.png", { 47,48,90,91,0 }, { 0.05f , 0.05f, 0.05f , 0.25f, 0.05f }, false);
        SpriteRenderer->CreateAnimation("Hoe_Back", "Farmer_Right_Hoe.png", { 77,76,43,11 }, { 0.1f , 0.1f,  0.2f, 0.05f }, false);
    }
}

APlayerToolsAnimation::~APlayerToolsAnimation()
{
}


void APlayerToolsAnimation::ChangeAnimation(std::string_view _AnimationName, bool _Force /*= false*/)
{
    SpriteRenderer->ChangeAnimation(_AnimationName, _Force);

}
