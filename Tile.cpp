#include "Tile.h"
#include <assert.h>

void Tile::PlaceMineAtTile()
{
  assert(!b_HasMine);

  b_HasMine = true;
}

void Tile::SetNeighborMinesCount(int mineCount)
{
  assert(m_NeighborMines == 0);

  m_NeighborMines = mineCount;  
}

void Tile::PrintTile(bool gameRunning) const
{
  if(gameRunning)
    Print1(); // If the game is running 
  else
    Print2(); // If the game is Over. This means it will be only called 1 time, at the end of the game.
}

void Tile::Print1() const
{
  switch(m_TileState)
  {
    case ETileState::ETS_Hidden:
      std::cout << TileTypes::Hidden;
      break;
    case ETileState::ETS_Flagged:
      std::cout << TileTypes::Flagged;
      break;
    case ETileState::ETS_Revealed:
      if(! HasMine())
        PrintTileWithNeighborMines(m_NeighborMines);
      else
        std::cout << TileTypes::Exploded;
      break; 
   }
}

void Tile::Print2() const
{
  switch(m_TileState)
  {
    case ETileState::ETS_Hidden:
      if( HasMine())
        std::cout << TileTypes::Mine;
      else
        std::cout << TileTypes::Hidden;
      break;
    case ETileState::ETS_Flagged:
      if( HasMine())
        std::cout << TileTypes::FlaggedRight;
      else 
        std::cout << TileTypes::FlaggedWrong; 
      break;
    case ETileState::ETS_Revealed:
      if(! HasMine())
        PrintTileWithNeighborMines(m_NeighborMines); 
      else
        std::cout << TileTypes::Exploded;
      break; 
    }
}

void Tile::PrintTileWithNeighborMines(int neighborMines) const
{
  assert(neighborMines >=0 && neighborMines <= 8);
  
  switch(neighborMines)
    {
      case 1:
      std::cout << TileTypes::one;
      break;
      case 2:
      std::cout << TileTypes::two;
      break;
      case 3:
      std::cout << TileTypes::three;
      break;
      case 4:
      std::cout << TileTypes::four;
      break;
      case 5:
      std::cout << TileTypes::five;
      break;
      case 6:
      std::cout << TileTypes::six;
      break;
      case 7:
      std::cout << TileTypes::seven;
      break;
      case 8:
      std::cout << TileTypes::eight;
      break;
      default:
      std::cout << TileTypes::Revealed;
      break;
    }
}

void Tile::SetToRevealed()
{
  assert (! IsRevealed() && ! IsFlagged());
  m_TileState = ETileState::ETS_Revealed;
}

void Tile::ToggleFlag()
{
  assert(! IsRevealed());

  if(m_TileState == ETileState::ETS_Hidden)
    m_TileState = ETileState::ETS_Flagged;
  else
    m_TileState = ETileState::ETS_Hidden;
}






