#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "Combinations/CombinationInterface.h"
#include "Dialog/Structs/DialogGraphEntryPoint.h"
#include "AdventurePluginRuntime.h"
#include "Common/AdventurePluginGameContext.h"
#include "BlueprintLibrary/AdventurePluginBlueprintLibrary.h"
#include "Combinations/CombinationWithSingleItemBase.h"
#include "StartDialogCombinationWithSingleItem.generated.h"

class UAdventurePluginGameContext;

/**
* Represents a combination with a target object and with a specific constant name.
* When the combination is triggered a dialog will be started.
*/
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UStartDialogCombinationWithSingleItem : public UCombinationWithSingleItemBase
{
	GENERATED_BODY()

public:

	/**
	* The class specifying the dialog to be started.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Adventure Plugin")
	FDialogGraphEntryPoint DialogToStart;

	/**
	* Retrieves the debug name of this combination to be shown in editor. Contains identification of this class and UStartDialogCombinationWithSingleItem#Name.
	* @return The debug combination name.
	*/
	virtual FText GetDebugName_Implementation() override
	{
		return FText::Format(NSLOCTEXT("AdventurePlugin", "StartDialogCombinationWithSingleItemDebugName", "StartDialog combination with single item:{0}"), Name);
	}

	/**
	* Executes the action this combination represents.
	* Starts a dialog from the entry point defined in UStartDialogCombinationWithSingleItem#DialogToStart.
	* @param CombinationSource The source object of the combination.
	* @param CombinationTarget The other object of the combination.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	virtual void Execute_Implementation(UObject* CombinationSource, UObject* CombinationTarget, UAdventurePluginGameContext* GameContext) override
	{
		if (!UAdventurePluginGameContext::IsGameContextValid(GameContext, TEXT("StartDialogCombinationWithSingleItem:Execute")))
		{
			return;
		}
		if (!IsValid(DialogToStart.Dialog))
		{
			LOG_Error(NSLOCTEXT("AdventurePlugin", "StartDialogCombinationWithSingleItem_Execute_DialogInvalid", "StartDialogCombinationWithSingleItem:Execute: The dialog is invalid"));
			return;
		}
		UAdventurePluginBlueprintLibrary::ShowDialogFromEntryPoint(GameContext, DialogToStart, this);
	}
};