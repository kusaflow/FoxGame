// Fill out your copyright notice in the Description page of Project Settings.


#include "Fox_AnimInstance.h"
#include "../characters/mainChar_Fox.h"

void UFox_AnimInstance::NativeInitializeAnimation() {

}

void UFox_AnimInstance::update() {

	player = Cast<AmainChar_Fox>(TryGetPawnOwner());

	if (player) {
		//Player_vel = player->
		Player_vel = player->VelForAnim_MoveFor;
		interact = player->interact;
	}

}