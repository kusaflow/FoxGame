// Fill out your copyright notice in the Description page of Project Settings.


#include "LvlGuide_s1.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h" 

// Sets default values
ALvlGuide_s1::ALvlGuide_s1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	RootComponent = box;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	mesh->SetupAttachment(box);

	box->OnComponentBeginOverlap.AddDynamic(this, &ALvlGuide_s1::OnOverlapBegin);


}

// Called when the game starts or when spawned
void ALvlGuide_s1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALvlGuide_s1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALvlGuide_s1::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}