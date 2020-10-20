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

};
