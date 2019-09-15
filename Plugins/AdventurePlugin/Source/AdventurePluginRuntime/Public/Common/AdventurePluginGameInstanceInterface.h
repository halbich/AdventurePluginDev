#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AdventurePluginGameInstanceInterface.generated.h"

class UAdventurePluginGameContext;

/**
* @see IAdventurePluginGameInstanceInterface
*/
UINTERFACE(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginGameInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
* Game Instance should implement this class to provide the plugin with a way to get a game context easily.
*/
class IAdventurePluginGameInstanceInterface
{
	GENERATED_BODY()

public:
	/**
	* Retrieves the default game context used by this game instance. Contains instances of classes defined in game config.
	* @see UAdventurePluginConfig
	* @return The default game context.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Adventure Plugin|Dialog")
		UAdventurePluginGameContext* GetDefaultGameContext();
};
