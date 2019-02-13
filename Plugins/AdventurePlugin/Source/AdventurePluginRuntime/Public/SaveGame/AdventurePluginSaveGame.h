// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "InventoryItemState.h"
#include "InventoryItem.h"
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
		TMap<FName, bool> StorageBoolean;

	UPROPERTY(EditDefaultsOnly, Category = "StoredValues")
		TMap<FName, int32> StorageInt;

	UPROPERTY(EditDefaultsOnly, Category = "StoredValues")
		TMap<FName, FString> StorageString;

	UPROPERTY(EditDefaultsOnly, Category = "StoredValues")
		TMap<TSubclassOf<UInventoryItem>, EInventoryItemState> StorageItemStates;

public:

	UPROPERTY(VisibleAnywhere, Category = Basic, meta = (DisplayName = "Slot Name"))
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic, meta = (DisplayName="User Index"))
		uint32 SaveUserIndex;


	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
		bool GetBoolOrDefault(FName Name, bool bDefaultValue);

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
		void SetBool(FName Name, bool bValue);


	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
		int32 GetIntOrDefault(FName Name, int32 DefaultValue);

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
		void SetInt(FName Name, int32 Value);


	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
		FString GetStringOrDefault(FName Name, FString DefaultValue);

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
		void SetString(FName Name, FString Value);


	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
		EInventoryItemState GetItemStateOrDefault(TSubclassOf<UInventoryItem> Item, EInventoryItemState DefaultValue);

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
		void SetItemState(TSubclassOf<UInventoryItem> Item, EInventoryItemState Value);


	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
		static UAdventurePluginSaveGame* CreateSave(FString& SlotName , int32 UserIndex );

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|SaveGame")
		bool Save();
};
