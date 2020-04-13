#include "Citizen.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"

#include "Components/WidgetComponent.h"
#include "Util/WidgetLibrary.h"
#include "Widget/BubbleWidget.h"

ACitizen::ACitizen()
{
	PrimaryActorTick.bCanEverTick = true;

	_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	_BoxComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	_BoxComponent->InitBoxExtent(FVector(16.0f, 100.0f, 16.0f));
	_BoxComponent->SetRelativeLocation(FVector(0.0f, 50.0f, 0.0f));
	_BoxComponent->SetGenerateOverlapEvents(true);
	SetRootComponent(_BoxComponent);

	_CitizenDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerDirection"));
	_CitizenDirection->SetupAttachment(RootComponent);

	_CitizenSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PlayerSprite"));
	_CitizenSprite->SetupAttachment(_CitizenDirection);

	_DialogBubbleComponent = CreateDefaultSubobject<UWidgetComponent>("DialogBubbleWidget");
	_DialogBubbleComponent->SetupAttachment(RootComponent);

	_DialogId = 0;
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

void ACitizen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

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
	return 0;
}
// END InteractInterface
