// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "Misc/NotifyHook.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Math/Color.h"
#include "AdventurePluginEditor.h"
#include "AdventurePluginDialogEditor.h"
#include "IAssetTools.h"

class FToolBarBuilder;
class FMenuBuilder;
class SGraphEditor;

class FAdventurePluginDialogEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

	FAdventurePluginEditor::FAdventurePluginEditorMenuExtender EditorMenuExtender;
	FDelegateHandle EditorMenuExtenderHandle;

	virtual TSharedRef<FAdventurePluginDialogEditor> CreateDialogEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* Object);

private:

	void AddMenuExtension(FMenuBuilder& Builder);
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

protected:

	TSharedRef<FExtender> OnExtendLevelEditorViewMenu(const TSharedRef<FUICommandList> CommandList)
	{
		TSharedRef<FExtender> Extender(new FExtender());

		Extender->AddMenuExtension(
			"AdventurePluginEditorTabs",
			EExtensionHook::After,
			PluginCommands,
			FMenuExtensionDelegate::CreateRaw(this, &FAdventurePluginDialogEditorModule::AddMenuExtension));

		return Extender;
	}

private:
	TSharedPtr<class FUICommandList> PluginCommands;
	TSharedPtr<FAdventurePluginDialogEditor> DialogEditor;
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;

	/**	The tab ids for the dialog editor */
	static const FName GraphCanvasTabId;
};