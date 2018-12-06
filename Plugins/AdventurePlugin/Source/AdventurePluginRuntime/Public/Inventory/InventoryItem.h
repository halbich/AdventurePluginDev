#pragma once

#include "Core.h"
#include "TextProperty.h" 
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Delegate.h"
#include "ItemCombination.h"
#include "InventoryItem.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UInventoryItem : public UObject, public IIconThumbnailInterface
{
	GENERATED_BODY()

public:

	void Init()
	{
		RefreshCombinations();
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundBase* Comment;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText CommentText;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void AddCombinationObject(UClass* InventoryItem, UItemCombination* ToAdd);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void AddCombination(UClass* InventoryItem, FText CombinationName, FCombinationEvent CombinationEvent);

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
		void InitCombinations();

	virtual UTexture2D* GetIcon() const override
	{
		return Icon;
	}

	void RefreshCombinations();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		UItemCombination* GetCombinationWithItem(UClass* TargetItem)
	{
		auto* toReturn = Combinations.Find(TargetItem);
		return toReturn ? *toReturn : nullptr;
	}

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool TryCombineWith(UInventoryItem* TargetItem, UAdventurePluginGameContext* Context);


protected:

	UPROPERTY(Transient)
		bool IsInitializingCombinations;

	/*Show warning if not currently in the process of initializing combinations.*/
	void CheckIsInitializingCombinations();
private:

	/*Map of all combinations, key is InventoryItem object type, value is the combination that should be done.*/
	UPROPERTY(Transient)
		TMap<UClass*, UItemCombination*> Combinations;

	bool TryCombineWithInternal(UInventoryItem* TargetItem, UAdventurePluginGameContext* Context);
};