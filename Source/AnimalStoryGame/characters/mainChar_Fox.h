// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "mainChar_Fox.generated.h"

UCLASS()
class ANIMALSTORYGAME_API AmainChar_Fox : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AmainChar_Fox();

	/*camera behind the player*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* cameraBoom;

	/* main camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;


	//=======Variable================================
	float VelShouldBe = 400;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "kusaVar", meta = (AllowPrivateAccess = "true"))
	float VelForAnim_MoveFor = 400;


	bool bCanLookAround = false;

	//BoneNames 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "k_BoneName")
	FName Back_Left_LegBoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "k_BoneName")
	FName Back_Right_LegBoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "k_BoneName")
	FName Front_Left_LegBoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "k_BoneName")
	FName Front_Right_LegBoneName;


	FVector Back_LeftBone_RelativeLocation, Back_RightBone_RelativeLocation;
	FVector Front_LeftBone_RelativeLocation, Front_RightBone_RelativeLocation;

	FVector InitMeshRelativeLoc;

	float fox_spine1_yOffset_shouldBe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	float interact;
	/*
	* 0 to stretch motion / elastic effect
	* 1 to eat something / get energy
	* 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	int What_to_do_with_interact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	FVector OtherActorLoc_ToSnapLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	int AnimInst_Idx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	float mileStone_interactVal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	bool playCineMetic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	bool do_changeState_at_mileStone;



	// disable Interact======================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	bool disableInput_movement = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	bool disableInput_camera = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	bool disableInput_interact = false;

	//after mile stone = AMS
	// disable Interact======================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	bool AMS_disableInput_movement = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
		bool AMS_disableInput_camera = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
		bool AMS_disableInput_interact = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
		int AMS_armLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
		int AMS_animInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
		FRotator AMS_CameraRot;


	//power================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
		float powerLvl;// total power it can have is 1000 at base and will be upgrated

	



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void moveForward(float val);

	UFUNCTION()
	void moveLeftRight(float val);

	UFUNCTION()
	void GoFast(float val);

	UFUNCTION()
	void CameraYaw_z(float val);

	UFUNCTION()
	void CameraPitch_y(float val);

	UFUNCTION()
	void CanLookAround(float val);

	void IK(float DeltaTime);

	UFUNCTION()
	void interact_f();

	UFUNCTION(BlueprintImplementableEvent)
	void playAnimation();

};
