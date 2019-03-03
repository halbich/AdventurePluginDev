#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPresenterInterface.h"
#include "InventoryPresenterWidget.generated.h"

/**
 * Base class for inventory presenter widgets. It has no behavior by default and must be overriden in blueprints.
 * @see IInventoryPresenterInterface
 */
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UInventoryPresenterWidget : public UUserWidget, public IInventoryPresenterInterface
{
	GENERATED_BODY()

public:

	/**
	* Displays the specified inventory to the player.
	* @param Inventory The inventory to present.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	void ShowInventory(UInventory* Inventory, UAdventurePluginGameContext* GameContext);

	/**
	* Hides the currently shown inventory
	* @param Inventory The inventory to hide.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	*/
	void HideInventory(UInventory* Inventory, UAdventurePluginGameContext* GameContext);
};
