#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "UObject/Interface.h"
#include "IconThumbnailInterface.generated.h"

/**
* @see IIconThumbnailInterface
*/
UINTERFACE()
class ADVENTUREPLUGINRUNTIME_API UIconThumbnailInterface : public UInterface
{
	GENERATED_BODY()
};

/**
* Interface that blueprints can implement. Used for custom thumbnails in the editor for these blueprints.
* However, the thumbnail renderers must still be explicitly registered for each class
*/
class ADVENTUREPLUGINRUNTIME_API IIconThumbnailInterface
{
	GENERATED_BODY()

public:

	/**
	* Retrieves the icon representing this object in the asset editor.
	* @return The icon for this object.
	*/
	virtual UTexture2D* GetIcon() const = 0;

};