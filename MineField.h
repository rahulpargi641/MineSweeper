#pragma once
#include "Tile.h"

class MineField
{
public:
static constexpr int ROWS = 9;
static constexpr int COLS = 9;
static constexpr int MinesToPlace = 5;

private:
Tile m_Tiles[ROWS][COLS];

public:
MineField();

inline Tile& TileAt(const Coordinate& coordinate) { return m_Tiles[coordinate.X][coordinate.Y]; };
inline const Tile& TileAt(const Coordinate& coordinate) const { return m_Tiles[coordinate.X][coordinate.Y]; }

private:
void InitTileCoordinates();

void DistributeMinesRandomly(const int nMines);

void SetNeighborMinesCountForAllTiles();

int CountNeighborMines(const Coordinate& tileCoordinate) const;
};