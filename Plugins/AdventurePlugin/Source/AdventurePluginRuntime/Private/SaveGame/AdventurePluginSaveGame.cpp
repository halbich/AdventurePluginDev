// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginSaveGame.h"

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

UAdventurePluginSaveGame* UAdventurePluginSaveGame::CreateSave(FString& SlotName, int32 UserIndex)
{
	UAdventurePluginSaveGame* SaveGameInstance = Cast<UAdventurePluginSaveGame>(UGameplayStatics::CreateSaveGameObject(UAdventurePluginSaveGame::StaticClass()));
	SaveGameInstance->SaveSlotName = SlotName;
	SaveGameInstance->SaveUserIndex = UserIndex;
	return SaveGameInstance;
}

bool UAdventurePluginSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, this->SaveSlotName, this->SaveUserIndex);
}
