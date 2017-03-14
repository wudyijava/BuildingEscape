// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

//���嶯̬�ಥ����
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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

	float GetTotalMassOfActorsInPlate();

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnCloseRequest;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//UPROPERTY(VisibleAnywhere)
	//float openAngle = 90;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	AActor* owner;		//�ű����ص�Actor����

	//UPROPERTY(EditAnywhere)
	//float DoorCloseDelay = 1.0f;	//�ſ������Զ����ŵ�ʱ��

	//float LastDoorOpenTime;			//�ſ�����ʱ��
};
