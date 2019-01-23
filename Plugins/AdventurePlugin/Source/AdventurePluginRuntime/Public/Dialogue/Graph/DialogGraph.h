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

	UPROPERTY(BlueprintReadOnly, Category = "AdventurePlugin")
		UDialogGraphNode* MainEntryPoint;

	UPROPERTY(BlueprintReadOnly, Category = "AdventurePlugin")
		TMap<FName, UDialogGraphNode*> SecondaryEntryPoints;

	UPROPERTY(BlueprintReadOnly, Category = "AdventurePlugin")
		TMap<FName, UDialogGraphNode*> IdToNodeMap;

	UPROPERTY(BlueprintReadOnly, Category = "AdventurePlugin")
		TSubclassOf<UAdventureCharacter> PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "AdventurePlugin")
		TSubclassOf<UAdventureCharacter> NPCCharacter;

#if WITH_EDITORONLY_DATA

	UPROPERTY(EditAnywhere, Category = "AdventurePlugin", Meta = (DisplayName = "Player Character"))
		UAdventureCharacterBlueprint* PickerPlayerCharacter;

	UPROPERTY(EditAnywhere, Category = "AdventurePlugin", Meta = (DisplayName = "NPC Character"))
		UAdventureCharacterBlueprint* PickerNPCCharacter;

#endif

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
		UDialogGraphNode_Event* GetEventNode(FName EventName);
};
