#pragma once

#include "Core.h"
#include "Classes/Engine/DataAsset.h"
#include "Classes/Engine/Texture2D.h"
#include "AdventureCharacter.generated.h"

UCLASS(BlueprintType)
class ADVENTUREPLUGINRUNTIME_API UAdventureCharacter : public UDataAsset
{
	//GENERATED_USTRUCT_BODY()
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;
};