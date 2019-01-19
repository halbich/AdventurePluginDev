#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraph.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_Player.h"
#include "Presenter/DialoguePresenterInterface.h"
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
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "OtherCategory", "Other");
#endif
		ChoiceCount = 1;
	}

	UPROPERTY(EditAnywhere, Category = "DialogGraphNode_Editor")
	uint32 ChoiceCount;

	UPROPERTY(BlueprintReadOnly)
	UDialogGraphNode* ChildFallback;

	UPROPERTY(BlueprintReadOnly)
	TMap<int, UDialogGraphNode*> ChildOptions;

	virtual void ResetSpecialChildren() override
	{
		ChildFallback = nullptr;
		ChildOptions.Reset();
	}

#if WITH_EDITOR

	virtual inline FText GetNodeTitle() const
	{
		return NSLOCTEXT("DialogGraphNode_Options", "OptionsName", "OPTIONS");
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

	virtual bool Execute(UAdventurePluginGameContext* context) override
	{
		selectedOptionIndex = -1;
		optionMapping.Reset();
		// Go through all child nodes, if visiting something other than Player Line, go to their children, find all Player Lines and show them to the player.
		auto optionsToPresent = TArray<FDialogLineData>();
		optionsToPresent.Reserve(ChoiceCount);
		check(ChildOptions.Num() == ChoiceCount);
		for (int i = 0; i < (int)ChoiceCount; ++i)
		{
			auto* childNode = ChildOptions[i];
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
					optionMapping.Add(optionsToPresent.Num(), i);
					optionsToPresent.Add(nodeCasted->GetDialogLine());
					break;
				}
				// Player line not found, go to child node.
				childNode = nodeCasted->GetNextNode(context);
			}
		}
		if (optionsToPresent.Num() != 0)
		{
			auto widget = Cast<IDialoguePresenterInterface>(context->DialoguePresenter.GetObject());
			IDialoguePresenterInterface::Execute_ShowDialogueSelection(widget->_getUObject(), optionsToPresent, context->DialogueController);
		}
		else
		{
			// TODO: Show the fallback for no results.
			return true;
		}
		return false;
	}

	virtual bool DialogueOptionSelected_Implementation(int32 selectedNodeIndex, UDialogueController* controller) override
	{
		this->selectedOptionIndex = optionMapping[selectedNodeIndex];
		return true;
	}

	virtual UDialogGraphNode* GetNextNode(UAdventurePluginGameContext* context) override
	{
		// TODO: Warning when calling with invalid index.
		if (selectedOptionIndex < 0) return ChildFallback;
		check(selectedOptionIndex < (int)ChoiceCount);
		return ChildOptions[selectedOptionIndex];
		// return (selectedOptionIndex >= 0 && selectedOptionIndex < ChildrenNodes.Num()) ? Cast<UDialogGraphNode>(ChildrenNodes[selectedOptionIndex]) : nullptr;
	}

	
protected:
	UPROPERTY(Transient)
	int32 selectedOptionIndex;

	UPROPERTY(Transient)
	TMap<int32, int32> optionMapping;
};
