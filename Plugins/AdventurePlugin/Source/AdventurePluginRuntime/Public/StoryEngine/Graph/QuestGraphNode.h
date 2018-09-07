#pragma once

#include "CoreMinimal.h"
#include "GenericGraphRuntime/Public/GenericGraphNode.h"
#include "QuestGraphNode.generated.h"


UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UQuestGraphNode : public UGenericGraphNode
{
	GENERATED_BODY()

public:
	UQuestGraphNode();
	virtual ~UQuestGraphNode();

	virtual FText GetDescription_Implementation() const;

#if WITH_EDITOR

	virtual void SetNodeTitle(const FText& NewTitle) override;

	virtual bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage) override;

#endif
};
