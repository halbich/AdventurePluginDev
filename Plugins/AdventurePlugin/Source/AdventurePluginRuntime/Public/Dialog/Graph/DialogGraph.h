#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraph.h"
#include "AdventureCharacter.h"
#include "Templates/SharedPointer.h"
#include "AdventureCharacterBlueprint.h"
#include "DialogGraphNode_Event.h"
#include "Engine/GameInstance.h"
#include "DialogGraph.generated.h"

class UDialogGraphNode;
class UAdventurePluginGameContext;

/**
* This graph represents a dialog between a Player and up to 1 NPC.
* Can contain branching, changing of variables, firing events, displaying dialog lines and many other things.
* The easiest way to extend the graph is to create custom nodes inheriting from UDialogGraphNode.
* That will add whole new capabilities to the graph. 
* These nodes don't have to be registered anywhere, the graph automatically finds all nodes inheriting from UDialogGraphNode.
* To see how the actual displaying of this graph works, see UDialogController.
* Note that the dialog graph does not support creation of cycles, if you really need one, you need to use a UDialogGraphNode_Goto node.
*/
UCLASS(Blueprintable)
class ADVENTUREPLUGINRUNTIME_API UDialogGraph : public UGenericGraph
{
	GENERATED_BODY()

public:

	/**
	* The name of the main entry point. Same for all graphs.
	*/
	static const FName MainEntryName;

	UDialogGraph();
	virtual ~UDialogGraph();

	TWeakObjectPtr<UGameInstance> CachedGameInstance;

	/**
	* The main entry point of this graph. The execution should start here if no other entry point is specified.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "DialogGraph")
	UDialogGraphNode* MainEntryPoint;

	/**
	* All the other entry points defined on this graph in a map indexed by their key.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "DialogGraph")
	TMap<FName, UDialogGraphNode*> SecondaryEntryPoints;

	/**
	* A map to provide easy access to nodes based on their ID.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "DialogGraph")
	TMap<FName, UDialogGraphNode*> IdToNodeMap;

	/**
	* The player character saying this dialog.
	* <p>
	* Note: In editor this is filled by UDialogGraph#PickerPlayerCharacter.
	* We did that because TSubclassOf editor picker does not support icons, which we wanted to have.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "DialogGraph")
	TSubclassOf<UAdventureCharacter> PlayerCharacter;

	/**
	* The NPC with whom the Player is talking in this dialog. Can be null, but in that case NPC lines should not be used.
	* <p>
	* Note: In editor this is filled by UDialogGraph#PickerNPCCharacter
	* We did that because TSubclassOf editor picker does not support icons, which we wanted to have.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "DialogGraph")
	TSubclassOf<UAdventureCharacter> NPCCharacter;

#if WITH_EDITORONLY_DATA

	/**
	* The helper property for filling UDialogGraph#PlayerCharacter. It is used only in editor
	* because its picker supports user-friendly asset thumbnails.
	*/
	UPROPERTY(EditAnywhere, Category = "DialogGraph", Meta = (DisplayName = "Player Character"))
	UAdventureCharacterBlueprint* PickerPlayerCharacter;

	/**
	* The helper property for filling UDialogGraph#NPCCharacter. It is used only in editor
	* because its picker supports user-friendly asset thumbnails. 
	*/
	UPROPERTY(EditAnywhere, Category = "DialogGraph", Meta = (DisplayName = "NPC Character"))
	UAdventureCharacterBlueprint* PickerNPCCharacter;

#endif

	/**
	* Retrieve the instance of the player character in this dialog.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The player character instance.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Dialog")
	UAdventureCharacter* GetDialogPlayerCharacterInstance(UAdventurePluginGameContext* GameContext);

	/**
	* Retrieve the instance of the NPC character in this dialog.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @return The NPC character instance.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Dialog")
	UAdventureCharacter* GetDialogNPCCharacterInstance(UAdventurePluginGameContext* GameContext);

	/**
	* Returns the instance of a specific character definition class.
	* @param GameContext Provides access to all Adventure Plugin data and functionality.
	* @param Speaker The class of the character whose instance is requested.
	* @return The character instance.
	*/
	UFUNCTION(BlueprintCallable, Category = "Adventure Plugin|Dialog")
	UAdventureCharacter * GetSpeakerInstance(UAdventurePluginGameContext* GameContext, TSubclassOf<UAdventureCharacter> Speaker);

	virtual class UWorld* GetWorld() const override {
		if (CachedGameInstance.IsValid())
		{
			return CachedGameInstance.Get()->GetWorld();
		}
		return nullptr;
	}
};
