// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePossessPawn.h"

// Sets default values
ABasePossessPawn::ABasePossessPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	camera->SetupAttachment(RootComponent);
	camera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	camera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABasePossessPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePossessPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle movement based on our "MoveX" and "MoveY" axes
	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}

}

// Called to bind functionality to input
void ABasePossessPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond when our "Possess" key is pressed or released.
	InputComponent->BindAction("Possess", IE_Pressed, this, &ABasePossessPawn::Possess);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	InputComponent->BindAxis("MoveX", this, &ABasePossessPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &ABasePossessPawn::Move_YAxis);
}

void ABasePossessPawn::Move_XAxis(float AxisValue)
{
	// Move at 100 units per second forward or backward
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 10000.0f;

}

void ABasePossessPawn::Move_YAxis(float AxisValue)
{

	//mesh->AddForce(GetActorForwardVector() * 200.0f);
	
	//TArray<UStaticMeshComponent> StaticComps;
	//auto mesh = GetComponents<UStaticMeshComponent>(StaticComps);
	
	
	//mesh.AddForce(AxisValue*100000,nullptr,false);
}

void ABasePossessPawn::Possess()
{

}

