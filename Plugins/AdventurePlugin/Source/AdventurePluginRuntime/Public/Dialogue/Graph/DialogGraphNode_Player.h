#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_Player.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Player : public UDialogGraphNode
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
		return FText::Format(NSLOCTEXT("DialogGraphNode_Player", "PlayerSay", "Player: \"{0}\""), DialogText);
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Green;
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		if (Other->IsA(UDialogGraphNode_Player::StaticClass()))
		{
			ErrorMessage = FText::FromString("Don't do that!!!");
			return false;
		}
		return true;
	}

#endif
};
