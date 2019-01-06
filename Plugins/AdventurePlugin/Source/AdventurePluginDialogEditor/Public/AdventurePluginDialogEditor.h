// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "Misc/NotifyHook.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Math/Color.h"
#include "AdventurePluginEditor.h"

class FAdventurePluginDialogDebugger;
class FToolBarBuilder;
class FMenuBuilder;
class SGraphEditor;
class UDialogGraph;

class FAdventurePluginDialogEditor : public FAssetEditorToolkit, public FNotifyHook
{
public:

	~FAdventurePluginDialogEditor();

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;

	void InitDialogEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit);
	TSharedRef<class SDockTab> GetPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	void DebuggerUpdateGraph();
	
private:

	void CreateInternalWidgets();
	TSharedRef<SGraphEditor> CreateGraphEditorWidget();

	TSharedRef<class SDockTab> SpawnTab_GraphCanvas(const class FSpawnTabArgs& SpawnTabArgs);

	void DummyAction();
	bool CanDummyAction() const;

	/* The Dialog Graph being edited */
	UDialogGraph* DialogGraph;

private:
	TSharedPtr<class FUICommandList> PluginCommands;
	TSharedPtr<class SGraphEditor> GraphEditor;
	TSharedPtr<FUICommandList> GraphEditorCommands;

	/**	The tab ids for the dialog editor */
	static const FName GraphCanvasTabId;

	TSharedPtr<class FAdventurePluginDialogDebugger> Debugger;
};