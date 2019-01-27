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
#include "AssetToolsModule.h"
#include "IAssetTypeActions.h"
#include "AssetTypeActions_DialogGraph.h"
#include "ClassIconFinder.h"
#include "SlateStyleRegistry.h"
#include "Styling/SlateStyle.h"
#include "PropertyEditorModule.h"
#include "PropertyEditorDelegates.h"
#include "Dialogue/Graph/DialogGraph.h"
#include "Dialogue/Graph/DialogGraphNode_Goto.h"
#include "Dialogue/Graph/DialogGraphNode_IfInInventory.h"
#include "Dialogue/Graph/DialogGraphNode_PlayAnimationBase.h"
#include "Dialogue/Structs/DialogGraphEntryPoint.h"
#include "Customizations/GotoCustomization.h"
#include "Customizations/DialogGraphCustomization.h"
#include "Customizations/DialogInventoryItemCustomization.h"
#include "Customizations/DialogGraphEntryPointCustomization.h"
#include "Customizations/AnimationCustomization.h"

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

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	FAdventurePluginEditor& AdventurePluginEditor = FAdventurePluginEditor::Get();
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_DialogGraph(AdventurePluginEditor.DefaultAssetCategory())));

	/* Adding custom asset icon */
	StyleSet = MakeShareable(new FSlateStyleSet("DialogStyle"));
	StyleSet->SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate"));
	StyleSet->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));
	StyleSet->Set("ClassIcon.DialogGraph", new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Icons/AssetIcons/BehaviorTree_16x.png")), FVector2D(16.0f, 16.0f)));
	StyleSet->Set("ClassThumbnail.DialogGraph", new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Icons/AssetIcons/BehaviorTree_64x.png")), FVector2D(64.0f, 64.0f)));
	//StyleSet->Set("ClassIcon.MyComponent", new FSlateImageBrush("path/to/MyComponent16.png", FVector2D(16.0f, 16.0f)));
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
	//FClassIconFinder::RegisterIconSource(&StyleSet.Get());
	/**/

	/* Registering custom property layouts */
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(UDialogGraph::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FDialogGraphCustomization::MakeInstance));
	PropertyModule.RegisterCustomClassLayout(UDialogGraphNode_Goto::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FGotoCustomization::MakeInstance));
	PropertyModule.RegisterCustomClassLayout(UDialogGraphNode_PlayAnimationBase::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FAnimationCustomization::MakeInstance));
	PropertyModule.RegisterCustomClassLayout(UDialogGraphNode_IfInInventory::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FDialogInventoryItemCustomization::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout(FDialogGraphEntryPoint::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDialogGraphEntryPointCustomization::MakeInstance));
	/**/
}

void FAdventurePluginDialogEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FAdventurePluginDialogEditorStyle::Shutdown();
	FAdventurePluginDialogEditorCommands::Unregister();

	/* Unregistering custom property layouts */
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout(UDialogGraph::StaticClass()->GetFName());
	PropertyModule.UnregisterCustomClassLayout(UDialogGraphNode_Goto::StaticClass()->GetFName());
	PropertyModule.UnregisterCustomClassLayout(UDialogGraphNode_PlayAnimationBase::StaticClass()->GetFName());
	PropertyModule.UnregisterCustomClassLayout(UDialogGraphNode_IfInInventory::StaticClass()->GetFName());
	PropertyModule.UnregisterCustomPropertyTypeLayout(FDialogGraphEntryPoint::StaticStruct()->GetFName());
	/**/

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AdventurePluginDialogEditorTabName);

	// Unregister all the asset types that we registered
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}

	if (UObjectInitialized() && !IsRunningCommandlet())
	{
		// Unregister the level editor extensions
		{
			FAdventurePluginEditor& LevelEditor = FModuleManager::GetModuleChecked<FAdventurePluginEditor>(TEXT("AdventurePluginEditor"));
			LevelEditor.GetAllAdventurePluginEditorToolbarExtenders().RemoveAll([=](const FAdventurePluginEditor::FAdventurePluginEditorMenuExtender& Extender) { return Extender.GetHandle() == EditorMenuExtenderHandle; });
		}
	}

	/* Removing custom asset icon */
	//FClassIconFinder::UnregisterIconSource(&StyleSet.Get());
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
	ensure(StyleSet.IsUnique());
	StyleSet.Reset();
	/**/
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

void FAdventurePluginDialogEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAdventurePluginDialogEditorModule, AdventurePluginDialogEditor)
