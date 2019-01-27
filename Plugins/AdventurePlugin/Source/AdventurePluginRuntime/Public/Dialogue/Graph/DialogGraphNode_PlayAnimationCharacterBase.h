#pragma once

#include "CoreMinimal.h"
#include "Common/AdventurePluginGameContext.h"
#include "DialogGraphNode.h"
#include "DialogGraphNode_PlayAnimationBase.h"
#include "DialogGraph.h"
#include "AdventureCharacterManager.h"
#include "Presenter/DialoguePresenterInterface.h"
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
		if (context == nullptr || !context->IsValidLowLevel() ||
			context->AdventureCharacterManager == nullptr || !context->AdventureCharacterManager->IsValidLowLevel())
		{
			// TODO: Log warning/error.
			return nullptr;
		}
		TSubclassOf<UAdventureCharacter> characterClass = GetAnimatedObjectClass();
		if (characterClass == nullptr)
		{
			// TODO: Log error.
			return nullptr;
		}
		auto* characterInstance = context->AdventureCharacterManager->GetCharacter(characterClass);
		return characterInstance;
	}
};
