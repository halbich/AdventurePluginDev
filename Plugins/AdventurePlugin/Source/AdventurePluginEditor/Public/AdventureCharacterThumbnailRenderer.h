#pragma once

#include "Core.h"
#include "AdventureCharacter.h"
#include "Classes/ThumbnailRendering/TextureThumbnailRenderer.h"
#include "AdventureCharacterThumbnailRenderer.generated.h"

class FCanvas;
class FRenderTarget;

UCLASS()
class ADVENTUREPLUGINEDITOR_API UAdventureCharacterThumbnailRenderer : public UTextureThumbnailRenderer
{
	//GENERATED_UCLASS_BODY()
	GENERATED_BODY()

	// Begin UThumbnailRenderer Object

	virtual void GetThumbnailSize(UObject* Object, float Zoom, uint32& OutWidth, uint32& OutHeight) const override
	{
		UAdventureCharacter* Character = Cast<UAdventureCharacter>(Object);
		UTextureThumbnailRenderer::GetThumbnailSize(Character ? Character->Icon : nullptr, Zoom, OutWidth, OutHeight);
	}


	virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas) override
	{
		UAdventureCharacter* Character = Cast<UAdventureCharacter>(Object);
		UTextureThumbnailRenderer::Draw(Character ? Character->Icon : nullptr, X, Y, Width, Height, nullptr, Canvas);
	}

	// End UThumbnailRenderer Object
};