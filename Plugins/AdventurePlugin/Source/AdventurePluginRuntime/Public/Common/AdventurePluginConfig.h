#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AdventurePluginConfig.generated.h"

class UDialogPresenterWidget;
class UDialogController;
class UInventoryPresenterWidget;
class UInventoryController;
class UCombinableObjectManager;
class UAdventurePluginSaveGame;

/**
 * Contains the configuration for the Adventure Plugin.
 */
UCLASS(Config = AdventurePlugin, DefaultConfig)
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginConfig : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Class specifying the save game to be used in the default GameContext. @see UAdventurePluginGameContext
	*/
	UPROPERTY(Config, EditAnywhere, Category=SaveGame, DisplayName="Default Save Game")
	TSoftClassPtr<UAdventurePluginSaveGame> DefaultSaveGame;

	/**
	* Class specifying the dialog presenter widget to be used in the default GameContext. @see UAdventurePluginGameContext
	*/
	UPROPERTY(Config, EditAnywhere, Category = Dialog, DisplayName = "Default Presenter")
	TSoftClassPtr<UDialogPresenterWidget> DefaultDialogPresenterWidget;

	/**
	* Class specifying the dialog controller to be used in the default GameContext. @see UAdventurePluginGameContext
	*/
	UPROPERTY(Config, EditAnywhere, Category = Dialog, DisplayName = "Default Controller")
	TSoftClassPtr<UDialogController> DefaultDialogController;

	/**
	* Class specifying the inventory presenter widget to be used in the default GameContext. @see UAdventurePluginGameContext
	*/
	UPROPERTY(Config, EditAnywhere, Category = Inventory, DisplayName = "Default Presenter")
	TSoftClassPtr<UInventoryPresenterWidget> DefaultInventoryPresenterWidget;

	/**
	* Class specifying the inventory controller to be used in the default GameContext. @see UAdventurePluginGameContext
	*/
	UPROPERTY(Config, EditAnywhere, Category = Inventory, DisplayName = "Default Controller")
	TSoftClassPtr<UInventoryController> DefaultInventoryController;

	/**
	* Class specifying the character manager to be used in the default GameContext. @see UAdventurePluginGameContext
	*/
	UPROPERTY(Config, EditAnywhere, Category = Dialog, DisplayName = "Default Adventure Character Manager")
	TSoftClassPtr<UCombinableObjectManager> DefaultCombinableObjectManager;

	/**
	* Defines the actions that can be represented by the Use action. 
	* E.g. Using a talking sword might be Talk action, using a mechanism might also be a different action etc.
	* Not doing anything by default, expected use case is determining which icon to use for the use action.
	*/
	UPROPERTY(Config, EditAnywhere, Category = Inventory, DisplayName = "Use Action types")
	TSet<FName> UseActionTypes;

	/**
	* Define the action that should be used for talk action, i.e. which action is initiating a dialog with another character.
	* Must be from the UseActionTypes set.
	*/
	UPROPERTY(Config, EditAnywhere, Category = Inventory, DisplayName = "Talk Action Type")
	TSet<FName> TalkActionType;
};
