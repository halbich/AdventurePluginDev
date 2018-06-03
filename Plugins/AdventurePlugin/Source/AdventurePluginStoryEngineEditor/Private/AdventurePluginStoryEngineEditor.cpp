// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginStoryEngineEditor.h"
#include "AdventurePluginStoryEngineEditorStyle.h"
#include "AdventurePluginStoryEngineEditorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

//static const FName AdventurePluginStoryEngineEditorTabName("AdventurePluginStoryEngineEditor");
//
//#define LOCTEXT_NAMESPACE "FAdventurePluginStoryEngineEditorModule"
//
//void FAdventurePluginStoryEngineEditorModule::StartupModule()
//{
//	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
//	
//	FAdventurePluginStoryEngineEditorStyle::Initialize();
//	FAdventurePluginStoryEngineEditorStyle::ReloadTextures();
//
//	FAdventurePluginStoryEngineEditorCommands::Register();
//	
//	PluginCommands = MakeShareable(new FUICommandList);
//
//	PluginCommands->MapAction(
//		FAdventurePluginStoryEngineEditorCommands::Get().OpenPluginWindow,
//		FExecuteAction::CreateRaw(this, &FAdventurePluginStoryEngineEditorModule::PluginButtonClicked),
//		FCanExecuteAction());
//		
//	// Add to our toolbar menu
//	if (FAdventurePluginEditor::IsAvailable())
//	{
//		EditorMenuExtender = FAdventurePluginEditor::FAdventurePluginEditorMenuExtender::CreateRaw(this, &FAdventurePluginStoryEngineEditorModule::OnExtendLevelEditorViewMenu);
//
//		FAdventurePluginEditor& ape = FAdventurePluginEditor::Get();
//		auto& MenuExtenders = ape.GetAllAdventurePluginEditorToolbarExtenders();
//		MenuExtenders.Add(EditorMenuExtender);
//		EditorMenuExtenderHandle = MenuExtenders.Last().GetHandle();
//	}
//	
//
//	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AdventurePluginStoryEngineEditorTabName, FOnSpawnTab::CreateRaw(this, &FAdventurePluginStoryEngineEditorModule::OnSpawnPluginTab))
//		.SetDisplayName(LOCTEXT("FAdventurePluginStoryEngineEditorTabTitle", "AdventurePluginStoryEngineEditor"))
//		.SetMenuType(ETabSpawnerMenuType::Hidden);
//}
//
//void FAdventurePluginStoryEngineEditorModule::ShutdownModule()
//{
//	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
//	// we call this function before unloading the module.
//	FAdventurePluginStoryEngineEditorStyle::Shutdown();
//
//	FAdventurePluginStoryEngineEditorCommands::Unregister();
//
//	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AdventurePluginStoryEngineEditorTabName);
//
//	if (UObjectInitialized() && !IsRunningCommandlet())
//	{
//		// Unregister the level editor extensions
//		{
//			FAdventurePluginEditor& LevelEditor = FModuleManager::GetModuleChecked<FAdventurePluginEditor>(TEXT("AdventurePluginEditor"));
//			LevelEditor.GetAllAdventurePluginEditorToolbarExtenders().RemoveAll([=](const FAdventurePluginEditor::FAdventurePluginEditorMenuExtender& Extender) { return Extender.GetHandle() == EditorMenuExtenderHandle; });
//		}
//	}
//}
//
//TSharedRef<SDockTab> FAdventurePluginStoryEngineEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
//{
//	FText WidgetText = FText::Format(
//		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
//		FText::FromString(TEXT("FAdventurePluginStoryEngineEditorModule::OnSpawnPluginTab")),
//		FText::FromString(TEXT("AdventurePluginStoryEngineEditor.cpp"))
//		);
//
//	return SNew(SDockTab)
//		.TabRole(ETabRole::NomadTab)
//		[
//			// Put your tab content here!
//			SNew(SBox)
//			.HAlign(HAlign_Center)
//			.VAlign(VAlign_Center)
//			[
//				SNew(STextBlock)
//				.Text(WidgetText)
//			]
//		];
//}
//
//void FAdventurePluginStoryEngineEditorModule::PluginButtonClicked()
//{
//	FGlobalTabmanager::Get()->InvokeTab(AdventurePluginStoryEngineEditorTabName);
//}
//
//void FAdventurePluginStoryEngineEditorModule::AddMenuExtension(FMenuBuilder& Builder)
//{
//	Builder.AddMenuEntry(FAdventurePluginStoryEngineEditorCommands::Get().OpenPluginWindow);
//}
//
//#undef LOCTEXT_NAMESPACE
//	
//IMPLEMENT_MODULE(FAdventurePluginStoryEngineEditorModule, AdventurePluginStoryEngineEditor)