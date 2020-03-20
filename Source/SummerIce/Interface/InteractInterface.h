#pragma once

#include "UObject/Interface.h"
#include "InteractInterface.generated.h"


UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()

public:
	UInteractInterface(const class FObjectInitializer& ObjectInitializer);
};

class SUMMERICE_API IInteractInterface
{
	GENERATED_BODY()

public:
	virtual void ShowDialogWidget() = 0;
};
