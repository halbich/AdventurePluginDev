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
/**
* Base class for nodes for playing animations on characters.
*/
UCLASS(Abstract, Blueprintable, HideCategories = (GenericGraphNode, GenericGraphNode_Editor))
class ADVENTUREPLUGINRUNTIME_API UDialogGraphNode_PlayAnimationCharacterBase : public UDialogGraphNode_PlayAnimationBase
{
	GENERATED_BODY()

public:
	/**
	* Retrieve the character animated by this class.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The animated character.
	*/
	virtual TScriptInterface<IAnimatableObjectInterface> GetAnimatedObject(UAdventurePluginGameContext* GameContext) override
	{
		UDialogGraph* DialogGraph = GetDialogGraph();
		TSubclassOf<UAdventureCharacter> CharacterClass = GetAnimatedObjectClass();
		UAdventureCharacter* CharacterInstance = IsValid(DialogGraph) ? DialogGraph->GetSpeakerInstance(GameContext, CharacterClass) : nullptr;
		if (!IsValid(CharacterInstance))
		{
			LOG_Warning(NSLOCTEXT("AP", "DialogGraphNode_PlayAnimationCharacterBasdeCharacterNull", "UDialogGraphNode_PlayAnimationCharacterBase:GetAnimatedObject: Cannot retrieve valid animated character."));
		}
		return CharacterInstance;
	}
};
