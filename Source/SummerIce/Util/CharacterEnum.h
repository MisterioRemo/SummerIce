#pragma once
#include "CharacterEnum.generated.h"

UENUM(BlueprintType)
enum class ECharacter: uint8
{
  Lavinia,
  Elizabeth,
  Object,
  Error
};

// Enum to String
static FString GetCharacterAsString(const ECharacter & Character)
{
  return (UEnum::GetValueAsString(Character)).RightChop(12);
}

// String to Enum
static ECharacter GetCharacterFromString(const FString & Name)
{
  FString Character = Name.ToLower();
  if (Character.Equals("lavinia"))
    return ECharacter::Lavinia;
  else if (Character.Equals("elizabeth"))
    return ECharacter::Elizabeth;
  else if (Character.Equals("object"))
    return ECharacter::Object;

  return ECharacter::Error;
}
