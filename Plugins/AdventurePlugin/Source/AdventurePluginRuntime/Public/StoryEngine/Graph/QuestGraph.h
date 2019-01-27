#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraph.h"
#include "QuestGraph.generated.h"

class UQuestGraphNode;
class UAdventurePluginGameContext;

class FQuestEvent;
DECLARE_DYNAMIC_DELEGATE(FQuestEvent);

USTRUCT()
struct ADVENTUREPLUGINRUNTIME_API FBoolVariable
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		bool DefaultValue;

	UPROPERTY(EditAnywhere)
		bool Value;
};

USTRUCT()
struct ADVENTUREPLUGINRUNTIME_API FIntegerVariable
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		int32 DefaultValue;

	UPROPERTY(EditAnywhere)
		int32 Value;
};

USTRUCT()
struct ADVENTUREPLUGINRUNTIME_API FStringVariable
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		FString DefaultValue;

	UPROPERTY(EditAnywhere)
		FString Value;
};

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UQuestGraph : public UGenericGraph
{
	GENERATED_BODY()

public:
	UQuestGraph();
	virtual ~UQuestGraph();
	UPROPERTY(BlueprintReadOnly, Category = "QuestGraph")
		UQuestGraphNode* EndNode;

	UFUNCTION(BlueprintCallable, Category = "QuestGraph")
		bool GetFlag(UAdventurePluginGameContext* GameContext, FName FlagName);
	UFUNCTION(BlueprintCallable, Category = "QuestGraph")
		void SetFlag(UAdventurePluginGameContext* GameContext, FName FlagName);
	UFUNCTION(BlueprintCallable, Category = "QuestGraph")
		bool GetBool(FName VarName, bool bDefaultValue = false);
	UFUNCTION(BlueprintCallable, Category = "QuestGraph")
		bool SetBool(FName VarName, bool bValue);
	UFUNCTION(BlueprintCallable, Category = "QuestGraph")
		int32 GetInteger(FName VarName, int32 DefaultValue = 0);
	UFUNCTION(BlueprintCallable, Category = "QuestGraph")
		bool SetInteger(FName VarName, int32 Value);
	UFUNCTION(BlueprintCallable, Category = "QuestGraph")
		FString GetString(FName VarName, FString DefaultValue = "");
	UFUNCTION(BlueprintCallable, Category = "QuestGraph")
		bool SetString(FName VarName, FString Value);
	/* Returns the list of all nodes that can be set to true, i.e. they are not true and all of their predecessors are true.*/
	UFUNCTION(BlueprintCallable, Category = "QuestGraph")
		TArray<UQuestGraphNode*> GetSatisfiableNodes(UAdventurePluginGameContext* GameContext);

	UPROPERTY(EditAnywhere, Category = "QuestGraph")
		TMap<FName, FBoolVariable> BoolVariables;

	UPROPERTY(EditAnywhere, Category = "QuestGraph")
		TMap<FName, FIntegerVariable> IntegerVariables;

	UPROPERTY(EditAnywhere, Category = "QuestGraph")
		TMap<FName, FStringVariable> StringVariables;

	UPROPERTY(EditAnywhere, Category = "QuestGraph")
		TMap<FName, FQuestEvent> QuestEvents;

protected:
	FText GetGraphNameText();
};
