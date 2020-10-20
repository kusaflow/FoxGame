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

	bool bCanLookAround = false;

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
	void GoFast(float val);

	UFUNCTION()
	void CameraYaw_z(float val);

	UFUNCTION()
	void CameraPitch_y(float val);

	UFUNCTION()
	void CanLookAround(float val);

};
