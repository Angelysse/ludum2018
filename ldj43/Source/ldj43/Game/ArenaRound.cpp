#include "ArenaRound.h"

//=====================
//Constructors

ArenaRound::ArenaRound():
	roundNumber{0u},
	totalWaves{3u},
	currentWave{0u}
{
	//Nothing here
}

//=====================
//Methods

bool ArenaRound::isLastWave()
{
	return totalWaves == currentWave;
}

//-----------------

void ArenaRound::nextRound()
{
	roundNumber++;
	computeWavesData();
}

//-----------------

uint32 ArenaRound::nextWave()
{
	currentWave++;
	return getNumberEnemiesForCurrentWave();
}

//-----------------

void ArenaRound::computeWavesData()
{
	currentWave = 0u;
	totalWaves = 3u;
}

//-----------------

uint32 ArenaRound::getNumberEnemiesForCurrentWave()
{
	return 5 + currentWave * roundNumber * 0.5;
}