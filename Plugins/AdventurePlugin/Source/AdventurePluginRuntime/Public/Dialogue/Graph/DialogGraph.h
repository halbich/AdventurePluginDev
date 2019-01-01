#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraph.h"
#include "AdventureCharacter.h"
#include "DialogGraphNode_Event.h"
#include "DialogGraph.generated.h"

class UDialogGraphNode;

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraph : public UGenericGraph
{
	GENERATED_BODY()

public:
	UDialogGraph();
	virtual ~UDialogGraph();

	UPROPERTY(BlueprintReadOnly, Category = "AdventurePlugin")
		UDialogGraphNode* MainEntryPoint;

	UPROPERTY(BlueprintReadOnly, Category = "AdventurePlugin")
		TMap<FName, UDialogGraphNode*> SecondaryEntryPoints;

	UPROPERTY(BlueprintReadOnly, Category = "AdventurePlugin")
		TMap<FName, UDialogGraphNode*> IdToNodeMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventurePlugin")
		UAdventureCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdventurePlugin")
		UAdventureCharacter* NPCCharacter;

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
		UDialogGraphNode_Event* GetEventNode(FName EventName);
};
