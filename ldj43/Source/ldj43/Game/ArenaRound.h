#pragma once

class ArenaRound
{
	public:
		//Variables
		uint32	roundNumber;
		uint32	totalWaves;
		uint32	currentWave;

		//Constructors
		ArenaRound();

		//Methods
		bool	isLastWave();
		void	nextRound();
		uint32	nextWave();
		void	computeWavesData();
		uint32	getNumberEnemiesForCurrentWave();
};