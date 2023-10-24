// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "Components/ActorComponent.h"
#include "QuestGiver.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UQuestGiver : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UQuestGiverWidget> QuestPanelWidgetClass;

	UPROPERTY()
	class UQuestGiverWidget* QuestGiverWidget;

	UPROPERTY()
	TArray<FString> ListQID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UQuestReceiver* QuestReceiver;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UDataTable* NPCQuestTable;

public:	
	// Sets default values for this component's properties
	UQuestGiver();

	/*  */
	UFUNCTION()
	void GiveQuestToReceiver(FName QuestID);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/*  */
	void SetRecevier(class UQuestReceiver* Receiver);

	/*  */
	void LoadTable(const TCHAR* Path, FName NID);

	/*  */
	TArray<FString> GetQuestList() const { return ListQID; };
};
