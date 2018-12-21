#pragma once

#include "Core.h"
#include "TextProperty.h" 
#include "Classes/Engine/Texture2D.h"
#include "IconThumbnailInterface.h"
#include "Delegate.h"
#include "ItemCombination.h"
#include "ItemCombinationInterface.h"
#include "InventoryItem.generated.h"

class UInventoryItemBlueprint;

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

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere)
		TMap<UBlueprint*, TScriptInterface<IItemCombinationInterface>> AllCombinations;

	UPROPERTY()
		UInventoryItemBlueprint* ParentBlueprint;
#endif

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void AddCombinationObject(TSubclassOf<UInventoryItem> InventoryItem, UItemCombination* ToAdd);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void AddCombination(TSubclassOf<UInventoryItem> InventoryItem, FText CombinationName, FCombinationEvent CombinationEvent);

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
		void InitCombinations();

	virtual UTexture2D* GetIcon() const override
	{
		return Icon;
	}

	void RefreshCombinations();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		TScriptInterface<IItemCombinationInterface> GetCombinationWithItem(TSubclassOf<UInventoryItem> TargetItem)
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
		TMap<TSubclassOf<UInventoryItem>, TScriptInterface<IItemCombinationInterface>> Combinations;

	bool TryCombineWithInternal(UInventoryItem* TargetItem, UAdventurePluginGameContext* Context);
};