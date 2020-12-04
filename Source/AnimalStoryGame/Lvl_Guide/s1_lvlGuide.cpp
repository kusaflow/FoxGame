// Fill out your copyright notice in the Description page of Project Settings.


#include "s1_lvlGuide.h"
#include "../kusaGameInstance.h"
#include "GuideActor.h"

// Sets default values
As1_lvlGuide::As1_lvlGuide()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currIdx = 1;

	totalCheckPoints = 2;

	locations = new FVector[totalCheckPoints];
	rotation = new FRotator[totalCheckPoints];
	Box_Bounds = new FVector[totalCheckPoints];

	locations[0] = FVector(-20, -1100, 500);
	rotation[0] = FRotator(0);
	Box_Bounds[0] = FVector(1);

	locations[1] = FVector(-3020.0, -2270.0, 500);
	rotation[1] = FRotator(0, -60, 0);
	Box_Bounds[1] = FVector(1);

}

// Called when the game starts or when spawned
void As1_lvlGuide::BeginPlay()
{
	Super::BeginPlay();

	UkusaGameInstance* gameInst = Cast<UkusaGameInstance>(GetGameInstance());

	
	currIdx=1;
	if (currIdx <= totalCheckPoints) {
		FActorSpawnParameters spawnPara;
		spawnPara.Owner = this;

		UWorld* world = GetWorld();
		if (world)
			world->SpawnActor<AGuideActor>(GuideActor, locations[currIdx - 1], rotation[currIdx - 1], spawnPara)->setBoxBounds(Box_Bounds[currIdx - 1]);
	}
	gameInst->bDrawGuideActor = false;
	gameInst->bshowPath= false;
	
}

// Called every frame
void As1_lvlGuide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UkusaGameInstance* gameInst = Cast<UkusaGameInstance>(GetGameInstance());

	if (gameInst->bDrawGuideActor) {
		currIdx++;
		if (currIdx <= totalCheckPoints) {
			FActorSpawnParameters spawnPara;
			spawnPara.Owner = this;


			UWorld* world = GetWorld();
			if (world)
				world->SpawnActor<AActor>(GuideActor, locations[currIdx - 1], rotation[currIdx - 1], spawnPara);

			gameInst->bDrawGuideActor = false;

			//RootComponent->SetWorldLocation(locations[currIdx - 1]);
			//RootComponent->SetWorldRotation(rotation[currIdx - 1]);
		}

	}

}

