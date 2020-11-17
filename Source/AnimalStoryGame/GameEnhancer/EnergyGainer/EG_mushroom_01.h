// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EG_mushroom_01.generated.h"

UCLASS()
class ANIMALSTORYGAME_API AEG_mushroom_01 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEG_mushroom_01();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "kusa")
	class UBoxComponent* box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "kusa")
		class UStaticMeshComponent* mesh;

	bool isFoodThere;
	bool CanEatFood;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
