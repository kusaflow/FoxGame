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

	void Visibility_Primary(bool setV);
	void Visibility_Secondary(bool setV);


	void SetText_Primary(FText msg);
	void SetText_Secondary(FText msg);
	
private:

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* InstructHelper;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* PrimaryHelpText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* SecondaryHelpText;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* interact_progressBar;
	
};
