
#include "AdventurePluginEditor.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "SlateApplication.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Framework/SlateDelegates.h"
#include "MessageLogModule.h"
#include "MessageLogInitializationOptions.h"
#include "LevelEditor.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_AdventureCharacter.h"
#include "AssetTypeActions_InventoryItem.h"
#include "InventoryItemBlueprint.h"
#include "AdventureCharacterBlueprint.h"
#include "IconThumbnailRenderer.h"
#include "GenericGraph/GenericGraphEditorStyle.h"
#include "SaveGame/AdventurePluginSaveGame.h"
#include "Inventory/Structs/UseActionType.h"
#include "Customizations/UseActionTypeCustomization.h"

#include "PropertyEditorModule.h"

#define LOCTEXT_NAMESPACE "AdventurePluginEditor"

IMPLEMENT_MODULE(FAdventurePluginEditor, AdventurePluginEditor)

const FName APLogName("AdventurePluginLog");

void FAdventurePluginEditor::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)

	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
	{
		FMessageLogInitializationOptions InitOptions;
		InitOptions.bShowFilters = true;
		MessageLogModule.RegisterLogListing(APLogName, LOCTEXT("AdventurePluginLog", "Adventure Plugin Log"), InitOptions);
	}

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AdventurePluginAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("AdventurePlugin")), LOCTEXT("AdventurePluginAssetCategory", "Adventure Plugin"));

	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_AdventureCharacter(AdventurePluginAssetCategory)));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_InventoryItem(AdventurePluginAssetCategory)));

	UThumbnailManager::Get().RegisterCustomRenderer(UAdventureCharacterBlueprint::StaticClass(), UIconThumbnailRenderer::StaticClass());
	UThumbnailManager::Get().RegisterCustomRenderer(UInventoryItemBlueprint::StaticClass(), UIconThumbnailRenderer::StaticClass());

	FGenericGraphEditorStyle::Initialize();

	RegisterSettings();

	// Registering custom property layouts
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout(FUseActionType::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FUseActionTypeCustomization::MakeInstance));
}

void FAdventurePluginEditor::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.


	if (UObjectInitialized())
	{
		UnregisterSettings();

		UThumbnailManager::Get().UnregisterCustomRenderer(UAdventureCharacterBlueprint::StaticClass());
		UThumbnailManager::Get().UnregisterCustomRenderer(UInventoryItemBlueprint::StaticClass());
	}

	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}

	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomPropertyTypeLayout(FUseActionType::StaticStruct()->GetFName());
	}

	FGenericGraphEditorStyle::Shutdown();

	if (FModuleManager::Get().IsModuleLoaded("MessageLog"))
	{
		FMessageLogModule& MessageLogModule = FModuleManager::GetModuleChecked<FMessageLogModule>("MessageLog");
		MessageLogModule.UnregisterLogListing(APLogName);
	}


}

void FAdventurePluginEditor::Log(const TSharedRef< class FTokenizedMessage >& Message) const
{
	if (GIsEditor)
	{
		FMessageLog SlateStyleLog("AdventurePluginLog");
		SlateStyleLog.AddMessage(Message);

		if (Message->GetSeverity() <= EMessageSeverity::Warning)
		{
			SlateStyleLog.Open();
		}
	}
}

void FAdventurePluginEditor::Log(EMessageSeverity::Type EngineMessageSeverity, const FText& Message) const
{
	if (GIsEditor)
	{
		FMessageLog SlateStyleLog("AdventurePluginLog");
		SlateStyleLog.AddMessage(FTokenizedMessage::Create(EngineMessageSeverity, Message));

		if (EngineMessageSeverity <= EMessageSeverity::Warning)
		{
			SlateStyleLog.Open();
		}
	}
}


// Callback for when the settings were saved.
bool FAdventurePluginEditor::HandleSettingsSaved()
{
	UAdventurePluginConfig* Settings = GetMutableDefault<UAdventurePluginConfig>();
	bool ResaveSettings = false;

	// You can put any validation code in here and resave the settings in case an invalid // value has been entered

	if (ResaveSettings)
	{
		Settings->SaveConfig();
	}

	return true;
}

void FAdventurePluginEditor::RegisterSettings()
{
	// Registering some settings is just a matter of exposing the default UObject of
	// your desired class, feel free to add here all those settings you want to expose
	// to your LDs or artists.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "AdventurePlugin",
			LOCTEXT("SettingsGeneralSectionName", "Adventure Plugin"),
			LOCTEXT("SettingsGeneralSectionDescription", "Base configuration for the Adventure Plugin"), GetMutableDefault<UAdventurePluginConfig>());

		// Register the save handler to your settings, you might want to use it to
		// validate those or just act to settings changes.
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FAdventurePluginEditor::HandleSettingsSaved);
		}
	}
}

void FAdventurePluginEditor::UnregisterSettings()
{
	// Ensure to unregister all of your registered settings here, hot-reload would
	// otherwise yield unexpected results.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "AdventurePlugin");
	}
}

void FAdventurePluginEditor::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

void FAdventurePluginEditor::RegisterEditorNodeForRuntimeNode(TSubclassOf<UGenericGraphNode> RuntimeNode, TSubclassOf<UEdNode_GenericGraphNode> EditorNode)
{
	EditorNodeMap.Add(RuntimeNode, EditorNode);
}

const TSubclassOf<UEdNode_GenericGraphNode>* FAdventurePluginEditor::FindEditorNodeForRuntimeNode(TSubclassOf<UGenericGraphNode> RuntimeNode) const
{
	const TSubclassOf<UEdNode_GenericGraphNode>* RegisteredEditorNode = EditorNodeMap.Find(RuntimeNode);
	if (RegisteredEditorNode != nullptr)
	{
		return RegisteredEditorNode;
	}

	const TSubclassOf<UGenericGraphNode>* ClosestRegisteredRuntimeNode = nullptr;
	const TSubclassOf<UEdNode_GenericGraphNode>* ClosestRegisteredEditorNode = nullptr;
	// This node was not explicitly registered. See if it inherits from some other registered node type.
	for (const TPair<TSubclassOf<UGenericGraphNode>, TSubclassOf<UEdNode_GenericGraphNode>>& RegisteredNode : EditorNodeMap)
	{
		if (RuntimeNode->IsChildOf(RegisteredNode.Key))
		{
			// The node type is compatible. But we want to find the parent the closest to the queried type in terms of inheritance. 
			// If we found some result we replace the already found result only if the current candidate inherits from the already found node, i.e. it is deeper in the inheritance tree.
			if (ClosestRegisteredRuntimeNode == nullptr || RegisteredNode.Key->IsChildOf(*ClosestRegisteredRuntimeNode))
			{
				ClosestRegisteredRuntimeNode = &RegisteredNode.Key;
				ClosestRegisteredEditorNode = &RegisteredNode.Value;
			}
		}
	}
	return ClosestRegisteredEditorNode;
}


#undef LOCTEXT_NAMESPACE