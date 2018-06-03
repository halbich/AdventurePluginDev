// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginStoryEngineEditorModule.h"
//#include "AdventurePluginStoryEngineEditorStyle.h"
//#include "AdventurePluginStoryEngineEditorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "ContentBrowserModule.h"
//#include "EditorStyleSet.h"
#include "ContentBrowserDelegates.h"

const FName AdventurePluginStoryEngineEditorAppIdentifier = FName(TEXT("AdventurePluginStoryEngineEditorApp"));

//static const FName AdventurePluginStoryEngineEditorTabName("AdventurePluginStoryEngineEditor");

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

/**
* Material editor module
*/
class FAdventurePluginStoryEngineEditorModule : public IAdventurePluginStoryEngineEditorModule
{
public:
	/** Constructor, set up console commands and variables **/
	FAdventurePluginStoryEngineEditorModule()
	{
	}

	/**
	* Called right after the module DLL has been loaded and the module object has been created
	*/
	virtual void StartupModule() override
	{
		/*MenuExtensibilityManager = MakeShareable(new FExtensibilityManager);
		ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);*/

		//if (!FEngineBuildSettings::IsInternalBuild() && !FEngineBuildSettings::IsSourceDistribution())
		//{
		//	TSharedPtr<IPlugin> SubstancePlugin = IPluginManager::Get().FindPlugin(TEXT("Substance"));
		//	if (!SubstancePlugin.IsValid())
		//	{
		//		// Extend content browser menu
		//		{
		//			FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
		//			ContentBrowserModule.GetAllAssetContextMenuExtenders().Add(FContentBrowserMenuExtender_SelectedPaths::CreateRaw(this, &FMaterialEditorModule::ExtendContentBrowserAssetContextMenu));
		//			ContentBrowserAssetExtenderDelegateHandle = ContentBrowserModule.GetAllAssetContextMenuExtenders().Last().GetHandle();
		//		}

		//		// Extend material editor toolbar
		//		{

		//			TSharedRef<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		//			ToolbarExtender->AddToolBarExtension("Graph", EExtensionHook::After, nullptr,
		//				FToolBarExtensionDelegate::CreateLambda([this](FToolBarBuilder& ToolbarBuilder)
		//			{
		//				ToolbarBuilder.BeginSection("Substance");
		//				ToolbarBuilder.AddToolBarButton(
		//					FUIAction(FExecuteAction::CreateRaw(this, &FMaterialEditorModule::OpenSubstancePluginGetter)),
		//					NAME_None,
		//					NSLOCTEXT("MaterialEditor", "GetContentText_SubstanceToolbar", "Substance"),
		//					NSLOCTEXT("MaterialEditor", "GetContentText_Substance", "Add Substance textures to the project"),
		//					FSlateIcon(FEditorStyle::GetStyleSetName(), "MaterialEditor.AddSubstanceSpecialToolbar")
		//				);
		//				ToolbarBuilder.EndSection();
		//			})
		//			);

		//			ToolBarExtensibilityManager->AddExtender(ToolbarExtender);
		//		}
		//	}
		//}

	}

	/*TSharedRef<FExtender> ExtendContentBrowserAssetContextMenu(const TArray<FString>& SelectedPaths)
	{
		TSharedRef<FExtender> Extender = MakeShared<FExtender>();
		Extender->AddMenuExtension(
			"ContentBrowserNewBasicAsset",
			EExtensionHook::After,
			TSharedPtr<FUICommandList>(),
			FMenuExtensionDelegate::CreateRaw(this, &FMaterialEditorModule::ContentBrowserExtenderFunc, SelectedPaths)
		);
		return Extender;
	}

	void ContentBrowserExtenderFunc(FMenuBuilder& MenuBuilder, const TArray<FString> SelectedPaths)
	{
		MenuBuilder.AddMenuEntry(
			FUIAction(FExecuteAction::CreateRaw(this, &FMaterialEditorModule::OpenSubstancePluginGetter)),
			SNew(SNewSubstanceMenuEntry).Icon(FEditorStyle::GetBrush("MaterialEditor.AddSubstanceSpecialMenu"))
		);
	}

	void OpenSubstancePluginGetter()
	{
		TSharedPtr<SWindow> Window = nullptr;
		TSharedPtr<SWidget> Widget = FSlateApplication::Get().GetKeyboardFocusedWidget();
		if (Widget.IsValid())
		{
			Window = FSlateApplication::Get().FindWidgetWindow(Widget.ToSharedRef());
		}

		IIntroTutorials::Get().LaunchTutorial(TEXT("/Engine/Tutorial/SubEditors/GettingSubstance"), Window);
	}*/

	/**
	* Called before the module is unloaded, right before the module object is destroyed.
	*/
	virtual void ShutdownModule() override
	{
		/*MenuExtensibilityManager.Reset();
		ToolBarExtensibilityManager.Reset();*/

		if (FModuleManager::Get().IsModuleLoaded(TEXT("ContentBrowser")))
		{
			FContentBrowserModule& ContentBrowserModule = FModuleManager::GetModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
			ContentBrowserModule.GetAllAssetContextMenuExtenders().RemoveAll([this](const auto& Delegate) { return Delegate.GetHandle() == ContentBrowserAssetExtenderDelegateHandle; });
		}
	}

	/**
	* Creates a new material editor, either for a material or a material function
	*/
	/*virtual TSharedRef<IMaterialEditor> CreateMaterialEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMaterial* Material) override
	{
		TSharedRef<FMaterialEditor> NewMaterialEditor(new FMaterialEditor());
		NewMaterialEditor->InitEditorForMaterial(Material);
		OnMaterialEditorOpened().Broadcast(NewMaterialEditor);
		NewMaterialEditor->InitMaterialEditor(Mode, InitToolkitHost, Material);
		return NewMaterialEditor;
	}

	virtual TSharedRef<IMaterialEditor> CreateMaterialEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMaterialFunction* MaterialFunction) override
	{
		TSharedRef<FMaterialEditor> NewMaterialEditor(new FMaterialEditor());
		NewMaterialEditor->InitEditorForMaterialFunction(MaterialFunction);
		OnMaterialFunctionEditorOpened().Broadcast(NewMaterialEditor);
		NewMaterialEditor->InitMaterialEditor(Mode, InitToolkitHost, MaterialFunction);
		return NewMaterialEditor;
	}

	virtual TSharedRef<IMaterialEditor> CreateMaterialInstanceEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMaterialInstance* MaterialInstance) override
	{
		TSharedRef<FMaterialInstanceEditor> NewMaterialInstanceEditor(new FMaterialInstanceEditor());
		NewMaterialInstanceEditor->InitEditorForMaterial(MaterialInstance);
		OnMaterialInstanceEditorOpened().Broadcast(NewMaterialInstanceEditor);
		NewMaterialInstanceEditor->InitMaterialInstanceEditor(Mode, InitToolkitHost, MaterialInstance);
		return NewMaterialInstanceEditor;
	}

	virtual TSharedRef<IMaterialEditor> CreateMaterialInstanceEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMaterialFunctionInstance* MaterialFunction) override
	{
		TSharedRef<FMaterialInstanceEditor> NewMaterialInstanceEditor(new FMaterialInstanceEditor());
		NewMaterialInstanceEditor->InitEditorForMaterialFunction(MaterialFunction);
		OnMaterialInstanceEditorOpened().Broadcast(NewMaterialInstanceEditor);
		NewMaterialInstanceEditor->InitMaterialInstanceEditor(Mode, InitToolkitHost, MaterialFunction);
		return NewMaterialInstanceEditor;
	}*/

	/*virtual void GetVisibleMaterialParameters(const class UMaterial* Material, class UMaterialInstance* MaterialInstance, TArray<FMaterialParameterInfo>& VisibleExpressions) override
	{
		FMaterialEditorUtilities::GetVisibleMaterialParameters(Material, MaterialInstance, VisibleExpressions);
	}

	virtual bool MaterialLayersEnabled()
	{
		static auto* CVar = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.SupportMaterialLayers"));
		return CVar && CVar->GetValueOnAnyThread() == 1;
	};*/

	/** Gets the extensibility managers for outside entities to extend material editor's menus and toolbars */
	//virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override { return MenuExtensibilityManager; }
	//virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override { return ToolBarExtensibilityManager; }

private:
	/*TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;
	TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;
	*/
	FDelegateHandle ContentBrowserAssetExtenderDelegateHandle;
};
	
IMPLEMENT_MODULE(FAdventurePluginStoryEngineEditorModule, AdventurePluginStoryEngineEditor)