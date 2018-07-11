#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_NPC.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_NPC : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	virtual inline FText GetDescription_Implementation() const
	{
		return DialogText;
	}
	
#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return DialogText;
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
};
