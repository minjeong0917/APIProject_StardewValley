#include "PreCompile.h"

#include "Text.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"
AText::AText()
{
	TextSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	TextSpriteRenderer->SetCameraEffect(false);
	TextSpriteRenderer->SetOrder(ERenderOrder::UIFont);
	//
}

AText::~AText()
{
}

