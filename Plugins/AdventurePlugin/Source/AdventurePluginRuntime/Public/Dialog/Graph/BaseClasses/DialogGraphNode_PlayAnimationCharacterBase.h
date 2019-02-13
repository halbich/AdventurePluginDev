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

	virtual TScriptInterface<IAnimatableObjectInterface> GetAnimatedObject(UAdventurePluginGameContext* GameContext) override
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		TSubclassOf<UAdventureCharacter> CharacterClass = GetAnimatedObjectClass();
		UAdventureCharacter* CharacterInstance = IsValid(DialogGraph) ? DialogGraph->GetSpeakerInstance(GameContext, CharacterClass) : nullptr;
		return CharacterInstance;
	}
};
