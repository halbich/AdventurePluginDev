#pragma once

#include "CoreMinimal.h"
#include "GenericGraphRuntime/Public/GenericGraph.h"
#include "QuestGraph.generated.h"

class UQuestGraphNode;

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

	bool GetFlag(FName FlagName);
	void SetFlag(FName FlagName);
	bool GetBool(FName VarName, bool bDefaultValue = false);
	bool SetBool(FName VarName, bool bValue);
	int32 GetInteger(FName VarName, int32 DefaultValue = 0);
	bool SetInteger(FName VarName, int32 Value);
	FString GetString(FName VarName, FString DefaultValue = "");
	bool SetString(FName VarName, FString Value);

	UPROPERTY(EditAnywhere, Category = "AdventurePlugin")
	TMap<FName, FBoolVariable> BoolVariables;

	UPROPERTY(EditAnywhere, Category = "AdventurePlugin")
	TMap<FName, FIntegerVariable> IntegerVariables;

	UPROPERTY(EditAnywhere, Category = "AdventurePlugin")
	TMap<FName, FStringVariable> StringVariables;
};
