// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "AdventurePluginEditor.h"

class FToolBarBuilder;
class FMenuBuilder;

class FAdventurePluginInventoryEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

	FAdventurePluginEditor::FAdventurePluginEditorMenuExtender EditorMenuExtender;
	FDelegateHandle EditorMenuExtenderHandle;

private:

	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

protected:

	TSharedRef<FExtender> OnExtendLevelEditorViewMenu(const TSharedRef<FUICommandList> CommandList)
	{
		TSharedRef<FExtender> Extender(new FExtender());

		Extender->AddMenuExtension(
			"AdventurePluginEditorTabs",
			EExtensionHook::After,
			PluginCommands,
			FMenuExtensionDelegate::CreateRaw(this, &FAdventurePluginInventoryEditorModule::AddMenuExtension));

		return Extender;
	}

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};