// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Scene1_Lvl_Guide.generated.h"

UCLASS()
class ANIMALSTORYGAME_API AScene1_Lvl_Guide : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScene1_Lvl_Guide();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "kusa")
		class UBoxComponent* box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "kusa")
		class UStaticMeshComponent* mesh;

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

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
