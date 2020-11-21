// Fill out your copyright notice in the Description page of Project Settings.


#include "mainHud.h"
#include "Blueprint/UserWidget.h"
#include "screens/helpfulDataOnScreen.h"


AmainHud::AmainHud() {

}

void AmainHud::BeginPlay() {
	Super::BeginPlay();

	if (helper_subClass) {
		UI_helper = CreateWidget<UhelpfulDataOnScreen>(GetWorld(), helper_subClass);
		if (UI_helper) {
			//UI_helper->AddToViewport();
		}
	}
}

void AmainHud::Tick(float Delta) {
	Super::Tick(Delta);

	//helper class
	if (UI_helper) {
		//UI_helper->Update_Interact_progressBar();
	}

}

void AmainHud::DrawHUD() {
	Super::DrawHUD();
}

