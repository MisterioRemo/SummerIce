#include "Citizen.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"

#include "Components/WidgetComponent.h"
#include "Widget/WidgetLibrary.h"
#include "Widget/BubbleWidget.h"

ACitizen::ACitizen(const FObjectInitializer& ObjectInitializer)
  :Super(ObjectInitializer)
{
  PrimaryActorTick.bCanEverTick = false;

  // если игрок входит в зону OuterBoxComponent, то он может поговорить с нпс
  _OuterBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OuterDialogBoxComponent"));
  _OuterBoxComponent->SetCollisionProfileName(TEXT("Trigger"));
  _OuterBoxComponent->InitBoxExtent(FVector(40.0f, 40.0f, 30.0f));
  _OuterBoxComponent->SetRelativeLocation(FVector(0.0f, 20.0f, 0.0f));
  _OuterBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  _OuterBoxComponent->SetGenerateOverlapEvents(true);
  SetRootComponent(_OuterBoxComponent);

  // чтобы баблы речи игрока не перекрывали нпс, то в зоне InnerBoxComponent нельзя начать разговор
  _InnerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("InnerDialogBoxComponent"));
  _InnerBoxComponent->SetCollisionProfileName(TEXT("Trigger"));
  _InnerBoxComponent->InitBoxExtent(FVector(16.0f, 40.0f, 30.0f));
  _InnerBoxComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
  _InnerBoxComponent->SetGenerateOverlapEvents(true);
  _InnerBoxComponent->SetupAttachment(RootComponent);

  _CitizenDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerDirection"));
  _CitizenDirection->SetupAttachment(_InnerBoxComponent);

  _CitizenSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PlayerSprite"));
  _CitizenSprite->SetupAttachment(_CitizenDirection);

  _DialogBubbleComponent = CreateDefaultSubobject<UWidgetComponent>("DialogBubbleWidget");
  _DialogBubbleComponent->SetupAttachment(RootComponent);

  _InteractiveSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("IneractableIcon"));
  _InteractiveSprite->SetupAttachment(RootComponent);
  _InteractiveSprite->SetCollisionProfileName(TEXT("NoCollision"));

  // AddDynamic должно вызываться единожды для одной функции,
  // но OnComponentEndOverlap не работает, если "связывать" в конструкторе объекта
  _OuterBoxComponent->OnComponentBeginOverlap.RemoveDynamic(this, &ACitizen::OnPlayerEnterBoxComponent);
  _OuterBoxComponent->OnComponentEndOverlap.RemoveDynamic(this, &ACitizen::OnPlayerExitBoxComponent);
  _InnerBoxComponent->OnComponentBeginOverlap.RemoveDynamic(this, &ACitizen::OnPlayerEnterBoxComponent);
  _InnerBoxComponent->OnComponentEndOverlap.RemoveDynamic(this, &ACitizen::OnPlayerExitBoxComponent);

  _OuterBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACitizen::OnPlayerEnterBoxComponent);
  _OuterBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACitizen::OnPlayerExitBoxComponent);
  _InnerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACitizen::OnPlayerEnterBoxComponent);
  _InnerBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACitizen::OnPlayerExitBoxComponent);
}

void ACitizen::BeginPlay()
{
  Super::BeginPlay();

  if (UWidgetLibrary::DialogBubbleClass) {
    _DialogBubbleComponent->SetWidgetClass(UWidgetLibrary::DialogBubbleClass);
    _DialogBubbleComponent->SetWidgetSpace(EWidgetSpace::Screen);
    _DialogBubbleComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
    //_DialogBubbleComponent->SetDrawSize(FVector2D(500.0f, 500.0f));
  }
}

void ACitizen::OnPlayerEnterBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                         bool bFromSweep, const FHitResult& SweepResult)
{
  if (OverlappedComp->GetName() == TEXT("OuterDialogBoxComponent"))
    OnPopUp(); // вызов в BP, добавление лупы
  if (OverlappedComp->GetName() == TEXT("InnerDialogBoxComponent"))
    OnPopUpEnd(); // вызов в BP, удаление лупы
}

void ACitizen::OnPlayerExitBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
  if (OverlappedComp->GetName() == TEXT("OuterDialogBoxComponent"))
    OnPopUpEnd(); // вызов в BP, удаление лупы
  if (OverlappedComp->GetName() == TEXT("InnerDialogBoxComponent"))
    OnPopUp(); // вызов в BP, добавление лупы
}

//void ACitizen::Tick(float DeltaTime)
//{
//  Super::Tick(DeltaTime);
//}

// BEGIN InteractInterface
void ACitizen::ShowDialogWidget(const FString * Text /* = nullptr*/, const bool & bCanChooseLine /* = false*/)
{
  auto Widget = Cast<UBubbleWidget>(_DialogBubbleComponent->GetUserWidgetObject());
  if (Text && Widget) {
    Widget->SetVisibility(ESlateVisibility::Visible);
    Widget->SetText(*Text);
  }
}

void ACitizen::HideDialogWidget()
{
  _DialogBubbleComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
}

ECharacter ACitizen::GetName() const
{
  return _CharacterName;
}
int32 ACitizen::GetDialogId() const
{
  return _DialogId;
}
// END InteractInterface
