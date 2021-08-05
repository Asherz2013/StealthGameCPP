// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UParticleSystem;

UCLASS()
class FPSGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp;

	/* Total impulse added to the character on overlap
		Marked "EditInstanceOnly" to allow in-level editing of this property per instance */
	UPROPERTY(EditInstanceOnly, Category="LaunchPad")
	int32 LaunchStrength;

	// Angle added on top of the actor rotation to launch the character.
	UPROPERTY(EditInstanceOnly, Category="LaunchPad")
	float LaunchPitchAngle;

	UPROPERTY(EditDefaultsOnly, Category="LaunchPad")
	UParticleSystem* ActivateLaunchPadEffect;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
