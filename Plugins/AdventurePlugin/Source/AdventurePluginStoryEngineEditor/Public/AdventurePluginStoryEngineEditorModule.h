// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "Styling/SlateStyle.h"
#include "IAssetTools.h"
#include "AdventurePluginEditor.h"

extern const FName AdventurePluginStoryEngineEditorAppIdentifier;

//class FToolBarBuilder;
//class FMenuBuilder;
//class SGraphEditor;

class FAdventurePluginStoryEngineEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

	TSharedPtr<FSlateStyleSet> StyleSet;
	TSharedPtr<class FUICommandList> PluginCommands;
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
};