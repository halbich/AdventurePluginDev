// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginSaveGame.h"

UAdventurePluginSaveGame::UAdventurePluginSaveGame()
{
	SaveSlotName = TEXT("DefaultSaveSlot");
	SaveUserIndex = 0;
}



bool UAdventurePluginSaveGame::GetBool(FName name)
{
	auto res = storageBoolean.Find(name);

	// TODO better key handling
	check(res && "Key not found in boolean storage");

	return *res;
}

bool UAdventurePluginSaveGame::GetBoolOrDefault(FName name)
{
	return storageBoolean.FindOrAdd(name);
}

void UAdventurePluginSaveGame::SetBool(FName name, bool value)
{
	// if key exist, value will be replaced
	storageBoolean.Add(name, value);
}



int UAdventurePluginSaveGame::GetInt(FName name)
{
	auto res = storageInt.Find(name);

	// TODO better key handling
	check(res && "Key not found in int storage");

	return *res;
}

int UAdventurePluginSaveGame::GetIntOrDefault(FName name)
{
	return storageInt.FindOrAdd(name);
}

void UAdventurePluginSaveGame::SetInt(FName name, int value)
{
	// if key exist, value will be replaced
	storageInt.Add(name, value);
}



FString UAdventurePluginSaveGame::GetString(FName name)
{
	auto res = storageString.Find(name);

	// TODO better key handling
	check(res && "Key not found in string storage");

	return *res;
}

FString UAdventurePluginSaveGame::GetStringOrDefault(FName name)
{
	return storageString.FindOrAdd(name);
}

void UAdventurePluginSaveGame::SetString(FName name, FString value)
{
	// if key exist, value will be replaced
	storageString.Add(name, value);
}



UAdventurePluginSaveGame* UAdventurePluginSaveGame::CreateSave(FString& slotName, int userIndex)
{
	auto instance = Cast<UAdventurePluginSaveGame>(UGameplayStatics::CreateSaveGameObject(UAdventurePluginSaveGame::StaticClass()));
	instance->SaveSlotName = slotName;
	instance->SaveUserIndex = userIndex;
	return instance;
}

bool UAdventurePluginSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, this->SaveSlotName, this->SaveUserIndex);
}