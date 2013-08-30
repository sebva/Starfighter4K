#ifndef ENUMERATION_H
#define ENUMERATION_H

enum Action
{
    Top = 1,
    Bottom = 2,
    Shoot = 3,
    NormalBonus = 4,
    aSpecialBonus = 5,
    Pause = 6
};

enum Shooter
{
    Player1 = 1,Player2 = 2,Alien = 3,Black = 4, Other = 5
};

enum TypeProjectiles
{
    ProjSimple = 1,ProjCross = 2,ProjV = 3,ProjAlien = 4, Nothing = 5
};

enum TypeItem
{
    tProj = 1,tAsteroid = 2,tSmallAsteroid = 3,tBonus = 4,tAlien = 5,tSupernova = 6,tSpaceship = 7, tBlackShip = 8
};

enum SizeFire
{
    sLeft1 = 1, sLeft2 = 2, sRight1 = 3, sRight2 = 4, sBoth = 5
};

enum GameMode
{
    Timer = 1,DeathMatch = 2
};

enum SpaceshipType
{
    NoSpaceShip = 0, SpaceshipType1 = 1, SpaceshipType2 = 2, SpaceshipType3 = 3
};

enum Difficulty
{
    Asteroids = 0x00000001, AlienMothership = 0x00000010, Satellites = 0x00000100, Supernovae = 0x00001000, BlackSquadron = 0x00010000
};

enum TypeBonus
{
    TypeBonusHP                 = 0,
    TypeBonusProjectile         = 1,
    TypeBonusInvicibility       = 2,
    TypeBonusShield             = 3,
    TypeBonusNothing            = 1000
};

enum TypeSpecialBonus
{
    TypeSpecialBonusFreeze = 0,
    TypeSpecialBonusAntiGravity = 1,
    TypeSpecialBonusGuidedMissile = 2,
    TypeSpecialBonusTrackingMissile = 3,
    TypeSpecialBonusOmnidirectionalShot = 4,
    TypeSpecialBonusNothing = 1000
};

enum BonusState {
    BonusStateActivated,
    BonusStateReady,
    BonusStateCooldown,
    BonusStateNoBonus
};

enum Sounds
{
    SatelliteSound = 1, ShootSound = 2, SupernovaSound = 3
};

#endif // ENUMERATION_H
