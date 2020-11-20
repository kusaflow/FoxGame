// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "helpfulDataOnScreen.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALSTORYGAME_API UhelpfulDataOnScreen : public UUserWidget
{
	GENERATED_BODY()
public:
	UhelpfulDataOnScreen(const FObjectInitializer& objectInit);

	virtual void NativeConstruct() override;

	void Update_Interact_progressBar();

private:

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* InstructHelper;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* interact_progressBar;
	
};
