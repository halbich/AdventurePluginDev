#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AdventurePluginGameContext.generated.h"

class UInventoryController;
class IInventoryPresenterInterface;
class UDialogController;
class IDialogPresenterInterface;
class UItemManager;
class UAdventureCharacterManager;
class UAdventurePluginSaveGame;

/**
 * A class that provides access to all Adventure Plugin data and functionality.
 * Almost all of the methods in the plugin require the context. 
 * The purpose of this class is similar to that of the GameInstance, but is not that to allow flexibility.
 * For example it might be possible to have one game context set up for displaying normal dialogs and one for background conversations.
 */
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginGameContext : public UObject
{
	GENERATED_BODY()

public:

	/**
	* The object reponsible for inventory-related things that do not involve displaying anything to the player.
	* Among other things, using this class you can access an inventory, add items and remove them.
	* This class also provides some event dispatchers to notify listeners, about for example new inventory items.
	*/
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Inventory")
	UInventoryController* InventoryController;

	/**
	* The object responsible for showing the inventory to the player and hiding it.
	*/
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Inventory")
	TScriptInterface< IInventoryPresenterInterface> InventoryPresenter;

	/**
	* The object used to start a dialog and go through the dialog graph.
	* Does not actually show anything, it binds itself to the DialogController.
	*/
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Dialog")
	UDialogController* DialogController;

	/**
	* Provides dialog interaction for the DialogController. Is able to show a dialog line, play sounds, animations.
	* It can also notify the DialogController about the player skipping a dialog, choosing a dialog option and animation finishing.
	*/
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Dialog")
	TScriptInterface< IDialogPresenterInterface> DialogPresenter;

	/**
	* The current save game. All classes that want to be serialized should store their data here and should load their data from here.
	*/
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Game Context")
	UAdventurePluginSaveGame* SaveGame;

	/**
	* The object that manages instances of UInventoryItem classes.
	* For each class contains a single instance of that item.
	*/
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Inventory")
	UItemManager* ItemManager;

	/**
	* The object that manages instances of UAdventureCharacter classes.
	* For each class contains a single instance of that character.
	*/
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Adventure Plugin|Character")
	UAdventureCharacterManager* AdventureCharacterManager;

	/**
	* Returns true if the game context and all of its direct subclasses are valid and not null.
	* If not, it will log an error, which will include caller as a description of where this problem happened.
	* @param GameContext Context to verify.
	* @param Caller Specifies from where this method was called so the log can tell us where the invalid context appeared.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin")
	static bool IsGameContextValid(const UAdventurePluginGameContext* GameContext, const FString& Caller);
};
