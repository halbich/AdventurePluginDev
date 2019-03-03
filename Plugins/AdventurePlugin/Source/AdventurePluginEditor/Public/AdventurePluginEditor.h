#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Developer/Settings/Public/ISettingsModule.h"
#include "Developer/Settings/Public/ISettingsSection.h"
#include "Developer/Settings/Public/ISettingsContainer.h"
#include "TokenizedMessage.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "IAssetTypeActions.h"
#include "MessageLog.h"
#include "EdGraphUtilities.h"
#include "GenericGraph/EdNode_GenericGraphNode.h"
#include "GenericGraph/SEdNode_GenericGraphNode.h"
#include "AdventurePluginRuntime/Public/Common/AdventurePluginConfig.h"

#define LOCTEXT_NAMESPACE "CustomSettings"

/**
 * This module is responsible for the main editor functionality of Adventure Plugin. It takes care
 * of logging, registering inventory item and adventure character assets, creating a section
 * in project settings, registering custom thumbnails renderers etc.
 */
class ADVENTUREPLUGINEDITOR_API FAdventurePluginEditor : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/**
	* Logs the given message with the severity given to the default plugin log
	* and opens the log if it's at least a warning.
	*/
	virtual void Log(EMessageSeverity::Type EngineMessageSeverity, const FText& Message) const;

	/**
	* Logs the given tokenized message to the default plugin log and opens the log
	* if it's at least a warning.
	*/
	virtual void Log(const TSharedRef< class FTokenizedMessage >& Message) const;

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline FAdventurePluginEditor& Get()
	{
		return FModuleManager::LoadModuleChecked<FAdventurePluginEditor>("AdventurePluginEditor");
	}

	/**
	 * Checks to see if this module is loaded and ready. It is only valid to call Get() if IsAvailable() returns true.
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("AdventurePluginEditor");
	}

	/**
	* Returns default category for all AdventurePlugin assets. In this case,
	* it is newly created AdventurePlugin category.
	* @return Default asset category
	*/
	inline EAssetTypeCategories::Type DefaultAssetCategory() const
	{
		return AdventurePluginAssetCategory;
	}

	/**
	* Registers specific editor node representation for corresponding runtime node class. It is
	* necessary when the node visualization should be different from the default one. It is usable
	* for both dialog nodes and quest nodes.
	* @see FAdventurePluginEditor#FindEditorNodeForRuntimeNode
	* @param RuntimeNode The runtime node class for which the editor node should be registered
	* @param EditorNode The editor node class which will visualize the runtime node given
	*/
	void RegisterEditorNodeForRuntimeNode(TSubclassOf<UGenericGraphNode> RuntimeNode, TSubclassOf<UEdNode_GenericGraphNode> EditorNode);

	/**
	* Returns editor node class, which was previously registered for visualizing given runtime
	* node class. When there is no editor node registered, returns the one which was registered
	* for the nearest ancestor of given runtime node, or nullptr, when there was no ancestor registered.
	* @see FAdventurePluginEditor#RegisterEditorNodeForRuntimeNode
	* @param RuntimeNode The runtime node class for which the editor node should be returned
	* @return Editor node class registered for the runtime node, or nullptr
	*/
	const TSubclassOf<UEdNode_GenericGraphNode>* FindEditorNodeForRuntimeNode(TSubclassOf<UGenericGraphNode> RuntimeNode) const;

private:

	bool HandleSettingsSaved();
	void RegisterSettings();
	void UnregisterSettings();

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;

	EAssetTypeCategories::Type AdventurePluginAssetCategory;

	UPROPERTY()
	TMap<TSubclassOf<UGenericGraphNode>, TSubclassOf<UEdNode_GenericGraphNode>> EditorNodeMap;
};

#undef LOCTEXT_NAMESPACE
