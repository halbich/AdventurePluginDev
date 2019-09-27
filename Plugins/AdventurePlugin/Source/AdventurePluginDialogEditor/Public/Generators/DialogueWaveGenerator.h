#pragma once
#include "CoreMinimal.h"

class UDialogGraph;
class UDialogueWave;
class UDialogueVoice;
class UDialogueWave;
class UAdventureCharacter;
class UDialogGraphNode_DialogLineBase;

/**
* A class that can create UDialogueWave objects for all nodes in a graph and ensure that UDialogueVoice objects are generated on the character.
*/
class FDialogueWaveGenerator
{
public:
	FDialogueWaveGenerator(UDialogGraph* Graph): Graph(Graph)
	{
	
	}
	/**
	* Generates the Dialogue wave assets for all nodes in the graph this class reprsents.
	*/
	void GenerateDialogueWaves();

	private:
	/**
	* The graph used, set in the constructor.
	*/
	UDialogGraph* Graph;
	/**
	* Cached from the graph, the reference to the player character.
	*/
	UAdventureCharacter* PlayerCharacter;
	/**
	* Cached from the graph, the reference to the player character's voice.
	*/
	UDialogueVoice* PlayerVoice;
	/**
	* Cached from the graph, the reference to the npc character.
	*/
	UAdventureCharacter* NpcCharacter;
	/**
	* Cached from the graph, the reference to the npc character's voice.
	*/
	UDialogueVoice* NpcVoice;
	/**
	* Updates the wave for the specified dialogue node, even generating it if it doesn't exist yet.
	* @param DialogNode The node for which the Dialogue wave should be generated or updated..
	*/
	void UpdateDialogueWaveForDialogueNode(UDialogGraphNode_DialogLineBase* DialogNode);
	/**
	* Generate a new dialogue wave for the specified node.
	* @param DialogNode The node for which the Dialogue wave should be generated.
	*/
	void GenerateDialogueWaveForNode(UDialogGraphNode_DialogLineBase* Node);
	/**
	* Generate if the name of the Dialogue Wave and its path fit to the expected format.
	* @param DialogNode The node that should be checked.
	*/
	bool IsDialogueWaveNameCorrect(UDialogGraphNode_DialogLineBase* Node);
	/**
	* Get the path where the specified node should have its dialogue wave stored.
	* @param DialogNode The dialogue node for which we need the path.
	*/
	FString GetDialogueWavePath(UDialogGraphNode_DialogLineBase* Node);
	/**
	* Get the dialogue voice of the specified character, creating it if it doesn't exist.
	* @param DialogNode The character whose voice is requested
	*/
	UDialogueVoice* GetDialogueVoiceOfCharacter(UAdventureCharacter* Character);
	/**
	* Create a dialogue voice for the specified character.
	* @param DialogNode The character whose voice is requested
	*/
	void GenerateDialogueVoiceForCharacter(UAdventureCharacter* Character);

};
