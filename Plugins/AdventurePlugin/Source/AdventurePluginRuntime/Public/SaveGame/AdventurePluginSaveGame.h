// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "AdventurePluginSaveGame.generated.h"

/**
 *
 */
UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew)
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginSaveGame : public USaveGame
{
	GENERATED_BODY()

		UAdventurePluginSaveGame();


	UPROPERTY(EditDefaultsOnly, Category= "StoredValues")
		TMap<FName, bool> storageBoolean;

	UPROPERTY(EditDefaultsOnly, Category = "StoredValues")
		TMap<FName, int32> storageInt;

	UPROPERTY(EditDefaultsOnly, Category = "StoredValues")
		TMap<FName, FString> storageString;

public:

	UPROPERTY(VisibleAnywhere, Category = Basic, meta = (DisplayName = "Slot Name"))
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic, meta = (DisplayName="User Index"))
		uint32 SaveUserIndex;


	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		bool GetBool(FName name);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		bool GetBoolOrDefault(FName name, bool defaultValue);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		void SetBool(FName name, bool value);


	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		int32 GetInt(FName name);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		int32 GetIntOrDefault(FName name, int32 defaultValue);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		void SetInt(FName name, int32 value);


	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		FString GetString(FName name);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		FString GetStringOrDefault(FName name, FString defaultValue);

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		void SetString(FName name, FString value);


	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		static UAdventurePluginSaveGame* CreateSave(FString& slotName , int32 userIndex );

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin|SaveGame")
		bool Save();
};
