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
};

USTRUCT()
struct ADVENTUREPLUGINRUNTIME_API FIntegerVariable
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		int32 DefaultValue;
};

USTRUCT()
struct ADVENTUREPLUGINRUNTIME_API FStringVariable
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		FString DefaultValue;
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

	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Quest")
		bool GetFlag(UAdventurePluginGameContext* GameContext, FName FlagName);
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Quest")
		void SetFlag(UAdventurePluginGameContext* GameContext, FName FlagName);
	
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Quest")
		bool GetBool(UAdventurePluginGameContext* GameContext, FName VarName);
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Quest")
		bool SetBool(UAdventurePluginGameContext* GameContext, FName VarName, bool bValue);
	
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Quest")
		int32 GetInteger(UAdventurePluginGameContext* GameContext, FName VarName);
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Quest")
		bool SetInteger(UAdventurePluginGameContext* GameContext, FName VarName, int32 Value);
	
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Quest")
		FString GetString(UAdventurePluginGameContext* GameContext, FName VarName);
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Quest")
		bool SetString(UAdventurePluginGameContext* GameContext, FName VarName, FString Value);
	
	/* Returns the list of all nodes that can be set to true, i.e. they are not true and all of their predecessors are true.*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Quest")
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