/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "GenericGraph/SEdNode_GenericGraphNode.h"
#include "GenericGraph/EdGraph_GenericGraph.h"
#include "Kismet2/Kismet2NameValidators.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Slate.h"

#define LOCTEXT_NAMESPACE "EdNode_GenericGraph"

UEdNode_GenericGraphNode::UEdNode_GenericGraphNode()
{
	bCanRenameNode = true;
}

UEdNode_GenericGraphNode::~UEdNode_GenericGraphNode()
{

}

void UEdNode_GenericGraphNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "MultipleNodes", FName(), FName());
	CreatePin(EGPD_Output, "MultipleNodes", FName(), FName());
}

FText UEdNode_GenericGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (GenericGraphNode == nullptr)
	{
		return Super::GetNodeTitle(TitleType);
	}
	else
	{
		return GenericGraphNode->GetNodeTitle();
	}
}

void UEdNode_GenericGraphNode::PrepareForCopying()
{
	GenericGraphNode->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
}

void UEdNode_GenericGraphNode::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);

	if (FromPin != nullptr)
	{
		if (GetSchema()->TryCreateConnection(FromPin, GetInputPin()))
		{
			FromPin->GetOwningNode()->NodeConnectionListChanged();
		}
	}
}

FLinearColor UEdNode_GenericGraphNode::GetBackgroundColor() const
{
	return GenericGraphNode == nullptr ? FLinearColor::Black : GenericGraphNode->GetBackgroundColor();
}

UEdGraphPin* UEdNode_GenericGraphNode::GetInputPin() const
{
	return Pins[0];
}

UEdGraphPin* UEdNode_GenericGraphNode::GetOutputPin() const
{
	return Pins[1];
}

#if WITH_EDITOR

void UEdNode_GenericGraphNode::PostEditUndo()
{
	UEdGraphNode::PostEditUndo();
}

bool UEdNode_GenericGraphNode::CanUserDeleteNode() const
{
	return !IsValid(GenericGraphNode) || GenericGraphNode->CanDelete();
}

bool UEdNode_GenericGraphNode::CanDuplicateNode() const
{
	return !IsValid(GenericGraphNode) || GenericGraphNode->CanDuplicate();
}

#endif

#undef LOCTEXT_NAMESPACE
