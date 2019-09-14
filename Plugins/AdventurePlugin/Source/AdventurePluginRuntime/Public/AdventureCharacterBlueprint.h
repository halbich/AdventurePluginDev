#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Combinations/CombinableObjectBlueprint.h"
#include "AdventureCharacterBlueprint.generated.h"

/**
* Blueprint class for adventure character.
* This class exists so combinations with character work correctly and to give custom icons to character blueprints.
* @see UAdventureCharacterFactory
*/
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventureCharacterBlueprint : public UCombinableObjectBlueprint, public IIconThumbnailInterface
{
	GENERATED_BODY()

public:

	virtual UTexture2D* GetIcon() const override;
};