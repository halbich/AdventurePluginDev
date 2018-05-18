// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "Misc/NotifyHook.h"

class FToolBarBuilder;
class FMenuBuilder;
class SGraphEditor;

class FAdventurePluginDialogEditorModule : public IModuleInterface, public FNotifyHook
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);
	void CreateInternalWidgets();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	void DummyAction();
	bool CanDummyAction() const;
	TSharedRef<SGraphEditor> CreateGraphEditorWidget();

private:
	TSharedPtr<class FUICommandList> PluginCommands;
	TSharedPtr<class SGraphEditor> GraphEditor;
	TSharedPtr<FUICommandList> GraphEditorCommands;
};