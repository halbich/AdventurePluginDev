/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#pragma once

#include "CoreMinimal.h"
#include "GenericGraph/GenericGraph.h"
#include "NotifyHook.h"
#include "GraphEditor.h"
#include "AssetEditorToolkit.h"

class FGGAssetEditorToolbar;

/**
* Editor class for editing assets of type UGenericGraph.
*/
class ADVENTUREPLUGINEDITOR_API FAssetEditor_GenericGraph : public FAssetEditorToolkit, public FNotifyHook, public FGCObject
{
public:
	FAssetEditor_GenericGraph();
	virtual ~FAssetEditor_GenericGraph();

	/**
	* Initializes this asset editor. Called immediately after construction. If you override this, remember to
	* call the base class implementation.
	* @param	Mode			Asset editing mode for this editor (standalone or world-centric)
	* @param	InitToolkitHost	When Mode is WorldCentric, this is the level editor instance to spawn this editor within
	* @param	Graph			The generic graph to edit
	*/
	void InitGenericGraphAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UGenericGraph* Graph);

	/** Register tabs that this toolkit can spawn with the TabManager */
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;

	/** Unregister tabs that this toolkit can spawn */
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;

	/** Returns the invariant name of this toolkit type */
	virtual FName GetToolkitFName() const override;

	/** Returns the localized name of this toolkit type */
	virtual FText GetBaseToolkitName() const override;

	/** Returns the localized name of this toolkit */
	virtual FText GetToolkitName() const override;

	/** Returns the localized tooltip text of this toolkit */
	virtual FText GetToolkitToolTipText() const override;

	/** @return The color and opacity to use for the color that appears behind the tab text for this toolkit's tab in world-centric mode. */
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	/** Returns the localized prefix string to use for tab labels in world-centric mode. */
	virtual FString GetWorldCentricTabPrefix() const override;

	/** @return The documentation location for this editor */
	virtual FString GetDocumentationLink() const override;

	/** Called when "Save" is clicked for this asset */
	virtual void SaveAsset_Execute() override;

	/**
	* Use this method to serialize any UObjects contained that you wish to keep around.
	* @param Collector The collector of referenced objects.
	*/
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	
private:

	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);

	TSharedRef<SGraphEditor> CreateViewportWidget();
	TSharedPtr<SGraphEditor> GetCurrentGraphEditor() const;
	FGraphPanelSelectionSet GetSelectedNodes() const;

	void BindCommands();
	void CreateEdGraph();
	void CreateCommandList();
	void CreateInternalWidgets();

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

	/** Handle to the registered OnPackageSave delegate */
	FDelegateHandle OnPackageSavedDelegateHandle;

	TSharedPtr<SGraphEditor> ViewportWidget;
	TSharedPtr<class IDetailsView> PropertyWidget;

	/** The command list for this editor */
	TSharedPtr<FUICommandList> GraphEditorCommands;

protected:

	/**
	* Returns FGraphAppearanceInfo for customizing the graph viewport, mainly for text
	* in the lower right corner.
	*/
	virtual FGraphAppearanceInfo GetViewportWidgetAppearanceInfo() const;

	/**
	* Returns graph schema class for this graph, derived from UEdGraphSchema.
	* @return UAssetGraphSchema_GenericGraph when not overriden.
	*/
	virtual UClass* GetGraphSchemaClass() const;

	/**
	* Executes rebuilding of this graph. It can be useful to override this method
	* when there are actions needed after every graph rebuild, but it is necessary
	* to call this base method first.
	*/
	virtual void RebuildGenericGraph();

	/** UGenericGraph graph which is currently edited in this editor. */
	UGenericGraph* EditingGraph;
};


