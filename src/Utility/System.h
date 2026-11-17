//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;

class ConsoleText;

class System
{
public:
	static Logger log;

	static string glVendor;
	static string glVersion;
	static string glRenderer;
	static string shaderVersion;
	static string glExtensions;

	static string bobVersion;

	static void initSystemInfo();
	static void initClockAndTimeZone();


	static sp<ConsoleText> totalRendersText;
	static sp<ConsoleText> totalUpdatesText;
	static sp<ConsoleText> rendersPerSecondText;
	static sp<ConsoleText> averageRendersPerSecondText;
	static sp<ConsoleText> updatesPerSecondText;
	static sp<ConsoleText> rendersSkippedText;
	static sp<ConsoleText> updatesSkippedText;
	static sp<ConsoleText> averageTicksPerFrameText;
	static sp<ConsoleText> averageTicksPerUpdateText;
	static sp<ConsoleText> onlineStatusText;

	static sp<ConsoleText> upTimeText;

	const static int amtTicksTexts = 10;
	static sp<ConsoleText> ticksText[amtTicksTexts];


private:
	static long long lastRenderTime;
	static long long lastUpdateTime;
	static int ticksTextCount;
	static int averageTicksPerRenderLastSecond;
	static int averageTicksPerUpdateLastSecond;


public:

	static sp<ConsoleText> mxThreadCountText;

	static sp<ConsoleText> memoryText;
	static sp<ConsoleText> texturesLoadedText;
	static sp<ConsoleText> textureBytesLoadedText;


	static int mb;

	static long long usedMemory;
	static long long maxUsedMemory;
	static long long totalMemory;
	static long long freeMemory;
	static long long maxMemory;

	sp<ConsoleText> vramText = nullptr;

	static void initStats();
	static void updateStats();


private:
	static long long highResTimer;
	static long long highResolutionTicksPerSecond;
	static long long timerOffset;


	static int totalSecondsPassed;
	static int averageFPSTestSecondsPassed;
	static int averageRendersPerSecond;
	static int totalUpdates;
	static int totalRenders;
	static int averageFPSTestTotalRenders;
	static long long lastUpdateHighResTime; 
	static long long lastRenderHighResTime; 
	static long long currentHighResTime;

	
	static int updatesThisSecond;
	static int rendersThisSecond;
	static long long lastSecondTime;

	static long long totalUpdateTicks;
	static long long totalRenderTicks;
	static int rendersSkipped;
	static int updatesSkipped;
	


public:
	static int ticksPassedThisRender;
	static int ticksPassedThisUpdate;
	static double cpuFreq;
	static void initTimers();


	static void updateRenderTimers();
	static void updateUpdateTimers();


	static double getTicksBetweenTimes(long long start, long long finish);
	static long long currentHighResTimer();
	
	static int getTotalRenderTicksPassed();
	static void resetTotalRenderTicksPassed();



	static uint64_t GetPerformanceFrequency();

	static long long getPerformanceCounter();
};
