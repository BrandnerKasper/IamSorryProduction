// Fill out your copyright notice in the Description page of Project Settings.


#include "PossesComponent.h"

// Sets default values for this component's properties
UPossesComponent::UPossesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPossesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPossesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPossesComponent::Possess()
{
	UE_LOG(LogTemp, Warning, TEXT("Possessed"));
	TArray<AActor*> pawnys;
	APawn* Pawn = Cast<APawn>(GetOwner());
	Pawn->GetOverlappingActors(pawnys, APawn::StaticClass());
	if (pawnys.Num() != 0)
	{
		APawn* pawny = Cast<APawn>(pawnys[0]);
		Pawn->Controller->Possess(pawny);
	}
}