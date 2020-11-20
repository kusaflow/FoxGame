// Fill out your copyright notice in the Description page of Project Settings.


#include "mainChar_Fox.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Anim/Fox_AnimInstance.h"
#include "../kusaGameInstance.h" 	
#include "Components/CapsuleComponent.h"


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
	cameraBoom->SetRelativeRotation(FRotator(-20, 300, 0.f));
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

	if (GetMesh()->SkeletalMesh) {
		const FVector Back_LeftBone_WorldLocation = GetMesh()->GetBoneLocation(Back_Left_LegBoneName);
		Back_LeftBone_RelativeLocation = GetActorTransform().InverseTransformPosition(Back_LeftBone_WorldLocation);

		const FVector Back_RightBone_WorldLocation = GetMesh()->GetBoneLocation(Back_Right_LegBoneName);
		Back_RightBone_RelativeLocation = GetActorTransform().InverseTransformPosition(Back_RightBone_WorldLocation);

		const FVector Front_LeftBone_WorldLocation = GetMesh()->GetBoneLocation(Front_Left_LegBoneName);
		Front_LeftBone_RelativeLocation = GetActorTransform().InverseTransformPosition(Front_LeftBone_WorldLocation);

		const FVector Front_RightBone_WorldLocation = GetMesh()->GetBoneLocation(Front_Right_LegBoneName);
		Front_RightBone_RelativeLocation = GetActorTransform().InverseTransformPosition(Front_RightBone_WorldLocation);

		InitMeshRelativeLoc = GetMesh()->GetRelativeTransform().GetLocation();
	}
	
}

// Called every frame
void AmainChar_Fox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UkusaGameInstance* gameInst = Cast<UkusaGameInstance>(GetGameInstance());


	if (GetCharacterMovement()->MaxWalkSpeed < VelShouldBe) {
		GetCharacterMovement()->MaxWalkSpeed += 800 * DeltaTime;
	}
	else if (GetCharacterMovement()->MaxWalkSpeed > VelShouldBe) {
		GetCharacterMovement()->MaxWalkSpeed -= 800 * DeltaTime;
	}

	//Inverse Kinemetics
	IK(DeltaTime);

	//animInst index set
	AnimInst_Idx = gameInst->anim_inst_idx;
	

	if (GetVelocity().Size() != 0) {}
		//GetMesh()->SetRelativeLocation(InitMeshRelativeLoc);

	
	//interact CoolDown
	if (interact > 0) {
		interact -= 130 * DeltaTime;
	}
	else if (interact <= 0) {
		interact = 0;
	}

	//state change check
	if (do_changeState_at_mileStone) {
		if (interact >= mileStone_interactVal) {
			do_changeState_at_mileStone = false;
			if (playCineMetic) {
				playAnimation();
			}
			
			disableInput_camera = AMS_disableInput_camera;
			disableInput_interact = AMS_disableInput_interact;
			disableInput_movement = AMS_disableInput_movement;

			AnimInst_Idx = AMS_animInst;
			gameInst->anim_inst_idx = AMS_animInst;

			cameraBoom->TargetArmLength = AMS_armLength;
			cameraBoom->SetRelativeRotation(AMS_CameraRot);
			
			
		}
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
	
	 
	//interact
	PlayerInputComponent->BindAction("interact", IE_Pressed, this, &AmainChar_Fox::interact_f);
	
}


void AmainChar_Fox::IK(float DeltaTime) {
	//Inverse Kinemetics
	UFox_AnimInstance* animInst = Cast<UFox_AnimInstance>(GetMesh()->GetAnimInstance());

	if (!animInst) {
		return;
	}

	//=================Ik--------------------------

	TArray<AActor*> ActorToIgnore;
	FHitResult Back_LeftLeg_Hit;

	const FVector Back_LeftLeg_Loc = GetTransform().TransformPosition(Back_LeftBone_RelativeLocation);
	bool b_Back_LeftFootTrace = UKismetSystemLibrary::SphereTraceSingle(this, Back_LeftLeg_Loc + FVector(0, 0, 50),
		Back_LeftLeg_Loc + FVector(0, 0, -100), 10, ETraceTypeQuery::TraceTypeQuery1, false, ActorToIgnore,
		EDrawDebugTrace::None, Back_LeftLeg_Hit, false);

	FHitResult Back_RightLeg_Hit;

	const FVector Back_RightLeg_Loc = GetTransform().TransformPosition(Back_RightBone_RelativeLocation);
	bool b_Back_RightFootTrace = UKismetSystemLibrary::SphereTraceSingle(this, Back_RightLeg_Loc + FVector(0, 0, 50),
		Back_RightLeg_Loc + FVector(0, 0, -100), 10, ETraceTypeQuery::TraceTypeQuery1, false, ActorToIgnore,
		EDrawDebugTrace::None, Back_RightLeg_Hit, false);

	float Back_zOffset = 0;
	if (Back_LeftLeg_Hit.ImpactPoint.Z < Back_RightLeg_Hit.ImpactPoint.Z) {
		Back_zOffset = Back_LeftLeg_Loc.Z - Back_LeftLeg_Hit.ImpactPoint.Z;

		animInst->Back_RightLeg_Effector_Loc = Back_RightLeg_Hit.ImpactPoint + FVector(0, 0, 10);
		animInst->Back_RightLeg_Alpha = 1;
		animInst->Back_LeftLeg_Alpha = 0;

	}
	else {
		Back_zOffset = Back_RightLeg_Loc.Z - Back_RightLeg_Hit.ImpactPoint.Z;

		animInst->Back_LeftLeg_Effector_Loc = Back_LeftLeg_Hit.ImpactPoint + FVector(0, 0, 10);
		animInst->Back_LeftLeg_Alpha = 1;
		animInst->Back_RightLeg_Alpha = 0;

	}

	GetMesh()->SetRelativeLocation(InitMeshRelativeLoc - FVector(0, 0, Back_zOffset - 10));

	if (GetVelocity().Size() != 0) {


		animInst->Back_LeftLeg_Effector_Loc = FVector(0);
		animInst->Back_LeftLeg_Target_Loc = FVector(0);
		animInst->Back_LeftLeg_Alpha = 0;

		animInst->Back_RightLeg_Effector_Loc = FVector(0);
		animInst->Back_RightLeg_Target_Loc = FVector(0);
		animInst->Back_RightLeg_Alpha = 0;

		animInst->Front_LeftLeg_Effector_Loc = FVector(0);
		animInst->Front_LeftLeg_Target_Loc = FVector(0);
		animInst->Front_LeftLeg_Alpha = 0;

		animInst->Front_RightLeg_Effector_Loc = FVector(0);
		animInst->Front_RightLeg_Target_Loc = FVector(0);
		animInst->Front_RightLeg_Alpha = 0;
	}
	//Front Legs
	FHitResult Front_LeftLeg_Hit;

	const FVector Front_LeftLeg_Loc = GetTransform().TransformPosition(Front_LeftBone_RelativeLocation);
	bool b_Front_LeftFootTrace = UKismetSystemLibrary::SphereTraceSingle(this, Front_LeftLeg_Loc + FVector(0, 0, 50),
		Front_LeftLeg_Loc + FVector(0, 0, -100), 10, ETraceTypeQuery::TraceTypeQuery1, false, ActorToIgnore,
		EDrawDebugTrace::None, Front_LeftLeg_Hit, false);

	FHitResult Front_RightLeg_Hit;

	const FVector Front_RightLeg_Loc = GetTransform().TransformPosition(Front_RightBone_RelativeLocation);
	bool b_Front_RightFootTrace = UKismetSystemLibrary::SphereTraceSingle(this, Front_RightLeg_Loc + FVector(0, 0, 50),
		Front_RightLeg_Loc + FVector(0, 0, -100), 10, ETraceTypeQuery::TraceTypeQuery1, false, ActorToIgnore,
		EDrawDebugTrace::None, Front_RightLeg_Hit, false);

	float Front_zOffset = 0;
	/*
	if (Front_LeftLeg_Hit.ImpactPoint.Z < Front_RightLeg_Hit.ImpactPoint.Z) {
		Front_zOffset = Front_LeftLeg_Hit.ImpactPoint.Z - Front_LeftBone_RelativeLocation.Z;

		animInst->Front_RightLeg_Effector_Loc = Front_RightLeg_Hit.ImpactPoint + FVector(0, 0, 10);
		animInst->Front_RightLeg_Alpha = 1;
		animInst->Front_LeftLeg_Alpha = 0;//0
	}
	else {
		Front_zOffset = Front_RightLeg_Hit.ImpactPoint.Z - Front_RightBone_RelativeLocation.Z;

		animInst->Front_LeftLeg_Effector_Loc = Front_LeftLeg_Hit.ImpactPoint + FVector(0, 0, 10);
		animInst->Front_LeftLeg_Alpha = 1;
		animInst->Front_RightLeg_Alpha = 0;//0
	}*/

	if (Front_LeftLeg_Hit.ImpactPoint.Z < Front_RightLeg_Hit.ImpactPoint.Z) {
		Front_zOffset = Front_LeftLeg_Hit.ImpactPoint.Z - Front_LeftLeg_Loc.Z;
	}
	else {
		Front_zOffset = Front_RightLeg_Hit.ImpactPoint.Z - Front_RightLeg_Loc.Z;
	}

	if (GetVelocity().Size() == 0) {
		animInst->Front_RightLeg_Effector_Loc = Front_RightLeg_Hit.ImpactPoint + FVector(0, 0, 5);
		animInst->Front_LeftLeg_Effector_Loc = Front_LeftLeg_Hit.ImpactPoint + FVector(0, 0, 5);
		animInst->Front_RightLeg_Alpha = 1;
		animInst->Front_LeftLeg_Alpha = 1;
	}

	if (fox_spine1_yOffset_shouldBe >= (Back_zOffset * -1) - Front_zOffset) {
		fox_spine1_yOffset_shouldBe -= DeltaTime * 100;
	}
	else if (fox_spine1_yOffset_shouldBe < (Back_zOffset * -1) - Front_zOffset) {
		fox_spine1_yOffset_shouldBe += DeltaTime * 100;
	}

	//animInst->fox_spine1_yOffset = Front_RightLeg_Hit.ImpactPoint.Z - Front_RightLeg_Loc.Z;// - Back_RightLeg_Hit.ImpactPoint.Z;
	animInst->fox_spine1_yOffset = /*fox_spine1_yOffset_shouldBe; */(Back_zOffset * -1) - Front_zOffset;
	//GetMesh()->SetRelativeLocation(InitMeshRelativeLoc - FVector(0, 0, Back_zOffset - 10));



	//Ik Ends---------------------------------------------------------------------

}


void AmainChar_Fox :: moveForward(float val) {
	if (disableInput_movement) {
		return;
	}

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
	if (disableInput_movement) {
		return;
	}

	VelShouldBe = 200;
	
	if (val == 1) {
		VelShouldBe = 900;
	}
}


void AmainChar_Fox::CameraYaw_z(float val) {
	if (disableInput_camera) {
		return;
	}

	if (!bCanLookAround) {
		return;
	}
	FRotator newR = FRotator(0, 0, 0);
	newR.Yaw += val;
	cameraBoom->AddRelativeRotation(newR);

}

void AmainChar_Fox::CameraPitch_y(float val) {
	if (disableInput_camera) {
		return;
	}

	if (!bCanLookAround) {
		return;
	}
	FRotator newR = cameraBoom->GetRelativeRotation();
	newR.Pitch = FMath::Clamp(newR.Pitch + val, -80.0f, 4.0f);

	cameraBoom->SetRelativeRotation(newR);
}

void AmainChar_Fox::CanLookAround(float val) {
	if (disableInput_camera) {
		return;
	}

	bCanLookAround = false;
	if (val == 1) {
		bCanLookAround = true;
	}
	else {
		cameraBoom->SetRelativeRotation(FRotator(-20, -35, 0.f));
	}
}


void AmainChar_Fox::moveLeftRight(float val) {
	if (disableInput_movement) {
		return;
	}

	if (val == -1) {
		RootComponent->AddWorldRotation(FRotator(0,-50 * GetWorld()->GetDeltaSeconds(),0));
	}
	else if (val == 1) {
		RootComponent->AddWorldRotation(FRotator(0, 50 * GetWorld()->GetDeltaSeconds(), 0));
	}
}
 
void AmainChar_Fox::interact_f() {
	//--------return if disabled
	if (disableInput_interact) {
		return;
	}

	UFox_AnimInstance* animInst = Cast<UFox_AnimInstance>(GetMesh()->GetAnimInstance());
	UkusaGameInstance* gameInst = Cast<UkusaGameInstance>(GetGameInstance());

	//to streach=========|============
	if (What_to_do_with_interact == 0) {
		interact += 50;
		if (interact >= 500)
			interact = 500;
	}
	// to eat mushrooom
	else if (What_to_do_with_interact == 1) {
		if (gameInst->bIsCurrentFoodIsThere) {
			animInst->AnimState = 1;
			animInst->inner_AnimState = 1;
			
			const FRotator YawRotation(0.0f, RootComponent->GetComponentRotation().Yaw, 0.0f);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			OtherActorLoc_ToSnapLoc -= Direction*100;

			OtherActorLoc_ToSnapLoc.Z = RootComponent->GetComponentLocation().Z;
			RootComponent->SetWorldLocation(OtherActorLoc_ToSnapLoc);


		}

		

	}
}


void AmainChar_Fox :: HudManagement() {
	if (What_to_do_with_interact != 0) {
		
	}
}


