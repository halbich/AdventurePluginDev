// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginSaveGame.h"

#pragma optimize("", off)

UAdventurePluginSaveGame::UAdventurePluginSaveGame()
{
	SaveSlotName = TEXT("DefaultSaveSlot");
	SaveUserIndex = 0;
}



bool UAdventurePluginSaveGame::GetBool(FName Name)
{
	bool* Result = StorageBoolean.Find(Name);

	// TODO better key handling
	check(Result && "Key not found in boolean storage");

	return *Result;
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



int32 UAdventurePluginSaveGame::GetInt(FName Name)
{
	int32* Result = StorageInt.Find(Name);

	// TODO better key handling
	check(Result && "Key not found in int32 storage");

	return *Result;
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



FString UAdventurePluginSaveGame::GetString(FName Name)
{
	FString* Result = StorageString.Find(Name);

	// TODO better key handling
	check(Result && "Key not found in string storage");

	return *Result;
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

#pragma optimize("", on)