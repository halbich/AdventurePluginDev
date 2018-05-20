
#include "AdventurePluginEditorToolBar.h"
#include "Modules/ModuleManager.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "AdventurePluginEditor.h"
#include "AdventurePluginEditorStyle.h"

TSharedRef< SWidget > FAdventurePluginEditorToolBar::GeneratePluginMenu(TSharedRef<FUICommandList> InCommandList)
{
#define LOCTEXT_NAMESPACE "AdventurePluginEditorToolBarViewMenu"



	// Get all menu extenders for this context menu from the level editor module
	FAdventurePluginEditor& LevelEditorModule = FAdventurePluginEditor::Get();


	TArray<FAdventurePluginEditor::FAdventurePluginEditorMenuExtender> MenuExtenderDelegates = LevelEditorModule.GetAllAdventurePluginEditorToolbarExtenders();

	TArray<TSharedPtr<FExtender>> Extenders;
	for (int32 i = 0; i < MenuExtenderDelegates.Num(); ++i)
	{
		if (MenuExtenderDelegates[i].IsBound())
		{
			Extenders.Add(MenuExtenderDelegates[i].Execute(InCommandList));
		}
	}

	auto extenders = LevelEditorModule.GetToolBarExtensibilityManager()->GetAllExtenders();
	Extenders.Add(extenders);

	TSharedPtr<FExtender> MenuExtender = FExtender::Combine(Extenders);

	const bool bShouldCloseWindowAfterMenuSelection = true;
	FMenuBuilder MenuBuilder(bShouldCloseWindowAfterMenuSelection, InCommandList, MenuExtender);

	struct Local
	{
		static void OpenSettings(FName ContainerName, FName CategoryName, FName SectionName)
		{
			//FModuleManager::LoadModuleChecked<ISettingsModule>("Settings").ShowViewer(ContainerName, CategoryName, SectionName);
		}
	};

	MenuBuilder.BeginSection("AdventurePluginEditorTabs", LOCTEXT("Adventure Plugin", "Adventure Plugin Tabs"));
	
	MenuBuilder.AddMenuSeparator();
	MenuBuilder.EndSection();

	MenuBuilder.BeginSection("OtherSection", LOCTEXT("other", "other"));
	{

		//MenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().WorldProperties);

		MenuBuilder.AddMenuEntry(
			LOCTEXT("ProjectSettingsMenuLabel", "Project Settings..."),
			LOCTEXT("ProjectSettingsMenuToolTip", "Change the settings of the currently loaded project"),
			FSlateIcon(FAdventurePluginEditorStyle::GetStyleSetName(), "ProjectSettings.TabIcon"),
			FUIAction(FExecuteAction::CreateStatic(&Local::OpenSettings, FName("Project"), FName("Project"), FName("General")))
		);

		/*if (IModularFeatures::Get().IsModularFeatureAvailable(EditorFeatures::PluginsEditor))
		{
		FGlobalTabmanager::Get()->PopulateTabSpawnerMenu(MenuBuilder, "PluginsEditor");
		}*/
	}
	MenuBuilder.EndSection();

	//MenuBuilder.BeginSection("LevelEditorSelection", LOCTEXT("SelectionHeading", "Selection"));
	//{
	//	MenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().AllowTranslucentSelection);
	//	MenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().AllowGroupSelection);
	//	MenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().StrictBoxSelect);
	//	MenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().TransparentBoxSelect);
	//	MenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().ShowTransformWidget);
	//}
	//MenuBuilder.EndSection();

	//MenuBuilder.BeginSection("LevelEditorScalability", LOCTEXT("ScalabilityHeading", "Scalability"));
	//{
	//	MenuBuilder.AddSubMenu(
	//		LOCTEXT("ScalabilitySubMenu", "Engine Scalability Settings"),
	//		LOCTEXT("ScalabilitySubMenu_ToolTip", "Open the engine scalability settings"),
	//		FNewMenuDelegate::CreateStatic(&MakeScalabilityMenu));

	//	MenuBuilder.AddSubMenu(
	//		LOCTEXT("MaterialQualityLevelSubMenu", "Material Quality Level"),
	//		LOCTEXT("MaterialQualityLevelSubMenu_ToolTip", "Sets the value of the CVar \"r.MaterialQualityLevel\" (low=0, high=1, medium=2). This affects materials via the QualitySwitch material expression."),
	//		FNewMenuDelegate::CreateStatic(&MakeMaterialQualityLevelMenu));

	//	MenuBuilder.AddSubMenu(
	//		LOCTEXT("FeatureLevelPreviewSubMenu", "Preview Rendering Level"),
	//		LOCTEXT("FeatureLevelPreviewSubMenu_ToolTip", "Sets the rendering level used by the main editor"),
	//		FNewMenuDelegate::CreateStatic(&MakeShaderModelPreviewMenu));
	//}
	//MenuBuilder.EndSection();

	//MenuBuilder.BeginSection("LevelEditorAudio", LOCTEXT("AudioHeading", "Real Time Audio"));
	//{
	//	TSharedRef<SWidget> VolumeItem = SNew(SHorizontalBox)
	//		+ SHorizontalBox::Slot()
	//		.FillWidth(0.9f)
	//		.Padding(FMargin(2.0f, 0.0f, 0.0f, 0.0f))
	//		[
	//			SNew(SVolumeControl)
	//			.ToolTipText_Static(&FLevelEditorActionCallbacks::GetAudioVolumeToolTip)
	//		.Volume_Static(&FLevelEditorActionCallbacks::GetAudioVolume)
	//		.OnVolumeChanged_Static(&FLevelEditorActionCallbacks::OnAudioVolumeChanged)
	//		.Muted_Static(&FLevelEditorActionCallbacks::GetAudioMuted)
	//		.OnMuteChanged_Static(&FLevelEditorActionCallbacks::OnAudioMutedChanged)
	//		]
	//	+ SHorizontalBox::Slot()
	//		.FillWidth(0.1f);

	//	MenuBuilder.AddWidget(VolumeItem, LOCTEXT("VolumeControlLabel", "Volume"));
	//}
	//MenuBuilder.EndSection();

	//MenuBuilder.BeginSection("Snapping", LOCTEXT("SnappingHeading", "Snapping"));
	//{
	//	MenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().EnableActorSnap);
	//	TSharedRef<SWidget> SnapItem =
	//		SNew(SHorizontalBox)
	//		+ SHorizontalBox::Slot()
	//		.FillWidth(0.9f)
	//		[
	//			SNew(SSlider)
	//			.ToolTipText_Static(&FLevelEditorActionCallbacks::GetActorSnapTooltip)
	//		.Value_Static(&FLevelEditorActionCallbacks::GetActorSnapSetting)
	//		.OnValueChanged_Static(&FLevelEditorActionCallbacks::SetActorSnapSetting)
	//		]
	//	+ SHorizontalBox::Slot()
	//		.FillWidth(0.1f);
	//	MenuBuilder.AddWidget(SnapItem, LOCTEXT("ActorSnapLabel", "Distance"));

	//	MenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().ToggleSocketSnapping);
	//	MenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().EnableVertexSnap);
	//}
	//MenuBuilder.EndSection();

	//MenuBuilder.BeginSection("LevelEditorViewport", LOCTEXT("ViewportHeading", "Viewport"));
	//{
	//	MenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().ToggleHideViewportUI);

	//	MenuBuilder.AddSubMenu(LOCTEXT("PreviewMenu", "Previewing"), LOCTEXT("PreviewMenuTooltip", "Game Preview Settings"), FNewMenuDelegate::CreateStatic(&MakePreviewSettingsMenu));
	//}
	//MenuBuilder.EndSection();

#undef LOCTEXT_NAMESPACE

	return MenuBuilder.MakeWidget();
}

