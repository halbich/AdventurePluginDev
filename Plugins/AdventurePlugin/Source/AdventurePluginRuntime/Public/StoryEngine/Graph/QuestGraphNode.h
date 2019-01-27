#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraphNode.h"
#include "QuestGraphNode.generated.h"

class UAdventurePluginGameContext;

UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UQuestGraphNode : public UGenericGraphNode
{
	GENERATED_BODY()

public:
	UQuestGraphNode();
	virtual ~UQuestGraphNode();

	UFUNCTION(BlueprintCallable, Category = "AdventurePlugin")
	virtual bool IsSatisfied(UAdventurePluginGameContext* gameContext) { return true; };

#if WITH_EDITORONLY_DATA

	UPROPERTY(EditAnywhere, Category = "QuestNode")
	FText Location;

#endif

#if WITH_EDITOR

	virtual bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage) override;

	virtual bool CanRename() const override;

#endif

	bool ParentNodesSatisfied(UAdventurePluginGameContext* GameContext);
};
