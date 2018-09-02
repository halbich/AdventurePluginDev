#pragma once

#include "CoreMinimal.h"
#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_Options.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Options : public UDialogGraphNode
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Options()
	{
#if WITH_EDITORONLY_DATA
		ChoiceCount = 1;
#endif
	}

	virtual inline FText GetDescription_Implementation() const
	{
		return NSLOCTEXT("DialogGraphNode_Options", "OptionsName", "Dialog Options");
	}

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "DialogGraphNode_Editor")
		uint32 ChoiceCount;
#endif

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return NSLOCTEXT("DialogGraphNode_Options", "OptionsName", "Dialog Options");
	}

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Yellow;
	}

	virtual inline bool CanCreateConnection(UGenericGraphNode* Other, FText& ErrorMessage)
	{
		return true;
	}

	virtual inline uint32 GetOutputPinsCount() const override
	{
		return ChoiceCount;
	}

	/*
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override
	{
		FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
		if (PropertyName == GET_MEMBER_NAME_CHECKED(UDialogGraphNode_Options, ChoiceCount))
		{
			UEdGraph_GenericGraph* GenericGraph = CastChecked<UEdGraph_GenericGraph>(Graph->EdGraph);
			UEdNode_GenericGraphNode* Node = GenericGraph->NodeMap[this];
			for (UEdGraphPin* Pin : Node->Pins) Node->RemovePin(Pin);
			Node->AllocateDefaultPins();
		}
		Super::PostEditChangeProperty(e);
	}
	*/

#endif


	virtual void Execute(UDialogueController* controller, IDialoguePresenterInterface* widget) override
	{

	};
};
