#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AdventurePluginGameContext.h"
#include "Dialog/Controller/DialogController.h"
#include "Dialog/Presenter/DialogPresenterWidget.h"
#include "Inventory/Controller/InventoryController.h"
#include "Inventory/Presenter/InventoryPresenterWidget.h"
#include "SaveGame/AdventurePluginSaveGame.h"
#include "Combinations/CombinableObjectManager.h"
#include "Combinations/CombinableObjectManager.h"
#include "Common/AdventurePluginGameInstanceInterface.h"
#include "Engine/GameInstance.h"
#include "AdventurePluginGameInstance.generated.h"

/**
 * A game instance that can be used for projects using our plugin.
 * It contains a single game context that contains instances of the classes specified in the project configuration.
 */
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginGameInstance : public UGameInstance, public IAdventurePluginGameInstanceInterface
{
	GENERATED_BODY()

public:

	/**
	* The game context used by this game instance.
	*/
	UPROPERTY(Transient, BlueprintReadWrite, Category="GameContext")
	UAdventurePluginGameContext* CurrentGameContext;

	virtual void Init() override;

	virtual void Shutdown() override;

	/**
	* Retrieves the default game context used by this game instance. Contains instances of classes defined in game config.
	* @see UAdventurePluginConfig
	* @return The default game context.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Adventure Plugin")
	UAdventurePluginGameContext* GetDefaultGameContext();
	virtual UAdventurePluginGameContext* GetDefaultGameContext_Implementation() override;

private:

	/**
	* Initializes the game context based on the project configuration.
	*/
	void InitCurrentGameContext();

	/**
	 * Instantiate an instance of a specified class. Used to instantiate the classes specified in the config.
	 * @param ClassToInstantiate The class that should be instantiated.
	 * @return The instance of that class, or nullptr if the class could not be instantiated.
	 */
	template<class T>
	T* InstantiateClass(TSoftClassPtr<T> ClassToInstantiate);
};

template<class T>
T* UAdventurePluginGameInstance::InstantiateClass(TSoftClassPtr<T> ClassToInstantiate)
{
	UClass* ActualClass = ClassToInstantiate.IsValid()
		? ClassToInstantiate.Get()				// we have C++ class
		: ClassToInstantiate.LoadSynchronous();	// we have Blueprint class
	T* ToReturn = nullptr;
	if (!IsValid(ActualClass))
	{
		LOG_Error(FText::Format(NSLOCTEXT("AdventurePlugin", "InstantiateClass_ClassNotValid", "Cannot instantiate class. Class not valid: {0}"), FText::FromString(ClassToInstantiate.GetAssetName())));
		return nullptr;
	}
	if (ActualClass->IsChildOf(UUserWidget::StaticClass()))
	{
		ToReturn = Cast<T>(CreateWidget<UUserWidget>(this, ActualClass));
		if (!IsValid(ToReturn))
		{
			LOG_Error(FText::Format(NSLOCTEXT("AdventurePlugin", "InstantiateClass_WidgetNotInstantiated", "Failed to instantiate widget class: {0}"), FText::FromString(ClassToInstantiate.GetAssetName())));
		}
	}
	else
	{
		ToReturn = NewObject<T>(this, ActualClass);
		if (!IsValid(ToReturn))
		{
			LOG_Error(FText::Format(NSLOCTEXT("AdventurePlugin", "InstantiateClass_ObjectNotInstantiated", "Failed to instantiate UObject class: {0}"), FText::FromString(ClassToInstantiate.GetAssetName())));
		}
	}
	return ToReturn;
}