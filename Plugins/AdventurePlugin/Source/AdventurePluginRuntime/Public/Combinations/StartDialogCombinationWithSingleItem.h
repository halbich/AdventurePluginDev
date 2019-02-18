#pragma once

#include "Core.h"
#include "Delegate.h"
#include "CombinationInterface.h"
#include "DialogGraphEntryPoint.h"
#include "AdventurePluginRuntime.h"
#include "AdventurePluginGameContext.h"
#include "AdventurePluginBlueprintLibrary.h"
#include "CombinationWithSingleItemBase.h"
#include "StartDialogCombinationWithSingleItem.generated.h"

class UAdventurePluginGameContext;

/**
* Represents a combination with a target object and with a specific constant name.
* When the combination is triggered a dialogue will be started.
*/
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UStartDialogCombinationWithSingleItem : public UCombinationWithSingleItemBase
{
	GENERATED_BODY()

public:
	/**
	* The class specifying the dialog to be started.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FDialogGraphEntryPoint DialogToStart;
	/**
	* Retrieves the debug name of this combination to be shown in editor. Contains identification of this class and Name. @see UStartDialogCombinationWithSingleItem#Name
	* @return The debug combination name.
	*/
	virtual FText GetDebugName_Implementation() override
	{
		return FText::Format(NSLOCTEXT("AP", "StartDialogCombinationWithSingleItemDebugName", "StartDialog combination with single item:{0}"), Name);
	}
	/**
	* Executes the action this combination represents.
	* Removes both combined items from the inventory and adds an instance of ResultItemClass to the inventory. See UStartDialogCombinationWithSingleItem#ResultItemClass.
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
			LOG_Error(NSLOCTEXT("AP", "UStartDialogCombinationWithSingleItem_ExecuteDialogInvalid", "UStartDialogCombinationWithSingleItem:Execute: The dialog is invalid"));
			return;
		}
		UAdventurePluginBlueprintLibrary::ShowDialogFromEntryPoint(GameContext, DialogToStart);
	}
};