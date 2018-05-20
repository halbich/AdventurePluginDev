// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "Misc/NotifyHook.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Math/Color.h"
#include "AdventurePluginEditor.h"

class FToolBarBuilder;
class FMenuBuilder;
class SGraphEditor;

class FAdventurePluginDialogEditorModule : public IModuleInterface, public FAssetEditorToolkit, public FNotifyHook
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

	FAdventurePluginEditor::FAdventurePluginEditorMenuExtender EditorMenuExtender;
	FDelegateHandle EditorMenuExtenderHandle;

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	
private:

	void AddMenuExtension(FMenuBuilder& Builder);
	void CreateInternalWidgets();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<class SDockTab> SpawnTab_GraphCanvas(const class FSpawnTabArgs& SpawnTabArgs);

	void DummyAction();
	bool CanDummyAction() const;
	TSharedRef<SGraphEditor> CreateGraphEditorWidget();

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
	TSharedPtr<class SGraphEditor> GraphEditor;
	TSharedPtr<FUICommandList> GraphEditorCommands;

	/**	The tab ids for the dialog editor */
	static const FName GraphCanvasTabId;
};