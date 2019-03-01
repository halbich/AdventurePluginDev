#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"
#include "Customizations/BaseClasses/ComboBoxDetailCustomization.h"

/**
* Property editor customization for UDialogGraphNode_Goto class, which replaces its TargetNodeId property
* with a ComboBox picker, allowing to choose one of other nodes in the same graph by its Id.
*/
class FGotoCustomization : public FComboBoxDetailCustomization
{
public:

	/**
	* Creates an instance of FGotoCustomization
	*/
	static TSharedRef<IDetailCustomization> MakeInstance();

	/**
	* Retrieves the TargetNodeId property of the customized UDialogGraphNode_Goto,
	* which should be represented as a ComboBox.
	*/
	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(IDetailLayoutBuilder& DetailLayout) const override;

	/**
	* Retrieves the label of this ComboBox, which will be displayed next
	* to it in property editor.
	*/
	virtual FText GetComboBoxName() const override;

	/**
	* Fills the Ids of other nodes in the graph to the Options
	* array when the ComboBox reloads.
	*/
	virtual void ReloadOptions() override;
};