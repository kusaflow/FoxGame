// Fill out your copyright notice in the Description page of Project Settings.


#include "mainChar_Fox.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AmainChar_Fox::AmainChar_Fox()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(GetRootComponent());
	cameraBoom->bDoCollisionTest = false;
	cameraBoom->TargetArmLength = 800;
	cameraBoom->SocketOffset = FVector(0.f, 0.f, 0.f);
	cameraBoom->SetRelativeRotation(FRotator(-20, 0, 0.f));
	//cameraBoom->RelativeRotation = FRotator(0.f, 0.f, 0.f);
	//cameraBoom->bUsePawnControlRotation = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void AmainChar_Fox::BeginPlay()
{
	Super::BeginPlay();

	RootComponent->AddLocalRotation(FRotator(0, 60, 0));
	
}

// Called every frame
void AmainChar_Fox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCharacterMovement()->MaxWalkSpeed < VelShouldBe) {
		GetCharacterMovement()->MaxWalkSpeed += 800 * DeltaTime;
	}
	else if (GetCharacterMovement()->MaxWalkSpeed > VelShouldBe) {
		GetCharacterMovement()->MaxWalkSpeed -= 800 * DeltaTime;
	}

}

// Called to bind functionality to input
void AmainChar_Fox::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("forward", this, &AmainChar_Fox::moveForward);
	PlayerInputComponent->BindAxis("moveLeftRight", this, &AmainChar_Fox::moveLeftRight);

	PlayerInputComponent->BindAxis("GoFast", this, &AmainChar_Fox::GoFast);

	PlayerInputComponent->BindAxis("xAxis", this, &AmainChar_Fox::CameraYaw_z);
	PlayerInputComponent->BindAxis("yAxis", this, &AmainChar_Fox::CameraPitch_y);

	//look around
	PlayerInputComponent->BindAxis("LookAround", this, &AmainChar_Fox::CanLookAround);

}

void AmainChar_Fox :: moveForward(float val) {

	if (val == 1) {
		if (Controller != nullptr) {
			const FRotator Rotation = RootComponent->GetComponentRotation();//Controller->GetControlRotation();
			const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);


			AddMovementInput(Direction, 1);
		}
	}
	else if (val == -1) {
		if (Controller != nullptr) {
			const FRotator Rotation = RootComponent->GetComponentRotation();// Controller->GetControlRotation();
			const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			AddMovementInput(Direction, -1);
		}
	}

	
}


void AmainChar_Fox::GoFast(float val) {
	VelShouldBe = 200;
	
	if (val == 1) {
		VelShouldBe = 900;
	}
}


void AmainChar_Fox::CameraYaw_z(float val) {
	if (!bCanLookAround) {
		return;
	}
	FRotator newR = FRotator(0, 0, 0);
	newR.Yaw += val;
	cameraBoom->AddRelativeRotation(newR);

}

void AmainChar_Fox::CameraPitch_y(float val) {
	if (!bCanLookAround) {
		return;
	}
	FRotator newR = cameraBoom->GetRelativeRotation();
	newR.Pitch = FMath::Clamp(newR.Pitch + val, -80.0f, 4.0f);

	cameraBoom->SetRelativeRotation(newR);
}

void AmainChar_Fox::CanLookAround(float val) {
	bCanLookAround = false;
	if (val == 1) {
		bCanLookAround = true;
	}
	else {
		cameraBoom->SetRelativeRotation(FRotator(-20, -35, 0.f));
	}
}


void AmainChar_Fox::moveLeftRight(float val) {
	if (val == -1) {
		RootComponent->AddWorldRotation(FRotator(0,-50 * GetWorld()->GetDeltaSeconds(),0));
	}
	else if (val == 1) {
		RootComponent->AddWorldRotation(FRotator(0, 50 * GetWorld()->GetDeltaSeconds(), 0));
	}
}



