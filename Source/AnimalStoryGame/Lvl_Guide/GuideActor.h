// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GuideActor.generated.h"

UCLASS()
class ANIMALSTORYGAME_API AGuideActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGuideActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "kusa")
		class UBoxComponent* box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "kusa")
		class UStaticMeshComponent* mesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
