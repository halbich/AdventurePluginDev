// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginDialogEditorModule.h"
#include "AdventurePluginDialogEditorStyle.h"
#include "AdventurePluginDialogEditorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "SlateOptMacros.h"
#include "GraphEditor.h"
#include "Framework/Commands/GenericCommands.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Materials/Material.h"
#include "EdGraph/EdGraphSchema.h"

static const FName AdventurePluginDialogEditorTabName("AdventurePluginDialogEditor");
//const FName DialogEditorAppIdentifier = FName(TEXT("DialogEditorApp"));

#define LOCTEXT_NAMESPACE "FAdventurePluginDialogEditorModule"

void FAdventurePluginDialogEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FAdventurePluginDialogEditorStyle::Initialize();
	FAdventurePluginDialogEditorStyle::ReloadTextures();

	FAdventurePluginDialogEditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAdventurePluginDialogEditorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	// Add to our toolbar menu
	if (FAdventurePluginEditor::IsAvailable())
	{
		EditorMenuExtender = FAdventurePluginEditor::FAdventurePluginEditorMenuExtender::CreateRaw(this, &FAdventurePluginDialogEditorModule::OnExtendLevelEditorViewMenu);

		FAdventurePluginEditor& ape = FAdventurePluginEditor::Get();
		auto& MenuExtenders = ape.GetAllAdventurePluginEditorToolbarExtenders();
		MenuExtenders.Add(EditorMenuExtender);
		EditorMenuExtenderHandle = MenuExtenders.Last().GetHandle();
	}

	//FGlobalTabmanager::Get()->RegisterTabSpawner(GraphCanvasTabId, FOnSpawnTab::CreateSP(this, &FAdventurePluginDialogEditorModule::SpawnTab_GraphCanvas))
	//.SetDisplayName(LOCTEXT("AdventurePlugin_DialogEditorName", "Dialog Editor"));
	//.SetGroup(WorkspaceMenuCategoryRef)
	//.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "GraphEditor.EventGraph_16x"));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AdventurePluginDialogEditorTabName, FOnSpawnTab::CreateRaw(this, &FAdventurePluginDialogEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("AdventurePlugin_DialogEditorName", "Dialog Editor"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FAdventurePluginDialogEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FAdventurePluginDialogEditorStyle::Shutdown();

	FAdventurePluginDialogEditorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AdventurePluginDialogEditorTabName);

	if (UObjectInitialized() && !IsRunningCommandlet())
	{
		// Unregister the level editor extensions
		{
			FAdventurePluginEditor& LevelEditor = FModuleManager::GetModuleChecked<FAdventurePluginEditor>(TEXT("AdventurePluginEditor"));
			LevelEditor.GetAllAdventurePluginEditorToolbarExtenders().RemoveAll([=](const FAdventurePluginEditor::FAdventurePluginEditorMenuExtender& Extender) { return Extender.GetHandle() == EditorMenuExtenderHandle; });
		}
	}
}

void FAdventurePluginDialogEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(AdventurePluginDialogEditorTabName);
}

void FAdventurePluginDialogEditorModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FAdventurePluginDialogEditorCommands::Get().OpenPluginWindow);
}

TSharedRef<SDockTab> FAdventurePluginDialogEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	if (!DialogEditor.IsValid())
	{
		DialogEditor = CreateDialogEditor(EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), NewObject<UObject>()); // Only temporary
	}
	return DialogEditor->GetPluginTab(SpawnTabArgs);
}

TSharedRef<FAdventurePluginDialogEditor> FAdventurePluginDialogEditorModule::CreateDialogEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* Object)
{
	TSharedRef<FAdventurePluginDialogEditor> NewDialogEditor(new FAdventurePluginDialogEditor());
	//NewDialogEditor->InitEditorForMaterial(Object);
	//OnMaterialEditorOpened().Broadcast(NewDialogEditor);
	NewDialogEditor->InitDialogEditor(Mode, InitToolkitHost, Object);
	return NewDialogEditor;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAdventurePluginDialogEditorModule, AdventurePluginDialogEditor)
