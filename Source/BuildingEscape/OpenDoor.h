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

	float GetTotalMassOfActorsInPlate();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere)
	float openAngle = 90;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	AActor* owner;		//�ű����ص�Actor����

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.0f;	//�ſ������Զ����ŵ�ʱ��

	float LastDoorOpenTime;			//�ſ�����ʱ��
};
