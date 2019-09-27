#pragma once

#include "CoreMinimal.h"
#include "AdventurePluginRuntime.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sound/DialogueWave.h"
#include "Sound/SoundBase.h"
#include "DialogueWaveHelpersBlueprintLibrary.generated.h"

/**
* Blueprint library for all global Adventure Plugin methods that do not belong to any other category.
*/
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UDialogueWaveHelpersBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Starts a dialog from an entry point.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param EntryPoint Specifies the place from which the dialog should begin, both the dialog graph and the entry point.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Dialog", meta = (WorldContext = WorldObjectContexte))
	static USoundBase* GetDialogueWaveSound(UDialogueWave* DialogueWave, UObject* WorldObjectContext)
	{
		if (DialogueWave == nullptr || DialogueWave->ContextMappings.Num() != 1)
		{
			return nullptr;
		}
		return DialogueWave->GetWaveFromContext(DialogueWave->ContextMappings[0]);
	}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Dialog", meta = (WorldContext = WorldObjectContexte))
	static FText GetDialogueWaveSubtitle(UDialogueWave* DialogueWave, UObject* WorldObjectContext)
	{
		if (DialogueWave == nullptr || DialogueWave->ContextMappings.Num() != 1)
		{
			return FText();
		}
		return DialogueWave->GetLocalizedSubtitle(DialogueWave->ContextMappings[0]);
	}

private:
};
