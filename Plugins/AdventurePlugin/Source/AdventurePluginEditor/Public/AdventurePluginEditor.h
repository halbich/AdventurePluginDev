// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "TokenizedMessage.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "MessageLog.h"

/**
 * The public interface to this module.  In most cases, this interface is only public to sibling modules
 * within this plugin.
 */
class FAdventurePluginEditor : public IModuleInterface, public IHasToolBarExtensibility
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void Log(EMessageSeverity::Type EngineMessageSeverity, const FText& Message) const;;
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


	/** Delegates to be called to extend the level viewport menus */
	DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FExtender>, FAdventurePluginEditorMenuExtender, const TSharedRef<FUICommandList>);


	/** Gets the extensibility managers for outside entities to extend this editor's menus and toolbars */
	virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override { return ToolBarExtensibilityManager; }
	virtual TArray<FAdventurePluginEditorMenuExtender>& GetAllAdventurePluginEditorToolbarExtenders() { return AdventurePluginEditorToolbarExtenders; }

private:
	TSharedPtr<class FExtensibilityManager> ToolBarExtensibilityManager;
	TSharedPtr<class FUICommandList> PluginCommands;

	TArray<FAdventurePluginEditorMenuExtender> AdventurePluginEditorToolbarExtenders;

	void AddToolbarExtension(FToolBarBuilder& Builder);
};
