// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginInventoryEditor.h"
#include "AdventurePluginInventoryEditorStyle.h"
#include "AdventurePluginInventoryEditorCommands.h"
#include "InventoryItemBlueprint.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "BlueprintEditor.h" 
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

		// Add combination button to blueprints
		FBlueprintEditorModule& BPEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");

		BPEditorModule.OnGatherBlueprintMenuExtensions().AddStatic(&FAdventurePluginInventoryEditorModule::OnBlueprintGatherExtensions);
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

void FAdventurePluginInventoryEditorModule::OnBlueprintGatherExtensions(TSharedPtr<FExtender> Extender, UBlueprint* Blueprint)
{
	// Make sure this is inventoryItem blueprint
	if (Blueprint == nullptr || !Blueprint->GetClass()->IsChildOf<UInventoryItemBlueprint>())
	{
		return;
	}
	const FAdventurePluginInventoryEditorCommands& Commands = FAdventurePluginInventoryEditorCommands::Get();

	// This specific editor needs its own Command List with delegates that include the blueprint pointer
	TSharedPtr<FUICommandList> CommandList = MakeShareable(new FUICommandList);
	CommandList->MapAction(
		Commands.OpenPluginWindow,
		FExecuteAction::CreateStatic(
			&FAdventurePluginInventoryEditorModule::OnShowCombinationsList,
			Blueprint));

	Extender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		CommandList,
		FToolBarExtensionDelegate::CreateStatic(&FAdventurePluginInventoryEditorModule::ExtendItemBlueprintToolBar));
}

void FAdventurePluginInventoryEditorModule::ExtendItemBlueprintToolBar(class FToolBarBuilder& Builder)
{
	FSlateIcon IconBrush = FSlateIcon(
		FAdventurePluginInventoryEditorStyle::GetStyleSetName(),
		"AdventurePluginInventoryEditor.Combinations",
		"AdventurePluginInventoryEditor.Combinations.Small");

	const FAdventurePluginInventoryEditorCommands& Commands = FAdventurePluginInventoryEditorCommands::Get();
	Builder.AddToolBarButton(
		Commands.OpenPluginWindow,
		NAME_None,
		TAttribute<FText>(),
		TAttribute<FText>(),
		IconBrush,
		NAME_None);
}

void FAdventurePluginInventoryEditorModule::OnShowCombinationsList(UBlueprint* Blueprint)
{

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