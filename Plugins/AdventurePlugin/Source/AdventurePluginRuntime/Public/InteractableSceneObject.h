#pragma once

#include "CoreMinimal.h"
#include "UObject/TextProperty.h" 
#include "Combinations/CombinableObject.h"
#include "Dialog/Structs/DialogGraphEntryPoint.h"
#include "Inventory/Structs/UseActionType.h"
#include "InteractableSceneObject.generated.h"

/**
* Represents a single object that could be rendered on the scene.
* This class should specify all data and behavior of an item that does not depend on its placement in the scene. Its name, actions, etc.
* It is expected that the designer will create a subclass of this class for each object and then also create a separate blueprint to handle the object's behavior on the scene.
* To allow combinations to work correctly, subclasses of this class should be done only in blueprints.
*/
UCLASS(Abstract, BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UInteractableSceneObject : public UCombinableObject
{
	GENERATED_BODY()

public:
	/**
	* The name of this item that should be displayed to the player.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interactable object")
	FText Name;
	/**
	* The dialog that should be started when this item is examined.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Examination")
	FDialogGraphEntryPoint ExamineDialog;
	/**
	* Tags assigned to this object, e.g. weapon, critical, red herring etc.
	* No inherent function unless designers make it so.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interactable object")
	FGameplayTagContainer ObjectTags;
	/**
	* If true, it is possible to examine this item. This is a value returned by IsExaminable() if not overriden.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Examination")
	bool bDefaultIsExaminable = true;
	/**
	* Checks whether this item can be examined right now.
	* Unless overriden this method returns UInteractableSceneObject#bDefaultIsExaminable.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if the item can be examined right now, otherwise false.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Interactable Object", meta = (AdvancedDisplay = GameContextOverride))
	bool IsExaminable(UAdventurePluginGameContext* GameContextOverride);
	/**
	* If true, this item has a use action that can be called, e.g. reading a map. This is a value returned by IsUsable() if not overriden.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Usage")
	bool bDefaultIsUsable = false;
	/**
	* Checks whether this item can be used right now, i.e. it is possible to call Use() method.
	* Unless overriden this method returns UInteractableSceneObject#bDefaultIsUsable.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return True if the item can be used right now, otherwise false.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Interactable Object", meta = (AdvancedDisplay = GameContextOverride))
	bool IsUsable(UAdventurePluginGameContext* GameContextOverride);
	/**
	* The name of the use action that can be displayed to the user, e.g. "Read a map".
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Usage")
	FText UseActionName;

	/**
	* The type of the use action, e.g. Use/Talk/Combine etc.
	* @see UAdventurePluginConfig#UseActionTypes
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Usage")
	FUseActionType UseActionType;
	/**
	* Executes examine action on the item. Can be overriden, default behavior starts the examine dialog.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Interactable Object", meta = (AdvancedDisplay = GameContextOverride))
	void Examine(UAdventurePluginGameContext* GameContextOverride);

	/**
	* Executes the use action of the object. Can be overriden, does nothing by default.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Interactable Object", meta = (AdvancedDisplay = GameContextOverride))
	void Use(UAdventurePluginGameContext* GameContextOverride);
	/**
	* Returns true if this item was already picked up.
	* Default behavior checks the item state using GetItemState() to see if the item was already picked up.
	* Can be overriden if the item uses custom states.
	* @return True if the item was already picked up.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Interactable Object", meta = (AdvancedDisplay = GameContextOverride))
	bool WasExamined(UAdventurePluginGameContext* GameContextOverride);

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Interactable Object", meta = (AdvancedDisplay = GameContextOverride))
	void SetWasExamined(UAdventurePluginGameContext* GameContextOverride, bool bWasExamined);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Adventure Plugin|Interactable Object", meta = (AdvancedDisplay = GameContextOverride))
	FName GetWasExaminedPropertyName();
};