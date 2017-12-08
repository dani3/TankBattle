#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	ATank * GetControlledTank() const;
	ATank * GetPlayerTank() const;
};
