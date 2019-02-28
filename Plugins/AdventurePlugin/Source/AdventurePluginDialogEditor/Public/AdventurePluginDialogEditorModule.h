
#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "Misc/NotifyHook.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Math/Color.h"
#include "AdventurePluginEditor.h"
#include "IAssetTools.h"
#include "Styling/SlateStyle.h"

class FMenuBuilder;
class SGraphEditor;
/**
* The module registers customizations and the asset editor.
*/
class FAdventurePluginDialogEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

private:
	TSharedPtr<FSlateStyleSet> StyleSet;
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;

	/**	The tab ids for the dialog editor */
	static const FName GraphCanvasTabId;
};