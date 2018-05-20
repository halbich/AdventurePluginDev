// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginInventoryEditor.h"
#include "AdventurePluginInventoryEditorStyle.h"
#include "AdventurePluginInventoryEditorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"


static const FName AdventurePluginInventoryEditorTabName("AdventurePluginInventoryEditor");

#define LOCTEXT_NAMESPACE "FAdventurePluginInventoryEditorModule"

void FAdventurePluginInventoryEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FAdventurePluginInventoryEditorStyle::Initialize();
	FAdventurePluginInventoryEditorStyle::ReloadTextures();

	FAdventurePluginInventoryEditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAdventurePluginInventoryEditorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FAdventurePluginInventoryEditorModule::PluginButtonClicked),
		FCanExecuteAction());


	// Add to our toolbar menu
	if (FAdventurePluginEditor::IsAvailable())
	{
		EditorMenuExtender = FAdventurePluginEditor::FAdventurePluginEditorMenuExtender::CreateRaw(this, &FAdventurePluginInventoryEditorModule::OnExtendLevelEditorViewMenu);
		
		FAdventurePluginEditor& ape = FAdventurePluginEditor::Get();
		auto& MenuExtenders = ape.GetAllAdventurePluginEditorToolbarExtenders();
		MenuExtenders.Add(EditorMenuExtender);
		EditorMenuExtenderHandle = MenuExtenders.Last().GetHandle();
	}

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AdventurePluginInventoryEditorTabName, FOnSpawnTab::CreateRaw(this, &FAdventurePluginInventoryEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FAdventurePluginInventoryEditorTabTitle", "AdventurePluginInventoryEditor"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FAdventurePluginInventoryEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FAdventurePluginInventoryEditorStyle::Shutdown();

	FAdventurePluginInventoryEditorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AdventurePluginInventoryEditorTabName);

	if (UObjectInitialized() && !IsRunningCommandlet())
	{
		// Unregister the level editor extensions
		{
			FAdventurePluginEditor& LevelEditor = FModuleManager::GetModuleChecked<FAdventurePluginEditor>(TEXT("AdventurePluginEditor"));
			LevelEditor.GetAllAdventurePluginEditorToolbarExtenders().RemoveAll([=](const FAdventurePluginEditor::FAdventurePluginEditorMenuExtender& Extender) { return Extender.GetHandle() == EditorMenuExtenderHandle; });
		}
	}
}



TSharedRef<SDockTab> FAdventurePluginInventoryEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FAdventurePluginInventoryEditorModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("AdventurePluginInventoryEditor.cpp"))
	);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(WidgetText)
		]
		];
}

void FAdventurePluginInventoryEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(AdventurePluginInventoryEditorTabName);
}

void FAdventurePluginInventoryEditorModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FAdventurePluginInventoryEditorCommands::Get().OpenPluginWindow);
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAdventurePluginInventoryEditorModule, AdventurePluginInventoryEditor)