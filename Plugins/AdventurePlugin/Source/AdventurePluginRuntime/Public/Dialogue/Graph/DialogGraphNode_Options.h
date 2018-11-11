#pragma once

#include "CoreMinimal.h"
#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_Player.h"
#include "NodeInterfaces/DialogueNodeShowOptionsCallbackInterface.h"
#include "DialogGraphNode_Options.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_Options : public UDialogGraphNode, public IDialogueNodeShowOptionsCallbackInterface
{
	GENERATED_BODY()

public:

	UDialogGraphNode_Options()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("Options");
#endif
		ChoiceCount = 1;
	}

	virtual inline FText GetDescription_Implementation() const
	{
		return NSLOCTEXT("DialogGraphNode_Options", "OptionsName", "Dialog Options");
	}

	UPROPERTY(EditAnywhere, Category = "DialogGraphNode_Editor")
	uint32 ChoiceCount;

	virtual inline uint32 GetOutputPinsCount() const override
	{
		return ChoiceCount;
	}

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

	virtual bool Execute(UDialogueController* controller, IDialoguePresenterInterface* widget) override
	{
		selectedOptionIndex = -1;
		optionToBinMapping.Reset();
		// Go through all child nodes, if visiting something other than Player Line, go to their children, find all Player Lines and show them to the player.
		auto optionsToPresent = TArray<FDialogLineData>();
		optionsToPresent.Reserve(ChoiceCount);
		for (int binIndex = 0; binIndex < (int)ChoiceCount; ++binIndex)
		{
			auto* childNode = GetFirstChildInBin(binIndex);
			while (childNode != nullptr)
			{
				auto* nodeCasted = Cast<UDialogGraphNode>(childNode);
				if (nodeCasted == nullptr)
				{
					// Invalid node found or end of tree. Stop this search.
					break;
				}
				if (nodeCasted->IsDialogOption())
				{
					// Found a player line to present
					optionToBinMapping.Add(optionsToPresent.Num(), binIndex);
					optionsToPresent.Add(nodeCasted->GetDialogLine());
					break;
				}
				// Player line not found, go to child node.
				childNode = nodeCasted->GetNextNode(controller);
			}
		}
		if (optionsToPresent.Num() != 0)
		{
			widget->Execute_ShowDialogueSelection(widget->_getUObject(), optionsToPresent, controller);
		}
		else
		{
			// TODO: Show the fallback for no results. 
		}
		return false;
	}

	virtual bool DialogueOptionSelected_Implementation(int32 selectedNodeIndex, UDialogueController* controller) override
	{
		this->selectedOptionIndex = optionToBinMapping[selectedNodeIndex];
		return true;
	}

	virtual UDialogGraphNode* GetNextNode(UDialogueController* controller) override
	{
		// TODO: Warning when calling with invalid index.
		check(selectedOptionIndex >= 0 && selectedOptionIndex < (int)ChoiceCount);
		return Cast<UDialogGraphNode>(GetFirstChildInBin(selectedOptionIndex));
		// return (selectedOptionIndex >= 0 && selectedOptionIndex < ChildrenNodes.Num()) ? Cast<UDialogGraphNode>(ChildrenNodes[selectedOptionIndex]) : nullptr;
	}

	
protected:
	UPROPERTY(Transient)
	int32 selectedOptionIndex;

	UPROPERTY(Transient)
	TMap<int32, int32> optionToBinMapping;
};
