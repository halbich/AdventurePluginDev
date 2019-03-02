#pragma once

#include "CoreMinimal.h"
#include "Customizations/BaseClasses/ComboBoxDetailCustomization.h"
#include "IDetailCustomization.h"

/**
* Property editor customization for UDialogGraphNode_DialogLineBase class,
* which replaces its UDialogGraphNode_DialogLineBase#AnimationName property
* with a ComboBox picker, allowing to choose one of defined animation states.
*/
class FDialogLineCustomization : public FComboBoxDetailCustomization
{
public:

	/**
	* Creates an instance of FDialogLineCustomization
	*/
	static TSharedRef<IDetailCustomization> MakeInstance();

	/**
	* Retrieves the UDialogGraphNode_DialogLineBase#AnimationName property
	* of the customized UDialogGraphNode_DialogLineBase,
	* which should be represented as a ComboBox.
	*/
	virtual TSharedPtr<IPropertyHandle> GetIdPropertyHandle(IDetailLayoutBuilder& DetailLayout) const override;

	/**
	* Retrieves the label of this ComboBox, which will be displayed next
	* to it in property editor.
	*/
	virtual FText GetComboBoxName() const override;

	/**
	* Fills the animation states to the FComboBoxCustomizationBase#Options array when the ComboBox reloads.
	*/
	virtual void ReloadOptions() override;
};