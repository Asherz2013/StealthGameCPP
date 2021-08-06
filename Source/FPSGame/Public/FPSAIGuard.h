// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/TargetPoint.h"
#include "GameFramework/Character.h"

#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
// Needs to be uint8 if we want to use it in Blueprints!
enum class EAIState : uint8
{
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* HeardPawn, const FVector& Location, float Volume);

	FTimerHandle TimerHandle_ResetOrientation;

	FRotator OriginalRotation;

	UFUNCTION()
	void ResetOrientation();

	UPROPERTY(ReplicatedUsing=OnRep_GuardState)
	EAIState GuardState;

	void SetGuardState(EAIState NewState);

	UFUNCTION()
	void OnRep_GuardState();
	
	UFUNCTION(BlueprintImplementableEvent, Category="AI")
	void OnGuardStateChanged(EAIState NewState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Challenge Code

	// For a UPROPERTY you can have "meta = (EditorCondition = <value>)" to make specific variables readonly if the condition is not met
	
	UPROPERTY(EditInstanceOnly, Category="AI")
	TArray<ATargetPoint*> PatrolPoints;

	int32 CurrentPatrolPoint;

	void MoveToNextPatrolPoint();
};
