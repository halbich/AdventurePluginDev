#pragma once

#include "Core.h"
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Engine/Blueprint.h"
#include "CombinableObjectBlueprint.h"
#include "AdventureCharacter.h"
#include "AdventureCharacterBlueprint.generated.h"

class UAdventurePluginGameContext;

#pragma optimize("", off)
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventureCharacterBlueprint : public UCombinableObjectBlueprint, public IIconThumbnailInterface
{
	GENERATED_BODY()

public:

	virtual UTexture2D* GetIcon() const override;

	UFUNCTION(BlueprintCallable)
		UAdventureCharacter* GetItemInstance(UAdventurePluginGameContext* GameContext);
};
#pragma optimize("", on)