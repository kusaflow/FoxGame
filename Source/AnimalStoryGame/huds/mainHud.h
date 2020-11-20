// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "mainHud.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALSTORYGAME_API AmainHud : public AHUD
{
	GENERATED_BODY()
public:

	AmainHud();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float Delta) override;

	//visibilities
	

private:

public:
	UPROPERTY(EditDefaultsOnly, Category = "kusa_UIs")
	TSubclassOf<class UUserWidget> helper_subClass;

	class UhelpfulDataOnScreen* UI_helper;
	
	
};
