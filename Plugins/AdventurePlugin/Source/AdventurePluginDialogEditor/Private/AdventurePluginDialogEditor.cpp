// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginDialogEditor.h"
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
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FAdventurePluginDialogEditorModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FAdventurePluginDialogEditorModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
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
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void FAdventurePluginDialogEditorModule::CreateInternalWidgets()
{
	GraphEditor = CreateGraphEditorWidget();
	// Manually set zoom level to avoid deferred zooming
	GraphEditor->SetViewLocation(FVector2D::ZeroVector, 1);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void FAdventurePluginDialogEditorModule::DummyAction() { }

bool FAdventurePluginDialogEditorModule::CanDummyAction() const { return true; }

TSharedRef<SGraphEditor> FAdventurePluginDialogEditorModule::CreateGraphEditorWidget()
{
	GraphEditorCommands = MakeShareable(new FUICommandList);
	{
		// Editing commands
		GraphEditorCommands->MapAction(FGenericCommands::Get().SelectAll,
				FExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditorModule::DummyAction),
				FCanExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditorModule::CanDummyAction)
				 );

		GraphEditorCommands->MapAction(FGenericCommands::Get().Delete,
				FExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditorModule::DummyAction),
				FCanExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditorModule::CanDummyAction)
				 );

		GraphEditorCommands->MapAction(FGenericCommands::Get().Copy,
				FExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditorModule::DummyAction),
				FCanExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditorModule::CanDummyAction)
				 );

		GraphEditorCommands->MapAction(FGenericCommands::Get().Paste,
				FExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditorModule::DummyAction),
				FCanExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditorModule::CanDummyAction)
				 );

		GraphEditorCommands->MapAction(FGenericCommands::Get().Cut,
				FExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditorModule::DummyAction),
				FCanExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditorModule::CanDummyAction)
				 );
		
		GraphEditorCommands->MapAction(FGenericCommands::Get().Duplicate,
				FExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditorModule::DummyAction),
				FCanExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditorModule::CanDummyAction)
				 );
	}

	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("AdventurePlugin_DialogEditor", "DIALOG EDITOR");
	SGraphEditor::FGraphEditorEvents InEvents;
	UMaterial * Obj = NewObject<UMaterial>(); // TODO totally must be changed from UMaterial!
	UEdGraph * Graph = CastChecked<UEdGraph>(FBlueprintEditorUtils::CreateNewGraph(Obj, NAME_None, UEdGraph::StaticClass(), UEdGraphSchema::StaticClass()));
	
	// Create the title bar widget
	//TSharedPtr<SWidget> TitleBarWidget = SNew(SMaterialEditorTitleBar)
	//	.TitleText(this, &FMaterialEditor::GetOriginalObjectName);
		
	return SNew(SGraphEditor)
		.AdditionalCommands(GraphEditorCommands)
		.IsEditable(true)
		.TitleBar(TSharedPtr<SWidget>())
		.Appearance(AppearanceInfo)
		.GraphToEdit(Graph)
		.GraphEvents(InEvents)
		.ShowGraphStateOverlay(false);
}

TSharedRef<SDockTab> FAdventurePluginDialogEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	//TSharedRef<SDockTab> dt = SNew(SDockTab).TabRole(ETabRole::NomadTab);
	//dt->SetContent(GraphEditor.ToSharedRef());
	//return dt;

	CreateInternalWidgets();
	
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			GraphEditor.ToSharedRef()
			//Put your tab content here!
			//SNew(SBox)
			//.HAlign(HAlign_Center)
			//.VAlign(VAlign_Center)
			//[
			//	//GraphEditor.ToSharedRef()
			//	SNew(STextBlock)
			//	.Text(WidgetText)
			//]
		];
	
}

void FAdventurePluginDialogEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(AdventurePluginDialogEditorTabName);
}

void FAdventurePluginDialogEditorModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FAdventurePluginDialogEditorCommands::Get().OpenPluginWindow);
}

void FAdventurePluginDialogEditorModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FAdventurePluginDialogEditorCommands::Get().OpenPluginWindow);
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAdventurePluginDialogEditorModule, AdventurePluginDialogEditor)