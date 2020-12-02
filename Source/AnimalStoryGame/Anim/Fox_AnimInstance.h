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
	/*
	* Anim State 
	* 1 = eating For Energy
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	int AnimState;

	/*
	* inner Anim State
	* 1 = mushroom from ground
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	int inner_AnimState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	class AmainChar_Fox* player;

	UPROPERTY(BlueprintReadWrite, Category = "kusaVar")
	float Player_vel;

	//range from 0 to 500
	UPROPERTY(BlueprintReadWrite, Category = "kusaVarT")
	float interact;


	//actions---------------------------------------------------
	//aatack
	UPROPERTY(BlueprintReadWrite, Category = "kusaVarAttack")
	float attackIndex = 0;

	UPROPERTY(BlueprintReadWrite, Category = "kusaVarAttack")
	bool bPlayAttckAnim = false;





};
