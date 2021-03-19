// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"

#include "BasePossessPawn.generated.h"


UCLASS()
class IAMSORRYONE_API ABasePossessPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePossessPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void Possess();
	
	//Scene Components haben nixo physixo
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;
	
	//Primitive Component ist das "oberste" component in der Vererbungshierarchie mit Physics SKILLSSZZZ
	UPROPERTY(EditAnywhere)
		UPrimitiveComponent* rootWithPhysics;

	UPROPERTY(EditAnywhere)
		UCameraComponent* camera;

	UPROPERTY(EditAnywhere)
		FVector RelativeToBall = FVector(-500, 0, 600);

	UPROPERTY(EditAnywhere)
		USphereComponent* SphereCollision;
};
