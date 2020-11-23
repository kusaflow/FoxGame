// Fill out your copyright notice in the Description page of Project Settings.


#include "GuideActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h" 
#include "../characters/mainChar_Fox.h"
#include "../kusaGameInstance.h"

// Sets default values
AGuideActor::AGuideActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	RootComponent = box;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	mesh->SetupAttachment(box);

	box->OnComponentBeginOverlap.AddDynamic(this, &AGuideActor::OnOverlapBegin);


}

// Called when the game starts or when spawned
void AGuideActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGuideActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UkusaGameInstance* GameInst = Cast<UkusaGameInstance>(GetGameInstance());
	if (mesh) {
		if (GameInst->bshowPath) {
			mesh->SetVisibility(true);
		}
		else {
			mesh->SetVisibility(false);
		}
	}

}

void AGuideActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AmainChar_Fox* fox = Cast<AmainChar_Fox>(OtherActor);
	UkusaGameInstance* gameInst = Cast<UkusaGameInstance>(GetGameInstance());
	if (fox) {
		gameInst->bDrawGuideActor = true;
		Destroy();
	}

}