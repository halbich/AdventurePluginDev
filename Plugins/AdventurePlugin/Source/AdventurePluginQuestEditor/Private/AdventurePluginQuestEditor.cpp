#include "AdventurePluginQuestEditor.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ContentBrowserModule.h"
#include "ContentBrowserDelegates.h"
#include "AssetToolsModule.h"
#include "PropertyEditorModule.h"
#include "PropertyEditorDelegates.h"
#include "AdventurePluginEditor.h"
#include "AssetTypeActions_QuestGraph.h"
#include "Quest/Structs/QuestGraphFlag.h"
#include "Quest/Structs/QuestGraphBool.h"
#include "Quest/Structs/QuestGraphString.h"
#include "Quest/Structs/QuestGraphInteger.h"
#include "Quest/Structs/QuestGraphEvent.h"
#include "Graph/EdQuestNode_NoOutput.h"
#include "Quest/Graph/QuestGraphNode_End.h"
#include "Quest/Graph/QuestGraphNode_Inventory.h"
#include "Customizations/QuestGraphFlagCustomization.h"
#include "Customizations/QuestGraphBoolCustomization.h"
#include "Customizations/QuestGraphStringCustomization.h"
#include "Customizations/QuestGraphIntegerCustomization.h"
#include "Customizations/QuestGraphEventCustomization.h"
#include "Customizations/QuestInventoryItemCustomization.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateStyle.h"

#define LOCTEXT_NAMESPACE "FAdventurePluginQuestEditor"

void FAdventurePluginQuestEditor::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	FAdventurePluginEditor& AdventurePluginEditor = FAdventurePluginEditor::Get();
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_QuestGraph(AdventurePluginEditor.DefaultAssetCategory())));

	/* Registering editor nodes for runtime nodes */
	AdventurePluginEditor.RegisterEditorNodeForRuntimeNode(UQuestGraphNode_End::StaticClass(), UEdQuestNode_NoOutput::StaticClass());

	/* Adding custom asset icon */
	StyleSet = MakeShareable(new FSlateStyleSet("QuestStyle"));
	StyleSet->SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate"));
	StyleSet->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));
	StyleSet->Set("ClassIcon.QuestGraph", new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Icons/AssetIcons/BehaviorTree_16x.png")), FVector2D(16.0f, 16.0f)));
	StyleSet->Set("ClassThumbnail.QuestGraph", new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Icons/AssetIcons/BehaviorTree_64x.png")), FVector2D(64.0f, 64.0f)));
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());

	/* Registering custom property layouts */
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(UQuestGraphNode_Inventory::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FQuestInventoryItemCustomization::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout(FQuestGraphFlag::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FQuestGraphFlagCustomization::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout(FQuestGraphBool::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FQuestGraphBoolCustomization::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout(FQuestGraphInteger::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FQuestGraphIntegerCustomization::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout(FQuestGraphString::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FQuestGraphStringCustomization::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout(FQuestGraphEvent::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FQuestGraphEventCustomization::MakeInstance));
	/**/
}

void FAdventurePluginQuestEditor::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	/* Unregistering custom property layouts */
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout(UQuestGraphNode_Inventory::StaticClass()->GetFName());
	PropertyModule.UnregisterCustomPropertyTypeLayout(FQuestGraphFlag::StaticStruct()->GetFName());
	PropertyModule.UnregisterCustomPropertyTypeLayout(FQuestGraphBool::StaticStruct()->GetFName());
	PropertyModule.UnregisterCustomPropertyTypeLayout(FQuestGraphInteger::StaticStruct()->GetFName());
	PropertyModule.UnregisterCustomPropertyTypeLayout(FQuestGraphString::StaticStruct()->GetFName());
	PropertyModule.UnregisterCustomPropertyTypeLayout(FQuestGraphEvent::StaticStruct()->GetFName());
	/**/

	// Unregister all the asset types that we registered
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}

	/* Removing custom asset icon */
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
	ensure(StyleSet.IsUnique());
	StyleSet.Reset();
	/**/
}

void FAdventurePluginQuestEditor::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAdventurePluginQuestEditor, AdventurePluginQuestEditor)