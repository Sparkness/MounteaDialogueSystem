// All rights reserved Dominik Pavlicek 2023

#pragma once

#include "CoreMinimal.h"
#include "Nodes/MounteaDialogueGraphNode.h"
#include "Engine/DataTable.h"
#include "Helpers/MounteaDialogueGraphHelpers.h"
#include "UObject/Object.h"
#include "MounteaDialogueGraphNode_DialogueNodeBase.generated.h"

/**
 * Mountea Dialogue Graph Node abstract Base class.
 * 
 * Enhances 'MounteaDialogueGraphNode' Base class with Dialogue data.
 * Provides DataTable and Row options that define the Dialogue data which will be displayed in UI.
 */
UCLASS(Abstract, ClassGroup=("Mountea|Dialogue"), AutoExpandCategories=("Mountea", "Dialogue", "Mountea|Dialogue"))
class MOUNTEADIALOGUESYSTEM_API UMounteaDialogueGraphNode_DialogueNodeBase : public UMounteaDialogueGraphNode
{
	GENERATED_BODY()

public:

	UMounteaDialogueGraphNode_DialogueNodeBase();

	virtual FText GetDescription_Implementation() const override;

	//TODO: Implement custom Handle with this logic: UPROPERTY(meta=(GetOptions ="abc")) https://benui.ca/unreal/uproperty/#getoptions
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Mountea|Dialogue")
	virtual UDataTable* GetDataTable() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Mountea|Dialogue")
	virtual FName GetRowName() const
	{ return RowName; };
	
protected:

	/** Defines whether this Node will start automatically or if requires input.*/
	UPROPERTY(BlueprintReadOnly, Category="Mountea|Dialogue")
	uint8 bAutoStarts : 1;

	UPROPERTY(Category="Mountea|Dialogue", EditAnywhere, BlueprintReadOnly, meta=(RequiredAssetDataTags="RowStructure=DialogueRow", DisplayThumbnail=false, NoResetToDefault))
	UDataTable*	DataTable;

	/** Name of row in the table that we want */
	UPROPERTY(Category="Mountea|Dialogue", EditAnywhere, BlueprintReadOnly, meta=(GetOptions ="GetRowNames", NoResetToDefault))
	FName RowName;

	UPROPERTY(BlueprintReadOnly, Category="Mountea|Dialogue")
	TArray<TSubclassOf<UMounteaDialogueGraphNode>> AllowedInputClasses;

	UPROPERTY(BlueprintReadOnly, Category="Mountea|Dialogue")
	FGuid NodeGUID;

#if WITH_EDITORONLY_DATA

	/**
	 * ❗Experimental Feature ❗
	 * Shows read-only Texts without localization of selected Dialogue Row.
	 */
	UPROPERTY(Transient, VisibleAnywhere, Category="Mountea|Dialogue", meta=(MultiLine=true))
	TArray<FString> Preview;

#endif
	
#if WITH_EDITOR
	virtual bool ValidateNode(TArray<FText>& ValidationsMessages, const bool RichFormat) override;
	virtual bool CanCreateConnection(UMounteaDialogueGraphNode* Other, EEdGraphPinDirection Direction, FText& ErrorMessage) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

#if WITH_EDITORONLY_DATA
public:
	virtual void UpdatePreviews();
#endif

private:

	UFUNCTION()
	TArray<FName> GetRowNames() const
	{
		if (DataTable)
		{
			return DataTable->GetRowNames();
		}

		return TArray<FName>();
	}
};
