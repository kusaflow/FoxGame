// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Fox_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALSTORYGAME_API UFox_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "AnimProperty")
		void update();

	//--------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	class AmainChar_Fox* player;

	UPROPERTY(BlueprintReadWrite, Category = "kusaVar")
	float Player_vel;

	UPROPERTY(BlueprintReadWrite, Category = "kusaVar")
	float fox_spine1_yOffset;

	//Effector Target Alpha 
	//-------Back Left Leg 
	UPROPERTY(BlueprintReadWrite, Category = "IK_kusaVar")
		FVector Back_LeftLeg_Effector_Loc;

	UPROPERTY(BlueprintReadWrite, Category = "IK_kusaVar")
		FVector Back_LeftLeg_Target_Loc;

	UPROPERTY(BlueprintReadWrite, Category = "IK_kusaVar")
		float Back_LeftLeg_Alpha;

	//-------Back Right Leg 
	UPROPERTY(BlueprintReadWrite, Category = "IK_kusaVar")
		FVector Back_RightLeg_Effector_Loc;

	UPROPERTY(BlueprintReadWrite, Category = "IK_kusaVar")
		FVector Back_RightLeg_Target_Loc;

	UPROPERTY(BlueprintReadWrite, Category = "IK_kusaVar")
		float Back_RightLeg_Alpha;


	//-------Front Left Leg 
	UPROPERTY(BlueprintReadWrite, Category = "IK_kusaVar")
		FVector Front_LeftLeg_Effector_Loc;

	UPROPERTY(BlueprintReadWrite, Category = "IK_kusaVar")
		FVector Front_LeftLeg_Target_Loc;

	UPROPERTY(BlueprintReadWrite, Category = "IK_kusaVar")
		float Front_LeftLeg_Alpha;

	//-------Front Right Leg 
	UPROPERTY(BlueprintReadWrite, Category = "IK_kusaVar")
		FVector Front_RightLeg_Effector_Loc;

	UPROPERTY(BlueprintReadWrite, Category = "IK_kusaVar")
		FVector Front_RightLeg_Target_Loc;

	UPROPERTY(BlueprintReadWrite, Category = "IK_kusaVar")
		float Front_RightLeg_Alpha;

};
