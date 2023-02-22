// All rights reserved Dominik Pavlicek 2023

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MounteaDialogueWBPInterface.generated.h"

class IMounteaDialogueManagerInterface;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMounteaDialogueWBPInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Mountea Dialogue Widget Blueprint Interface.
 * 
 * Interface allowing any Widget Blueprint to be used for Mountea Dialogue.
 * Provides a nice and clean way to trigger Refresh event in any Widget Blueprint.
 */
class MOUNTEADIALOGUESYSTEM_API IMounteaDialogueWBPInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	 * This event should be called when you want to refresh UI data.
	 * 
	 * @param DialogueManager	Dialogue Manager Interface reference. Request 'GetDialogueContext' to retrieve data to display.
	 * @param Command			String command. All commands are defined in ProjectSettings/MounteaFramework/MounteaDilaogueSystem.
	 */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Interaction")
	void RefreshDialogueWidget(const TScriptInterface<IMounteaDialogueManagerInterface>& DialogueManager, const FString& Command);
};
