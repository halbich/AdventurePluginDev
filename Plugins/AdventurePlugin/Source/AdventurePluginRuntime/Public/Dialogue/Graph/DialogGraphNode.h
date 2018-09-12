#pragma once

#include "CoreMinimal.h"
#include "GenericGraphRuntime/Public/GenericGraphNode.h"
#include "Presenter/DialoguePresenterInterface.h"
#include "DialogGraphNode.generated.h"

class UDialogueController;
class UDialoguePresenterWidget;


UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode : public UGenericGraphNode
{
	GENERATED_BODY()

public:
	UDialogGraphNode();
	virtual ~UDialogGraphNode();

	virtual FText GetDescription_Implementation() const;

#if WITH_EDITOR

	virtual void SetNodeTitle(const FText& NewTitle) override;

	virtual bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage) override;

#endif

	virtual bool Execute(UDialogueController* controller, IDialoguePresenterInterface* widget)
	{
		return true;
	}

	virtual UDialogGraphNode* GetNextNode()
	{
		return ChildrenNodes.Num() > 0 ? Cast<UDialogGraphNode>(ChildrenNodes[0]) : nullptr;
	}

	
};
