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
		ChoiceCount = 1;
#endif
		ContextMenuName = FText::FromString("Options");
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

	virtual bool Execute(UDialogueController* controller, IDialoguePresenterInterface* widget) override
	{
		selectedOptionIndex = -1;
		// Go through all child nodes, if visiting something other than Player Line, go to their children, find all Player Lines and show them to the player.
		auto optionsToPresent = TArray<UDialogGraphNode*>();
		optionsToPresent.Reserve(ChildrenNodes.Num());
		for (auto* childNode : ChildrenNodes) {
			while (childNode != nullptr) {
				auto* dialogOption = Cast<UDialogGraphNode_Player>(childNode);
				if (dialogOption != nullptr) {
					// Found a player line to present
					optionsToPresent.Add(dialogOption);
					break;
				}
				// Player line not found, go to child node.
				auto* childNodeCasted = Cast<UDialogGraphNode>(childNode);
				if (childNodeCasted == nullptr)
				{
					// Invalid node found or end of tree. Stop this search.
					break;
				}
				childNode = childNodeCasted->GetNextNode();
			}
		}
		if (optionsToPresent.Num() != 0) {
			widget->Execute_ShowDialogueSelection(widget->_getUObject(), optionsToPresent, controller);
		}
		else {
			// TODO: Show the fallback for no results. 
		}
		return false;
	}

	virtual bool DialogueOptionSelected_Implementation(int32 selectedNodeIndex, UDialogueController* controller) override {
		this->selectedOptionIndex = selectedNodeIndex;
		return true;
	}

	virtual UDialogGraphNode* GetNextNode() override
	{
		// TODO: Warning when calling with invalid index.
		return (selectedOptionIndex >= 0 && selectedOptionIndex < ChildrenNodes.Num()) ? Cast<UDialogGraphNode>(ChildrenNodes[selectedOptionIndex]) : nullptr;
	}

	
protected:
	UPROPERTY(Transient)
	int32 selectedOptionIndex;
};
