// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "AdventurePluginSaveGame.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginSaveGame : public USaveGame
{
	GENERATED_BODY()

		UAdventurePluginSaveGame();


	UPROPERTY()
		TMap<FName, bool> storageBoolean;

	UPROPERTY()
		TMap<FName, int> storageInt;

	UPROPERTY()
		TMap<FName, FString> storageString;

public:

	UPROPERTY(VisibleAnywhere, Category = Basic, meta = (DisplayName = "Slot Name"))
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic, meta = (DisplayName="User Index"))
		uint32 SaveUserIndex;


	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		bool GetBool(FName name);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		bool GetBoolOrDefault(FName name);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		void SetBool(FName name, bool value);


	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		int GetInt(FName name);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		int GetIntOrDefault(FName name);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		void SetInt(FName name, int value);


	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		FString GetString(FName name);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		FString GetStringOrDefault(FName name);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		void SetString(FName name, FString value);


	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		static UAdventurePluginSaveGame* CreateSave(FString& slotName , int userIndex );

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		bool Save();
};
