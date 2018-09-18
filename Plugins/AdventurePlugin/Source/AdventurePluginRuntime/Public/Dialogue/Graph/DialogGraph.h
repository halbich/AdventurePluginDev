#pragma once

#include "CoreMinimal.h"
#include "GenericGraphRuntime/Public/GenericGraph.h"
#include "AdventureCharacter.h"
#include "DialogGraph.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraph : public UGenericGraph
{
	GENERATED_BODY()

public:
	UDialogGraph();
	virtual ~UDialogGraph();

	UPROPERTY(BlueprintReadOnly, Category = "AdventurePlugin")
		UGenericGraphNode* MainEntryPoint;

	UPROPERTY(BlueprintReadOnly, Category = "AdventurePlugin")
		TMap<FName, UGenericGraphNode*> SecondaryEntryPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventurePlugin")
		UAdventureCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventurePlugin")
		UAdventureCharacter* NPCCharacter;
};
