#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "Presenter/DialogPresenterInterface.h"
#include "NodeInterfaces/DialogNodeShowLineCallbackInterface.h"
#include "DialogGraph.h"
#include "DialogGraphNode_DialogLineBase.h"
#include "DialogGraphNode_NPC.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_NPC : public UDialogGraphNode_DialogLineBase
{
	GENERATED_BODY()

public:

	UDialogGraphNode_NPC()
	{
#if WITH_EDITORONLY_DATA
		ContextMenuName = FText::FromString("NPC Line");
		ContextMenuCategory = NSLOCTEXT("NodeCategories", "LineCategory", "Lines");
#endif
		DialogText = NSLOCTEXT("DialogGraphNode_NPC", "DefaultDialog", "<Insert something clever>");
	}

#if WITH_EDITOR

	virtual inline FLinearColor GetBackgroundColor() const
	{
		return FLinearColor::Red;
	}

	virtual UAdventureCharacter* GetSpeakerEditorOnly() const
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		if (!IsValid(DialogGraph))
		{
			LOG_Warning(NSLOCTEXT("AP", "DialogGraphNode_NPCGetSpeakerEditorOnlyGraphInvalid", "DialogGraphNode_NPC:GetSpeakerEditorOnly:Quest is null or invalid."));
			return nullptr;
		}
		return DialogGraph->NPCCharacter.GetDefaultObject();
	}

#endif

	virtual UAdventureCharacter* GetSpeaker(UAdventurePluginGameContext* GameContext) const override
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		if (!IsValid(DialogGraph))
		{
			LOG_Warning(NSLOCTEXT("AP", "DialogGraphNode_NPCGetSpeakerGraphInvalid", "DialogGraphNode_NPC:GetSpeaker:Quest is null or invalid."));
			return nullptr;
		}
		return DialogGraph->GetDialogNPCCharacterInstance(GameContext);
	}
};
