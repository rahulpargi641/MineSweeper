#include "MineField.h";
#include <random>
#include <assert.h>

MineField::MineField()
{
  InitTileCoordinates();
  DistributeMinesRandomly(MinesToPlace);
  SetNeighborMinesCountForAllTiles();
}

void MineField::InitTileCoordinates()
{
  for(Coordinate coordinate = {0, 0}; coordinate.X  < ROWS; coordinate.X++)
      for(coordinate.Y = 0; coordinate.Y < COLS; coordinate.Y++)
          TileAt(coordinate).SetTileCoordinate(coordinate);
}

void MineField::DistributeMinesRandomly(const int nMines)
{
  assert(nMines > 0 && nMines < ROWS * COLS);
  
  std::random_device randomDevice;
  std::mt19937 rNG(randomDevice()); // rng - Random Number Generator
  std::uniform_int_distribution<int> xDist(0, ROWS - 1);
  std::uniform_int_distribution<int> yDist(0, COLS - 1);

  for(int i = 0; i < nMines; i++)
    {
      Coordinate randMinePos;
      do 
      { randMinePos = { xDist(rNG), yDist(rNG) }; }
      while(TileAt(randMinePos).HasMine());

      TileAt(randMinePos).PlaceMineAtTile();
    }
}

void MineField::SetNeighborMinesCountForAllTiles()
{
  for(Coordinate coordinate = {0, 0}; coordinate.X < ROWS; coordinate.X++)
    {
      for(coordinate.Y = 0; coordinate.Y < COLS; coordinate.Y++)
        {
          int count = CountNeighborMines(coordinate);
          TileAt(coordinate).SetNeighborMinesCount(count);
        }
    }
}

int MineField::CountNeighborMines(const Coordinate& tileCoordinate) const
{
  const int xStart = std::max(0, tileCoordinate.X - 1);
  const int yStart = std::max(0, tileCoordinate.Y - 1);
  const int xEnd = std::min(ROWS - 1, tileCoordinate.X + 1);
  const int yEnd = std::min(COLS - 1, tileCoordinate.Y + 1);

  int count = 0;
  for(Coordinate coordinate = {xStart, yStart}; coordinate.X <= xEnd; coordinate.X++)
    {
      for(coordinate.Y = yStart; coordinate.Y <= yEnd; coordinate.Y++)
        {
          if(TileAt(coordinate).HasMine())
            count++;
        }
    }
  return count;
}


