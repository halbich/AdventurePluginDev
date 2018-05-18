// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "Widgets/SWidget.h"
#include "Framework/Commands/UICommandList.h"


/**
* Unreal level editor main toolbar
*/
class FAdventurePluginEditorToolBar
{

public:

	/**
	* Generates menu content for the main combo button drop down menu
	*
	* @return	Menu content widget
	*/
	static TSharedRef< SWidget > GeneratePluginMenu(TSharedRef<FUICommandList> InCommandList);

};
