// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Stats/Stats.h"
#include "AdventurePluginEditor.h"
#include "AdventurePluginDialogEditor.h"
#include "Tickable.h"

class UDialogGraph;

/* based on FBehaviorTreeDebugger */
class FAdventurePluginDialogDebugger : public FTickableGameObject
{
public:

	FAdventurePluginDialogDebugger();
	~FAdventurePluginDialogDebugger();


	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual bool IsTickableWhenPaused() const override { return true; }
	virtual bool IsTickableInEditor() const override { return true; }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(FFAdventurePluginDialogEditorTickHelper, STATGROUP_Tickables); }

	/** Refresh the debugging information we are displaying (only when paused, as Tick() updates when running) */
	void Refresh();

	void Setup(UDialogGraph* InDialogAsset, TSharedRef<class FAdventurePluginDialogEditor> InEditorOwner);


	bool IsDebuggerReady() const;

	void OnBeginPIE(const bool bIsSimulating);
	void OnEndPIE(const bool bIsSimulating);
	void OnPausePIE(const bool bIsSimulating);

	static void StopPlaySession();
	static void PausePlaySession();
	static void ResumePlaySession();
	static bool IsPlaySessionPaused();
	static bool IsPlaySessionRunning();
	static bool IsPIESimulating();
	static bool IsPIENotSimulating();

private:

	/** owning editor */
	TWeakPtr<FAdventurePluginDialogEditor> EditorOwner;

	/** asset for debugging */
	UDialogGraph* DialogAsset;

	/** cached PIE state */
	uint32 bIsPIEActive : 1;
};