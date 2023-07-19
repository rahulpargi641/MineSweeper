#pragma once
#include <memory>
#include "MineField.h"

class GameManager
{
private:
enum EGameState : unsigned char
{ EGS_GamePlay = 1, EGS_GameOver = 0 };

EGameState m_GameState = EGameState::EGS_GamePlay;
static constexpr int m_SafeTiles = (MineField::ROWS * MineField::COLS) - MineField::MinesToPlace;

bool b_SteppedOnMine = false;
unsigned int m_RevealedTiles = 0;
bool b_UserClicked = false;

bool b_ActionCompleted = false;
char m_ChosenAction;
Coordinate m_PickedTileCoordinate;

std::unique_ptr<MineField> m_MineField;

public:
GameManager();

void GameIntroduction() const;

void StartGameLoop();

private:
void PrintGameBoard() const;

const std::string ReadInput() const;

void ReadValidateNCaptureInput();

bool IsActionValid(const char action) const;

bool IsCoordinateValid(const Coordinate& coordinate) const;

void ProcessTileStateChangesBasedOnAction();

void ProcessRevealAction(Tile& pickedTile);

void ProcessFlagAction(Tile& pickedTile);

void RevealAllNeighborTiles(Tile& emptyNeighborsTile);

void CheckIfWinOrLose();
};