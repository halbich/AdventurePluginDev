#include "SaveGame/AdventurePluginSaveGame.h"
#include "Common/AdventurePluginConfig.h"

UAdventurePluginSaveGame::UAdventurePluginSaveGame()
{
	SaveSlotName = TEXT("DefaultSaveSlot");
	SaveUserIndex = 0;
}

bool UAdventurePluginSaveGame::GetBoolOrDefault(FName Name, bool bDefaultValue)
{
	bool* Result = StorageBoolean.Find(Name);
	if (Result == nullptr)
	{
		StorageBoolean.Add(Name, bDefaultValue);
		return bDefaultValue;
	}
	else
	{
		return *Result;
	}

}

void UAdventurePluginSaveGame::SetBool(FName Name, bool bValue)
{
	// if key exist, value will be replaced
	StorageBoolean.Add(Name, bValue);
}


int32 UAdventurePluginSaveGame::GetIntOrDefault(FName Name, int32 DefaultValue)
{
	int32* Result = StorageInt.Find(Name);
	if (Result == nullptr)
	{
		StorageInt.Add(Name, DefaultValue);
		return DefaultValue;
	}
	else
		return *Result;
}

void UAdventurePluginSaveGame::SetInt(FName Name, int32 Value)
{
	// if key exist, value will be replaced
	StorageInt.Add(Name, Value);
}


FString UAdventurePluginSaveGame::GetStringOrDefault(FName Name, FString DefaultValue)
{
	FString* Result = StorageString.Find(Name);
	if (Result == nullptr)
	{
		StorageString.Add(Name, DefaultValue);
		return DefaultValue;
	}
	else
	{
		return *Result;
	}
}

void UAdventurePluginSaveGame::SetString(FName Name, FString Value)
{
	// if key exist, value will be replaced
	StorageString.Add(Name, Value);
}

EInventoryItemState UAdventurePluginSaveGame::GetItemStateOrDefault(TSubclassOf<UInventoryItem> Item, EInventoryItemState DefaultValue)
{
	EInventoryItemState* Result = StorageItemStates.Find(Item);
	if (Result == nullptr)
	{
		StorageItemStates.Add(Item, DefaultValue);
		return DefaultValue;
	}
	else
	{
		return *Result;
	}
}

void UAdventurePluginSaveGame::SetItemState(TSubclassOf<UInventoryItem> Item, EInventoryItemState Value)
{
	StorageItemStates.Add(Item, Value);
}

UAdventurePluginSaveGame* UAdventurePluginSaveGame::CreateSave(FString SlotName, int32 UserIndex)
{
	UAdventurePluginConfig* Settings = GetMutableDefault<UAdventurePluginConfig>();
	TSoftClassPtr<UAdventurePluginSaveGame> ClassToInstantiate = Settings->DefaultSaveGame;
	UClass* ActualSaveClass = ClassToInstantiate.IsValid()
		? ClassToInstantiate.Get()				// we have C++ class
		: ClassToInstantiate.LoadSynchronous();	// we have Blueprint class

	if (!IsValid(ActualSaveClass))
	{
		LOG_Error(FText::Format(NSLOCTEXT("AdventurePlugin", "CreateSave_ClassNotValid", "Cannot instantiate class. Class not valid: {0}"), FText::FromString(ClassToInstantiate.GetAssetName())));
		return nullptr;
	}

	UAdventurePluginSaveGame* SaveGameInstance = Cast<UAdventurePluginSaveGame>(UGameplayStatics::CreateSaveGameObject(ActualSaveClass));
	SaveGameInstance->SaveSlotName = SlotName;
	SaveGameInstance->SaveUserIndex = UserIndex;
	return SaveGameInstance;
}

bool UAdventurePluginSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, this->SaveSlotName, this->SaveUserIndex);
}
