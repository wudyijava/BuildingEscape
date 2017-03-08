// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();	//��ʼ��ʱ
	}

	//�������ʱ��ﵽ���ʱ�䣬����
	if (GetWorld()->GetTimeSeconds() - DoorCloseDelay > LastDoorOpenTime)
	{
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor() {
	FRotator newRotator = FRotator(0.0f, openAngle, 0.0f);
	owner->SetActorRotation(newRotator);
}

void UOpenDoor::CloseDoor()
{
	owner->SetActorRotation(FRotator::ZeroRotator);
}

