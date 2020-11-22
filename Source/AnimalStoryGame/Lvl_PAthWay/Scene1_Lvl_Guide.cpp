// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene1_Lvl_Guide.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h" 
#include "../characters/mainChar_Fox.h"

// Sets default values
AScene1_Lvl_Guide::AScene1_Lvl_Guide()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	RootComponent = box;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	mesh->SetupAttachment(box);

	box->OnComponentBeginOverlap.AddDynamic(this, &AScene1_Lvl_Guide::OnOverlapBegin);

	currIdx = 1;

	totalCheckPoints = 4;

	locations = new FVector[totalCheckPoints];
	rotation = new FRotator[totalCheckPoints];

	locations[0] = FVector(1130, -2350, 100);
	rotation[0] = FRotator(0);

	locations[1] = FVector(-3195.0, -5315, 100);
	rotation[1] = FRotator(0, -60, 0);

	locations[2] = FVector(1130, -7752, 100);
	rotation[2] = FRotator(0, 50, 0);

	locations[3] = FVector(6350, -7752, 100);
	rotation[3] = FRotator(0, 120, 0);

}

// Called when the game starts or when spawned
void AScene1_Lvl_Guide::BeginPlay()
{
	Super::BeginPlay();

	currIdx = 1;
	if (locations && rotation) {
		RootComponent->SetWorldLocation(locations[0]);
		RootComponent->SetWorldRotation(rotation[0]);
	}
	
}

// Called every frame
void AScene1_Lvl_Guide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScene1_Lvl_Guide::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AmainChar_Fox* fox = Cast<AmainChar_Fox>(OtherActor);

	if (fox) {
		currIdx++;
		UE_LOG(LogTemp, Warning, TEXT("oh no"));
		if (currIdx <= totalCheckPoints) {
			RootComponent->SetWorldLocation(locations[currIdx - 1]);
			RootComponent->SetWorldRotation(rotation[currIdx - 1]);
		}
	}

}

