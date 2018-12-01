#include "CubeActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"


ACubeActor::ACubeActor()
{
	UStaticMeshComponent* CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshContainer(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshContainer.Succeeded())
	{
		CubeMesh->SetStaticMesh(MeshContainer.Object);
		SetRootComponent(CubeMesh);
	}
}