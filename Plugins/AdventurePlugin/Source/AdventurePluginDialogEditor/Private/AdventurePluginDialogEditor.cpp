// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginDialogEditor.h"
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

const FName FAdventurePluginDialogEditor::GraphCanvasTabId(TEXT("DialogEditor_GraphCanvas"));
const FName DialogEditorAppIdentifier = FName(TEXT("DialogEditorApp"));

#define LOCTEXT_NAMESPACE "FAdventurePluginDialogEditor"

void FAdventurePluginDialogEditor::InitDialogEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit)
{
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

	// if we are already editing objects, dont try to recreate the editor from scratch
	const TArray<UObject*>* EditedObjects = GetObjectsCurrentlyBeingEdited();
	if (EditedObjects == nullptr || EditedObjects->Num() == 0)
	{
		FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, DialogEditorAppIdentifier, StandaloneDefaultLayout, true, true, ObjectToEdit, false);
	}
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void FAdventurePluginDialogEditor::CreateInternalWidgets()
{
	GraphEditor = CreateGraphEditorWidget();
	// Manually set zoom level to avoid deferred zooming
	GraphEditor->SetViewLocation(FVector2D::ZeroVector, 1);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FName FAdventurePluginDialogEditor::GetToolkitFName() const
{
	return FName("DialogEditor");
}

FText FAdventurePluginDialogEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Dialog Editor");
}

FString FAdventurePluginDialogEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "Dialog ").ToString();
}

FLinearColor FAdventurePluginDialogEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

void FAdventurePluginDialogEditor::DummyAction() { }

bool FAdventurePluginDialogEditor::CanDummyAction() const { return true; }

TSharedRef<SGraphEditor> FAdventurePluginDialogEditor::CreateGraphEditorWidget()
{
	GraphEditorCommands = MakeShareable(new FUICommandList);
	{
		// Editing commands
		GraphEditorCommands->MapAction(FGenericCommands::Get().SelectAll,
			FExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditor::DummyAction),
			FCanExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditor::CanDummyAction)
		);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Delete,
			FExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditor::DummyAction),
			FCanExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditor::CanDummyAction)
		);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Copy,
			FExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditor::DummyAction),
			FCanExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditor::CanDummyAction)
		);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Paste,
			FExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditor::DummyAction),
			FCanExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditor::CanDummyAction)
		);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Cut,
			FExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditor::DummyAction),
			FCanExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditor::CanDummyAction)
		);

		GraphEditorCommands->MapAction(FGenericCommands::Get().Duplicate,
			FExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditor::DummyAction),
			FCanExecuteAction::CreateRaw(this, &FAdventurePluginDialogEditor::CanDummyAction)
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

void FAdventurePluginDialogEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_DialogEditor", "Dialog Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(GraphCanvasTabId, FOnSpawnTab::CreateSP(this, &FAdventurePluginDialogEditor::SpawnTab_GraphCanvas))
		.SetDisplayName(LOCTEXT("GraphCanvasTab", "Graph"))
		.SetGroup(WorkspaceMenuCategoryRef);

}


void FAdventurePluginDialogEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(GraphCanvasTabId);

}

TSharedRef<SDockTab> FAdventurePluginDialogEditor::SpawnTab_GraphCanvas(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.Label(LOCTEXT("GraphCanvasTitle", "Graph"));

	if (GraphEditor.IsValid())
	{
		SpawnedTab->SetContent(GraphEditor.ToSharedRef());
	}

	return SpawnedTab;
}

TSharedRef<SDockTab> FAdventurePluginDialogEditor::GetPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	CreateInternalWidgets();


	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			GraphEditor.ToSharedRef()
		];

}

#undef LOCTEXT_NAMESPACE