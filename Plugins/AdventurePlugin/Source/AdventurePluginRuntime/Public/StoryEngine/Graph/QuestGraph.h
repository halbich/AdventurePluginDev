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
	UPROPERTY(BlueprintReadOnly, Category = "AdventurePlugin")
		UQuestGraphNode* EndNode;

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
		bool GetFlag(UAdventurePluginGameContext* GameContext, FName FlagName);
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
		void SetFlag(UAdventurePluginGameContext* GameContext, FName FlagName);
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
		bool GetBool(FName VarName, bool bDefaultValue = false);
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
		bool SetBool(FName VarName, bool bValue);
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
		int32 GetInteger(FName VarName, int32 DefaultValue = 0);
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
		bool SetInteger(FName VarName, int32 Value);
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
		FString GetString(FName VarName, FString DefaultValue = "");
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
		bool SetString(FName VarName, FString Value);
	/* Returns the list of all nodes that can be set to true, i.e. they are not true and all of their predecessors are true.*/
	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
		TArray<UQuestGraphNode*> GetSatisfiableNodes(UAdventurePluginGameContext* GameContext);

	UPROPERTY(EditAnywhere, Category = "AdventurePlugin")
		TMap<FName, FBoolVariable> BoolVariables;

	UPROPERTY(EditAnywhere, Category = "AdventurePlugin")
		TMap<FName, FIntegerVariable> IntegerVariables;

	UPROPERTY(EditAnywhere, Category = "AdventurePlugin")
		TMap<FName, FStringVariable> StringVariables;

	UPROPERTY(EditAnywhere, Category = "AdventurePlugin")
		TMap<FName, FQuestEvent> QuestEvents;

protected:
	FText GetGraphNameText();
};
