#pragma once

#include "Core.h"
#include "Interface.h"
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.generated.h"

UINTERFACE()
class ADVENTUREPLUGINRUNTIME_API UIconThumbnailInterface : public UInterface // TODO I don't know why this class is here. Do we need this class if we don't to blueprint inheritance?
{
	GENERATED_BODY()
};

class ADVENTUREPLUGINRUNTIME_API IIconThumbnailInterface
{
	GENERATED_BODY()

public:

	virtual UTexture2D* GetIcon() const = 0;

};