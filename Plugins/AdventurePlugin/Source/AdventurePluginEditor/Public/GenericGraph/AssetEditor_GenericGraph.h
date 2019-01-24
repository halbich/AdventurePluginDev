#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraph.h"

#include "NotifyHook.h"
#include "GraphEditor.h"
#include "AssetEditorToolkit.h"

class FGGAssetEditorToolbar;

class ADVENTUREPLUGINEDITOR_API FAssetEditor_GenericGraph : public FAssetEditorToolkit, public FNotifyHook, public FGCObject
{
public:
	FAssetEditor_GenericGraph();
	virtual ~FAssetEditor_GenericGraph();

	void InitGenericGraphAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UGenericGraph* Graph);

	// IToolkit interface
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	// End of IToolkit interface

	// FAssetEditorToolkit
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FString GetDocumentationLink() const override;
	virtual void SaveAsset_Execute() override;
	// End of FAssetEditorToolkit

	//Toolbar
	void UpdateToolbar();
	TSharedPtr<class FAssetEditorToolbar_GenericGraph> GetToolbarBuilder() { return ToolbarBuilder; }
	void RegisterToolbarTab(const TSharedRef<class FTabManager>& TabManager);


	// FSerializableObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	// End of FSerializableObject interface

private:
	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);

	void CreateInternalWidgets();
	TSharedRef<SGraphEditor> CreateViewportWidget();


	void BindCommands();

	void CreateEdGraph();

	void CreateCommandList();

	TSharedPtr<SGraphEditor> GetCurrGraphEditor() const;

	FGraphPanelSelectionSet GetSelectedNodes() const;


	// Delegates for graph editor commands
	void SelectAllNodes();
	bool CanSelectAllNodes();
	void DeleteSelectedNodes();
	bool CanDeleteNodes();
	void DeleteSelectedDuplicatableNodes();
	void CutSelectedNodes();
	bool CanCutNodes();
	void CopySelectedNodes();
	bool CanCopyNodes();
	void PasteNodes();
	void PasteNodesHere(const FVector2D& Location);
	bool CanPasteNodes();
	void DuplicateNodes();
	bool CanDuplicateNodes();

	void GraphSettings();
	bool CanGraphSettings() const;

	void OnRenameNode();
	bool CanRenameNodes() const;

	//////////////////////////////////////////////////////////////////////////
	// graph editor event
	void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);

	void OnNodeDoubleClicked(UEdGraphNode* Node);

	void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);

	void OnPackageSaved(const FString& PackageFileName, UObject* Outer);

private:

	//Toolbar
	TSharedPtr<class FAssetEditorToolbar_GenericGraph> ToolbarBuilder;

	/** Handle to the registered OnPackageSave delegate */
	FDelegateHandle OnPackageSavedDelegateHandle;

	TSharedPtr<SGraphEditor> ViewportWidget;
	TSharedPtr<class IDetailsView> PropertyWidget;

	/** The command list for this editor */
	TSharedPtr<FUICommandList> GraphEditorCommands;

protected:
	virtual FGraphAppearanceInfo GetViewportWidgetAppearanceInfo() const;
	virtual UClass* GetGraphSchemaClass() const;
	virtual void RebuildGenericGraph();
	UGenericGraph* EditingGraph;
};


