#include "Coordinate.h"
#include <iostream>

namespace TileTypes
{
const std::string Hidden = "⬜";
const std::string Revealed = "🟦";
const std::string Exploded = "🎆";
const std::string Flagged = "🚩";
const std::string FlaggedRight = "✅";
const std::string FlaggedWrong = "❌";
const std::string Mine = "💣";
const std::string one = "1 ";
const std::string two = "2 ";
const std::string three = "3 ";
const std::string four = "4 ";
const std::string five = "5 ";
const std::string six = "6 ";
const std::string seven = "7 ";
const std::string eight = "8 ";
};

class Tile
{
private:
enum class ETileState : unsigned char
{ ETS_Hidden, ETS_Flagged, ETS_Revealed };

ETileState m_TileState = ETileState::ETS_Hidden;
Coordinate m_TileCoordinate = {-1, -1}; 
unsigned int m_NeighborMines = 0;
bool b_HasMine = false;

public:
void PlaceMineAtTile();

void SetNeighborMinesCount(int mineCount);

void PrintTile(bool bGameRunning) const;

void SetToRevealed(); 

void ToggleFlag();

inline bool IsRevealed() const { return m_TileState == ETileState::ETS_Revealed; }

inline bool IsFlagged() const { return m_TileState == ETileState::ETS_Flagged; }

inline Coordinate GetTileCoordinate() const { return m_TileCoordinate; }
inline void SetTileCoordinate(const Coordinate& coordinate) { m_TileCoordinate = coordinate; }

inline bool HasMine() const { return b_HasMine; };

inline bool HasNoNeighborMines() const { return m_NeighborMines == 0; };

private:
void Print1() const;

void Print2() const;

void PrintTileWithNeighborMines(int neighborMines) const;
};