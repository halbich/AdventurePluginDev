#pragma once

#include "CoreMinimal.h"
#include "AdventureCharacter.h"
#include "IconThumbnailInterface.h"
#include "ThumbnailRendering/TextureThumbnailRenderer.h"
#include "IconThumbnailRenderer.generated.h"

class FCanvas;
class FRenderTarget;

/**
* If an object implements IIconThumbnailInterface, this renderer will replace
* its asset editor icon with the one returned by IIconThumbnailInterface#GetIcon.
*/
UCLASS()
class ADVENTUREPLUGINEDITOR_API UIconThumbnailRenderer : public UTextureThumbnailRenderer
{
	GENERATED_BODY()

	virtual void GetThumbnailSize(UObject* Object, float Zoom, uint32& OutWidth, uint32& OutHeight) const override
	{
		IIconThumbnailInterface* Character = Cast<IIconThumbnailInterface>(Object);
		UTextureThumbnailRenderer::GetThumbnailSize(Character ? Character->GetIcon() : nullptr, Zoom, OutWidth, OutHeight);
	}

	virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas) override
	{
		IIconThumbnailInterface* Character = Cast<IIconThumbnailInterface>(Object);
		UTextureThumbnailRenderer::Draw(Character ? Character->GetIcon() : nullptr, X, Y, Width, Height, nullptr, Canvas);
	}
};