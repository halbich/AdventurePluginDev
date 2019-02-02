#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_PlayAnimationBase.h"
#include "DialogGraph.h"
#include "AdventureCharacterManager.h"
#include "Presenter/DialogPresenterInterface.h"
#include "NodeInterfaces/DialogNodePlayAnimationCallbackInterface.h"
#include "AnimatableObjectInterface.h"
#include "DialogGraphNode_PlayAnimationCharacterBase.generated.h"

UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_PlayAnimationCharacterBase : public UDialogGraphNode_PlayAnimationBase
{
	GENERATED_BODY()

public:

	virtual TScriptInterface<IAnimatableObjectInterface> GetAnimatedObject(UAdventurePluginGameContext* context) override
	{
		auto* graph = GetDialogGraph();
		TSubclassOf<UAdventureCharacter> characterClass = GetAnimatedObjectClass();
		auto* characterInstance = graph && graph->IsValidLowLevel() ? graph->GetSpeakerInstance(context, characterClass) : nullptr;
		return characterInstance;
	}
};
