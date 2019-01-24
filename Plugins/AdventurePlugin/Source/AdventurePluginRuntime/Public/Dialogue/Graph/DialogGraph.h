#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraph.h"
#include "AdventureCharacter.h"
#include "AdventureCharacterBlueprint.h"
#include "DialogGraphNode_Event.h"
#include "DialogGraph.generated.h"

class UDialogGraphNode;

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraph : public UGenericGraph
{
	GENERATED_BODY()

public:

	static const FName MainEntryName;

	UDialogGraph();
	virtual ~UDialogGraph();

	UPROPERTY(BlueprintReadOnly, Category = "DialogGraph")
		UDialogGraphNode* MainEntryPoint;

	UPROPERTY(BlueprintReadOnly, Category = "DialogGraph")
		TMap<FName, UDialogGraphNode*> SecondaryEntryPoints;

	UPROPERTY(BlueprintReadOnly, Category = "DialogGraph")
		TMap<FName, UDialogGraphNode*> IdToNodeMap;

	UPROPERTY(BlueprintReadOnly, Category = "DialogGraph")
		TSubclassOf<UAdventureCharacter> PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "DialogGraph")
		TSubclassOf<UAdventureCharacter> NPCCharacter;

#if WITH_EDITORONLY_DATA

	UPROPERTY(EditAnywhere, Category = "DialogGraph", Meta = (DisplayName = "Player Character"))
		UAdventureCharacterBlueprint* PickerPlayerCharacter;

	UPROPERTY(EditAnywhere, Category = "DialogGraph", Meta = (DisplayName = "NPC Character"))
		UAdventureCharacterBlueprint* PickerNPCCharacter;

#endif

	UFUNCTION(BlueprintCallable, Category = "DialogGraph")
		UDialogGraphNode_Event* GetEventNode(FName EventName);
};
