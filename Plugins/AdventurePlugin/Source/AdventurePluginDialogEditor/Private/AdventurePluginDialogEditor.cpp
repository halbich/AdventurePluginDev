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
//#include "Toolkits/SStandaloneAssetEditorToolkitHost.h"

static const FName AdventurePluginDialogEditorTabName("AdventurePluginDialogEditor");
const FName FAdventurePluginDialogEditorModule::GraphCanvasTabId(TEXT("DialogEditor_GraphCanvas"));
const FName DialogEditorAppIdentifier = FName(TEXT("DialogEditorApp"));

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

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void FAdventurePluginDialogEditorModule::CreateInternalWidgets()
{
	GraphEditor = CreateGraphEditorWidget();
	// Manually set zoom level to avoid deferred zooming
	GraphEditor->SetViewLocation(FVector2D::ZeroVector, 1);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FName FAdventurePluginDialogEditorModule::GetToolkitFName() const
{ 
	return FName("DialogEditor");
}

FText FAdventurePluginDialogEditorModule::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Dialog Editor");
}

FString FAdventurePluginDialogEditorModule::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "Dialog ").ToString();
}

FLinearColor FAdventurePluginDialogEditorModule::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

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

void FAdventurePluginDialogEditorModule::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_DialogEditor", "Dialog Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(GraphCanvasTabId, FOnSpawnTab::CreateSP(this, &FAdventurePluginDialogEditorModule::SpawnTab_GraphCanvas))
		.SetDisplayName(LOCTEXT("GraphCanvasTab", "Graph"))
		.SetGroup(WorkspaceMenuCategoryRef);
		//.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "GraphEditor.EventGraph_16x"));

	//OnRegisterTabSpawners().Broadcast(InTabManager);
}


void FAdventurePluginDialogEditorModule::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(GraphCanvasTabId);

	//OnUnregisterTabSpawners().Broadcast(InTabManager);
}

TSharedRef<SDockTab> FAdventurePluginDialogEditorModule::SpawnTab_GraphCanvas(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.Label(LOCTEXT("GraphCanvasTitle", "Graph"));

	if (GraphEditor.IsValid())
	{
		SpawnedTab->SetContent(GraphEditor.ToSharedRef());
	}

	return SpawnedTab;
}

TSharedRef<SDockTab> FAdventurePluginDialogEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	CreateInternalWidgets();
	
	/*
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_DialogEditor_Layout_v10")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->SetHideTabWell(true)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.9f)
				->SetHideTabWell(true)
				->AddTab(GraphCanvasTabId, ETabState::OpenedTab)
			)
		);

	// Add the preview material to the objects being edited, so that we can find this editor from the temporary material graph
	EToolkitMode::Type Mode = EToolkitMode::Standalone;
	TSharedPtr<IToolkitHost> InitToolkitHost = TSharedPtr<IToolkitHost>();
	TArray<UObject*> ObjectsToEdit;
	//ObjectsToEdit.Add(ObjectToEdit);
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, DialogEditorAppIdentifier, StandaloneDefaultLayout, true, true, ObjectsToEdit, false);

	TSharedPtr<SDockTab> NewTab = SNew(SDockTab).TabRole(ETabRole::NomadTab);
	const TSharedRef<FTabManager> NewTabManager = FGlobalTabmanager::Get()->NewTabManager(NewTab.ToSharedRef());
	TSharedPtr<SStandaloneAssetEditorToolkitHost> NewStandaloneHost;
	NewTab->SetContent
	(
		SAssignNew(NewStandaloneHost, SStandaloneAssetEditorToolkitHost, NewTabManager, DialogEditorAppIdentifier)
		.OnRequestClose(this, &FAssetEditorToolkit::OnRequestClose)
	);
	return NewTab.ToSharedRef();
	*/
	
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

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAdventurePluginDialogEditorModule, AdventurePluginDialogEditor)