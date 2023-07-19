#include "GameManager.h"
#include <string>

GameManager::GameManager()
{
  m_MineField = std::make_unique<MineField>();
}

void GameManager::GameIntroduction() const
{
  std::string infoText = 
  R"(WELCOME TO MINESWEEPER GAME! 

  SYMBOLS: 
  ⬜ - Unrevealed Tile. 🟦 - Revealed Tile. 🚩 - Flag. 💣 - Mine. 🎆 - Exploded Mine. ✅ - Flagged Right
  ❌ - Flagged Wrong.
  Numbers 1-8 indicate no. of mines in adjacent tiles.

  ACTIONS:
  R - Reveal, F - Flag or Unflagged

  HOW TO PLAY:
  Choose Action and Tile Coordinate: (eg. R23 or F58)
  
  Example 1: R23 - R to Reveal tile, followed by the coordinate you want to reveal. 
  Example 2: F58 - F to Flag or Unflag Tile, followed by tile coordinate that you want to flag or unflag.

  HOW TO WIN:
  Reveal all the tiles without stepping on the mine.
  )";
  
  std::cout << infoText << std::endl;
}

void GameManager::StartGameLoop()
{
  PrintGameBoard();
  
  while(m_GameState == EGameState::EGS_GamePlay)
    {
      do
        {
          ReadValidateNCaptureInput();
          ProcessTileStateChangesBasedOnAction();
        }
        while(! b_ActionCompleted);
      
      PrintGameBoard();
      CheckIfWinOrLose();
    }
}

void GameManager::PrintGameBoard() const
{
  std::cout << "\n     0    1    2    3    4    5   6    7    8" << std::endl;
  for(int x = 0; x < MineField::ROWS; x++)
    {
      std::cout << "  +----+----+----+----+----+----+----+----+----+" << std::endl;
      std::cout << x << " | ";
      for(int y = 0 ; y < MineField::COLS; y++)
        {
          m_MineField->TileAt({x, y}).PrintTile(m_GameState);
          std::cout << " | ";
        }
      std::cout << std::endl;
    }
  std::cout << "  +----+----+----+----+----+----+----+----+----+" << std::endl;
  std::cout << " --------------------------------------------------" << std::endl;
}

const std::string GameManager::ReadInput() const
{
  std::cout << "\nAction: 'R' to reveal, 'F' to flag or unflag." << std::endl << std::endl; 
  std::cout << "Choose an action and pick a tile coordinate (eg. R12 or F56): ";
  std::string userInput;
  std::getline(std::cin, userInput);
  return userInput;
}

void GameManager::ReadValidateNCaptureInput()
{
  std::string userInput = ReadInput();
  
  const char chosenAction = userInput[0];
  const Coordinate pickedTileCoordinate = { userInput[1] - '0', userInput[2] - '0' };
  
  if(! IsActionValid(chosenAction) || ! IsCoordinateValid(pickedTileCoordinate))
  {
    std::cout << "\nINVALID INPUT!, Please Enter the correct input." << std::endl;
    ReadValidateNCaptureInput();
    return;
  }
  else
  {
    m_ChosenAction = chosenAction;
    m_PickedTileCoordinate = pickedTileCoordinate;
  }
}

bool GameManager::IsActionValid(const char action) const
{
  if(action == 'R' || action == 'r' || action == 'F' || action == 'f' || action == 'S' || action == 's')
    return true;
  else
    std::cout << "\nINVALID action entered! ";
    return false;
}

bool GameManager::IsCoordinateValid(const Coordinate& coordinate) const
{
  if((coordinate.X >= 0 && coordinate.X <= 8) && (coordinate.Y >= 0 && coordinate.Y <= 8))
    return true;
  else
    std::cout << "\nINVALID coordinate entered! ";
  return false;
}

  
void GameManager::ProcessTileStateChangesBasedOnAction()
{
  b_ActionCompleted = false;
  Tile& pickedTile = m_MineField->TileAt(m_PickedTileCoordinate);
 
  switch(m_ChosenAction)
    {
      case 'R':
      case 'r':
        ProcessRevealAction(pickedTile);
        break;
      case 'F':
      case 'f':
        ProcessFlagAction(pickedTile);
      break;
    }
}

void GameManager::ProcessRevealAction(Tile& pickedTile)
{
  if(! pickedTile.IsRevealed() && ! pickedTile.IsFlagged())
  {
    pickedTile.SetToRevealed();
    m_RevealedTiles++;
    b_ActionCompleted = true;
                    
    if( pickedTile.HasMine())
      b_SteppedOnMine = true;
    else if( pickedTile.HasNoNeighborMines())
      RevealAllNeighborTiles(pickedTile);
  }
   else
  { std::cout << "\nTHE TILE YOU PICKED IS ALREADY REVEALED, pick a different tile." << std::endl; }
}

void GameManager::ProcessFlagAction(Tile& pickedTile)
{
  if(! pickedTile.IsRevealed())
  {
    pickedTile.ToggleFlag();
    b_ActionCompleted = true;
  }
  else
  { std::cout << "\nA REVEALED TILE CAN'T BE FLAGGED, pick a different tile." << std::endl; }
}

void GameManager::RevealAllNeighborTiles(Tile& noNeighborMinesTile)
{
  Coordinate noNeighborsMinesTileCoordinate = noNeighborMinesTile.GetTileCoordinate();
  // Getting ranges of the coordinates of the neighbor tiles
  const int xStart = std::max(0, noNeighborsMinesTileCoordinate.X - 1);
  const int yStart = std::max(0, noNeighborsMinesTileCoordinate.Y - 1);
  const int xEnd = std::min(MineField::ROWS - 1, noNeighborsMinesTileCoordinate.X + 1);
  const int yEnd = std::min(MineField::COLS - 1, noNeighborsMinesTileCoordinate.Y + 1);

  for(Coordinate coordinate = {xStart, yStart}; coordinate.X <= xEnd; coordinate.X++)
    {
      for(coordinate.Y = yStart; coordinate.Y <= yEnd; coordinate.Y++)
        {
          Tile& currNeighborTile = m_MineField->TileAt(coordinate);
          if(! currNeighborTile.IsRevealed())
          {
            currNeighborTile.SetToRevealed();
            m_RevealedTiles++;
            
            if(currNeighborTile.HasNoNeighborMines()) 
              RevealAllNeighborTiles(currNeighborTile); // Recursively revealing neighboring tiles
          }
        }
    }
  return;
}

void GameManager::CheckIfWinOrLose()
{
  if(b_SteppedOnMine)
  {
    m_GameState = EGameState::EGS_GameOver;
    PrintGameBoard();
    std::cout << "\nOops, Stepped on the Mine. GAME OVER! 💀 " << std::endl;
  }

  if(m_RevealedTiles == m_SafeTiles)
  {
    m_GameState = EGameState::EGS_GameOver;
    PrintGameBoard();
    std::cout << "\nGame Over. Congratulations, 🎉 You Win! Thank you for playing. :) " << std::endl;
   }
}
  
  


