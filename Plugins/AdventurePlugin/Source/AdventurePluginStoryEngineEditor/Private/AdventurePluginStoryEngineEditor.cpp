// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TestEditorStandalone.h"
#include "TestEditorStandaloneStyle.h"
#include "TestEditorStandaloneCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName TestEditorStandaloneTabName("TestEditorStandalone");

#define LOCTEXT_NAMESPACE "FTestEditorStandaloneModule"

void FTestEditorStandaloneModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTestEditorStandaloneStyle::Initialize();
	FTestEditorStandaloneStyle::ReloadTextures();

	FTestEditorStandaloneCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTestEditorStandaloneCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FTestEditorStandaloneModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FTestEditorStandaloneModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FTestEditorStandaloneModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TestEditorStandaloneTabName, FOnSpawnTab::CreateRaw(this, &FTestEditorStandaloneModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FTestEditorStandaloneTabTitle", "TestEditorStandalone"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FTestEditorStandaloneModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FTestEditorStandaloneStyle::Shutdown();

	FTestEditorStandaloneCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TestEditorStandaloneTabName);
}

TSharedRef<SDockTab> FTestEditorStandaloneModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FTestEditorStandaloneModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("TestEditorStandalone.cpp"))
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

void FTestEditorStandaloneModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(TestEditorStandaloneTabName);
}

void FTestEditorStandaloneModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FTestEditorStandaloneCommands::Get().OpenPluginWindow);
}

void FTestEditorStandaloneModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FTestEditorStandaloneCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTestEditorStandaloneModule, TestEditorStandalone)