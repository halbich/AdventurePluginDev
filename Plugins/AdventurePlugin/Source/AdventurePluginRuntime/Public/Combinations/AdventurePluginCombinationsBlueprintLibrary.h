#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Combinations/CombinableObject.h"
#include "Inventory/InventoryItem.h"
#include "SimpleCombinationWithSingleItem.h"
#include "GenericCombinationWithSingleItem.h"
#include "StartDialogCombinationWithSingleItem.h"
#include "Inventory/Structs/UseActionType.h"
#include "Dialog/Structs/DialogGraphEntryPoint.h"
#include "AdventurePluginCombinationsBlueprintLibrary.generated.h"

/**
* Blueprint library for all global Adventure Plugin methods concerning combinations.
*/
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginCombinationsBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	* Creates a combination with some specific item that executes an event when triggered. Use when your usecase does not fit any other method for creating combinations.
	* @param TargetObject The other object of this combination. Defined by class so it can be easily used in editor.
	* @param CombinationName The name of this combination that can be displayed to the user.
	* @param CombinationType The type of this combination. No default behavior, expected usecase is to allow cursor to change based on the type of the combination.
	* @param CombinationEvent The event that should be executed when the combination is triggered.
	* @return The object representing this combination.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Combinations")
	static UGenericCombinationWithSingleItem* CreateGenericCombinationWithSingleItem(TSubclassOf<UCombinableObject> TargetObject, FText CombinationName, FUseActionType CombinationType, FCombinationEvent CombinationEvent);
	
	/**
	* Creates a combination with some specific item. When triggered, this combination removes both objects from inventory and adds a new one. 
	* If objects are not in inventory they are ignored, but the ResultItem is still added.
	* @param TargetObject The other object of this combination. Defined by class so it can be easily used in editor.
	* @param ResultItem The item that should be added to the inventory when this combination is triggered.
	* @param CombinationName The name of this combination that can be displayed to the user.
	* @param CombinationType The type of this combination. No default behavior, expected usecase is to allow cursor to change based on the type of the combination.
	* @return The object representing this combination.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Combinations")
	static USimpleCombinationWithSingleItem* CreateSimpleCombinationWithSingleItem(TSubclassOf<UCombinableObject> TargetObject, TSubclassOf<UInventoryItem> ResultItem, FText CombinationName, FUseActionType CombinationType);

	/**
	* Creates a combination with some specific item. When triggered, this combination starts a dialog.
	* @param TargetObject The other object of this combination. Defined by class so it can be easily used in editor.
	* @param DialogToStart The dialog that should be started when this combination is triggered.
	* @param CombinationName The name of this combination that can be displayed to the user.
	* @param CombinationType The type of this combination. No default behavior, expected usecase is to allow cursor to change based on the type of the combination.
	* @return The object representing this combination.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AdventurePlugin|Combinations")
	static UStartDialogCombinationWithSingleItem* CreateDialogCombinationWithSingleItem(TSubclassOf<UCombinableObject> TargetObject, FDialogGraphEntryPoint DialogToStart, FText CombinationName, FUseActionType CombinationType);
};
