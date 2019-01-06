#pragma once

#include "CoreMinimal.h"
#include "GenericGraphNode.h"
#include "GameplayTagContainer.h"
#include "GenericGraph.generated.h"

#define LOG_INFO(FMT, ...) UE_LOG(GenericGraphRuntime, Display, (FMT), ##__VA_ARGS__)

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UGenericGraph : public UObject
{
	GENERATED_BODY()

public:
	UGenericGraph();
	virtual ~UGenericGraph();

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraph")
	FString Name;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraph")
	TSubclassOf<UGenericGraphNode> NodeType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GenericGraph")
	FGameplayTagContainer GraphTags;

	UPROPERTY(BlueprintReadOnly, Category = "GenericGraph")
	TArray<UGenericGraphNode*> RootNodes;

	UPROPERTY(BlueprintReadOnly, Category = "GenericGraph")
	TArray<UGenericGraphNode*> AllNodes;

	UFUNCTION(BlueprintCallable, Category = "GenericGraph")
	void Print(bool ToConsole = true, bool ToScreen = true);

	UFUNCTION(BlueprintCallable, Category = "GenericGraph")
	int GetLevelNum() const;

	UFUNCTION(BlueprintCallable, Category = "GenericGraph")
	void GetNodesByLevel(int Level, TArray<UGenericGraphNode*>& Nodes);

	void ClearGraph();

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	class UEdGraph* EdGraph;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraph_Editor")
	bool bCanRenameNode;
#endif
};
