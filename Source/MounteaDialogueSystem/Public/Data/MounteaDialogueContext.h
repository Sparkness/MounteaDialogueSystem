// All rights reserved Dominik Pavlicek 2023

#pragma once

#include "CoreMinimal.h"
#include "MounteaDialogueGraphDataTypes.h"
#include "UObject/Object.h"
#include "MounteaDialogueContext.generated.h"

class UMounteaDialogueGraphNode;

/**
 * Dialogue Context.
 * 
 * Contains information needed to successfully start Dialogue.
 * Also helps tracking Dialogue Specific data. Is recycled for whole Dialogue Graph.
 */
UCLASS()
class MOUNTEADIALOGUESYSTEM_API UMounteaDialogueContext : public UObject
{
	GENERATED_BODY()

public:

	/**
	 * Pointer to the Node which is currently active.
	 * ❗Might be null❗
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mountea|Dialogue")
	UMounteaDialogueGraphNode* ActiveNode = nullptr;
	/**
	 * List of Nodes that can be accessed from Active Node.
	 * Already filtered to contain only those that can be triggered.
	 * 
	 * ❗Might be empty❗ 
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mountea|Dialogue")
	TArray<UMounteaDialogueGraphNode*> AllowedChildNodes;
	/**
	 * Active Dialogue Row from Active Node. 
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mountea|Dialogue")
	FDialogueRow ActiveDialogueRow;
	/**
	 * Index of currently used Dialogue Row Data row.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mountea|Dialogue")
	int32 ActiveDialogueRowDataIndex = 0;

public:

	virtual bool IsValid() const;

	/**
	 * Returns the Active Node object.
	 * ❗Might be null❗
	 * 
	 * @return Active Node if any specified
	 */
	UMounteaDialogueGraphNode* GetActiveNode() const
	{ return ActiveNode; };
	/**
	 * Returns lsit of Children Nodes from Active Node.
	 * ❗Might be empty❗
	 * 
	 * @return List of allowed Children Nodes 
	 */
	TArray<UMounteaDialogueGraphNode*> GetChildrenNodes() const
	{ return AllowedChildNodes; };
	/**
	 * Returns Active Dialogue Row if any.
	 * ❗Might return invalid❗ 
	 * 
	 * @return Active Dialogue Row if any 
	 */
	FDialogueRow GetActiveDialogueRow() const
	{ return ActiveDialogueRow; };
	/**
	 *Returns the Active Dialogue Row Data Index.
	 * 
	 * @return Active Row Index 
	 */
	int32 GetActiveDialogueRowDataIndex() const
	{ return ActiveDialogueRowDataIndex; };
	
	virtual void SetDialogueContext(UMounteaDialogueGraphNode* NewActiveNode, TArray<UMounteaDialogueGraphNode*> NewAllowedChildNodes);
	virtual void UpdateActiveDialogueNode(UMounteaDialogueGraphNode* NewActiveNode);
	virtual void UpdateActiveDialogueRow(const FDialogueRow& NewActiveRow);
	virtual void UpdateActiveDialogueRowDataIndex(int32 NewIndex);
};