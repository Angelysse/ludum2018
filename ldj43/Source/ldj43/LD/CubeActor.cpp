#include "CubeActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

UMaterial* ACubeActor::_mat = nullptr;

ACubeActor::ACubeActor()
{
	UStaticMeshComponent* CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshContainer(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshContainer.Succeeded())
	{
		CubeMesh->SetStaticMesh(MeshContainer.Object);
		SetRootComponent(CubeMesh);
	}

	if (!_mat)
	{
		ConstructorHelpers::FObjectFinder<UMaterial> MatContainer(TEXT("Material'/Game/Resources/Materials/StyleWall_MAT.StyleWall_MAT'"));
		if (MatContainer.Succeeded())
			_mat = MatContainer.Object;
	}
}

void ACubeActor::BeginPlay()
{
	if(_mat)
		Cast<UStaticMeshComponent>(RootComponent)->SetMaterial(0, UMaterialInstanceDynamic::Create(_mat, this));
}

void ACubeActor::ScaleWall(const FVector& scale)
{
	SetActorScale3D(scale);
	//Cast<UStaticMeshComponent>(RootComponent)->GetMaterial(0)->SET_TILING_FU_UE4
}