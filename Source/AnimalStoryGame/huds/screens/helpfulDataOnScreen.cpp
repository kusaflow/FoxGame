// Fill out your copyright notice in the Description page of Project Settings.


#include "helpfulDataOnScreen.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "../../characters/mainChar_Fox.h"
#include "Kismet/GameplayStatics.h"

UhelpfulDataOnScreen::UhelpfulDataOnScreen(const FObjectInitializer& objectInit) : Super(objectInit)
{
	
}

void UhelpfulDataOnScreen::NativeConstruct()
{
	Super::NativeConstruct();
}

void UhelpfulDataOnScreen :: Update_Interact_progressBar() {
	AmainChar_Fox* fox = Cast<AmainChar_Fox>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (fox) {
		//UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD();
		interact_progressBar->SetPercent((float)fox->interact / fox->mileStone_interactVal);
	}
}

