// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "s1_lvlGuide.generated.h"

UCLASS()
class ANIMALSTORYGAME_API As1_lvlGuide : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	As1_lvlGuide();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	TSubclassOf<class AGuideActor> GuideActor;

	FVector* locations;
	FRotator* rotation;
	int totalCheckPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "kusa")
		int currIdx;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
