// Fill out your copyright notice in the Description page of Project Settings.


#include "EG_mushroom_01.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h" 
#include "../../characters/mainChar_Fox.h"
#include "../../kusaGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEG_mushroom_01::AEG_mushroom_01()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	RootComponent = box;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	mesh->SetupAttachment(box);

	mesh->SetWorldScale3D(FVector(5));
	mesh->SetRelativeLocation(FVector(0, 0, -12));

	CanEatFood = false;
	isFoodThere = true;

	box->OnComponentBeginOverlap.AddDynamic(this, &AEG_mushroom_01::OnOverlapBegin);
	box->OnComponentEndOverlap.AddDynamic(this, &AEG_mushroom_01::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AEG_mushroom_01::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEG_mushroom_01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UkusaGameInstance* gameInst = Cast<UkusaGameInstance>(GetGameInstance());

	if (CanEatFood)
		gameInst->bIsCurrentFoodIsThere = isFoodThere;

	if (isFoodThere && CanEatFood) {
		
		if (gameInst) {
			if (gameInst->bCanDisapearFood && mesh) {

				AmainChar_Fox* fox = Cast<AmainChar_Fox>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

				if (fox) {
					fox->OtherActorLoc_ToSnapLoc = mesh->GetComponentLocation();
				}

				fox->powerLvl += 50;

				mesh->DestroyComponent();
				isFoodThere = false;
				gameInst->bCanDisapearFood = false;
			}
		}

	}
	

}

void AEG_mushroom_01 :: OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CanEatFood = true;

	if (isFoodThere)
		mesh->SetWorldScale3D(FVector(6));

	
	AmainChar_Fox* fox = Cast<AmainChar_Fox>(OtherActor);

	if (fox) {
		if (isFoodThere) {
			fox->What_to_do_with_interact = 1;
			fox->OtherActorLoc_ToSnapLoc = box->GetComponentLocation();
		}
		else {
			fox->What_to_do_with_interact = 0;
		}
	}


}


void AEG_mushroom_01::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CanEatFood = false;
	AmainChar_Fox* fox = Cast<AmainChar_Fox>(OtherActor);

	if (fox) {
		fox->What_to_do_with_interact = 0;
	}

	if (isFoodThere)
		mesh->SetWorldScale3D(FVector(5));

}
