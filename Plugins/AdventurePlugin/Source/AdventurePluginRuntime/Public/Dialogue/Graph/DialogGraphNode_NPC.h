#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_NPC.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_NPC : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_NPC()
	{
		ContextMenuName = FText::FromString("NPC Line");
	}

	virtual inline FText GetDescription_Implementation() const
	{
		return DialogText;
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return FText::Format(NSLOCTEXT("DialogGraphNode_NPC", "NPCSay", "NPC: \"{0}\""), DialogText);
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Red;
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		if (Other->IsA(UDialogGraphNode_NPC::StaticClass()))
		{
			ErrorMessage = FText::FromString("Don't do that!!!");
			return false;
		}
		return true;
	}

#endif

	virtual void Execute(UDialogueController* controller, IDialoguePresenterInterface* widget) override
	{
		widget->Execute_ShowDialogueLine(widget->_getUObject(),this);
	};
};
