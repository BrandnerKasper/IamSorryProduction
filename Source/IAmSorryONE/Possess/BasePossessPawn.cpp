// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePossessPawn.h"

// Sets default values
ABasePossessPawn::ABasePossessPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	camera->SetRelativeLocation(FVector(0, 0, 0));
	camera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	SetPhysicsRoot();

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/EditorMeshes/EditorSphere.EditorSphere'"));
	mesh->SetStaticMesh(MeshAsset.Object);
	mesh->SetWorldScale3D(FVector(0.5, 0.5, 0.5));
	mesh->SetSimulatePhysics(true);
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
	rootWithPhysics->AddForce(FVector(1, 0, 0) * AxisValue * 100000.0f);
	camera->SetWorldLocation(rootWithPhysics->GetComponentTransform().GetLocation() + FVector(-250,0,250));
}

void ABasePossessPawn::Move_YAxis(float AxisValue)
{
	rootWithPhysics->AddForce(FVector(0,1,0) * AxisValue* 100000.0f);
	camera->SetWorldLocation(rootWithPhysics->GetComponentTransform().GetLocation() + FVector(-250, 0, 250));
}

void ABasePossessPawn::Possess()
{

}


void ABasePossessPawn::SetPhysicsRoot()
{
	TArray<UPrimitiveComponent*> Comps;
	GetComponents(Comps);
	rootWithPhysics = (Comps[0]);
	this->GetComponentByClass(StaticClass());
}

