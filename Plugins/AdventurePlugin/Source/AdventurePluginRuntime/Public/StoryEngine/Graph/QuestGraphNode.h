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

	virtual bool IsSatisfied() { return true; };

#if WITH_EDITOR

	virtual bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage) override;

	virtual bool CanRename() const override;

#endif
};
