// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSObjectiveActor.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
	// Create a Static Mesh Component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	// Turn off its collision
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Make the Static Mesh Component the ROOT component
	RootComponent = MeshComp;
	
	// Create a Sphere Component
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	// Setup Collision to Query Only
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// Ignore EVERYTHING
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	// Apart from the Pawn
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	// Make it a Child of the Static Mesh Component
	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSObjectiveActor::PlayerEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickupFX, GetActorLocation());
}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayerEffects();

	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if(MyCharacter)
	{
		MyCharacter->bIsCarryObjective = true;

		Destroy();
	}
}

