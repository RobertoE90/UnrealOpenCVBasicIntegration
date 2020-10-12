

#include "BackgroundImageDisplayActor.h"

ABackgroundImageDisplayActor::ABackgroundImageDisplayActor()
{	
    PrimaryActorTick.bCanEverTick = false;

    USceneComponent* WebCamRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WebCameraCaptureRootSceneComponent"));
    RootComponent = WebCamRootComponent;
    //adds the static mesh component 
    UStaticMeshComponent* StaticMeshPlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TextureDisplayMesh"));

    auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
    if (MeshAsset.Object != nullptr)
    {
        StaticMeshPlaneComponent->SetStaticMesh(MeshAsset.Object);
    }

    //StaticMeshPlaneComponent->SetWorldScale3D(FVector(ResizeDeminsions.X / ResizeDeminsions.Y, 1, 1));
    StaticMeshPlaneComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    StaticMeshPlaneComponent->SetRelativeRotation(FRotator(0, -90, 90));

    auto MaterialAsset = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Materials/M_WebCam.M_WebCam'"));
    if (MaterialAsset.Object != nullptr)
    {
        RenderTextureDynamicInstanceMaterial = UMaterialInstanceDynamic::Create(MaterialAsset.Object, this, TEXT("WebCamRendererMaterialInstance"));
        StaticMeshPlaneComponent->SetMaterial(0, RenderTextureDynamicInstanceMaterial);
    }
}

void ABackgroundImageDisplayActor::Initialize(AWebCamReader* WebCamReader)
{
    WebCamReader->OnTextureInitialized.AddUObject(this, &ABackgroundImageDisplayActor::OnDisplayTextureInitialized);
}

void ABackgroundImageDisplayActor::BeginPlay()
{
	Super::BeginPlay();	
}

void ABackgroundImageDisplayActor::OnDisplayTextureInitialized(FVector2D Size, UTexture2D* Texture)
{
    RenderTextureDynamicInstanceMaterial->SetTextureParameterValue(TEXT("Texture"), Texture);
}
