
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
 * The public interface to this module.  In most cases, this interface is only public to sibling modules
 * within this plugin.
 * Takes care of logging, registering inventory item and adventure character assets, creates a section in project settings, registers custom thumbnails renderers.
 */
class ADVENTUREPLUGINEDITOR_API FAdventurePluginEditor : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void Log(EMessageSeverity::Type EngineMessageSeverity, const FText& Message) const;
	virtual void Log(const TSharedRef< class FTokenizedMessage >& Message) const;


	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline FAdventurePluginEditor& Get()
	{
		return FModuleManager::LoadModuleChecked<FAdventurePluginEditor>("AdventurePluginEditor");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("AdventurePluginEditor");
	}

	inline EAssetTypeCategories::Type DefaultAssetCategory() const
	{
		return AdventurePluginAssetCategory;
	}

	void RegisterEditorNodeForRuntimeNode(TSubclassOf<UGenericGraphNode> RuntimeNode, TSubclassOf<UEdNode_GenericGraphNode> EditorNode);

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
