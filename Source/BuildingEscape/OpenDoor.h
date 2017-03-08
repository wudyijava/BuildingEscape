// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere)
	float openAngle = 90;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	//触发者，Pawn是一种特殊的Actor，可以由人类玩家或AI（人工智能）来进行控制
	AActor* ActorThatOpens;

	AActor* owner;		//脚本挂载的Actor对象

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.0f;	//门开启后到自动关门的时长

	float LastDoorOpenTime;			//门开启的时间
};
