#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

Logger System::log = Logger("System");

string System::bobVersion = "Unknown";

ConsoleText* System::totalRendersText = nullptr;
ConsoleText* System::totalUpdatesText = nullptr;
ConsoleText* System::rendersPerSecondText = nullptr;
ConsoleText* System::averageRendersPerSecondText = nullptr;
ConsoleText* System::updatesPerSecondText = nullptr;
ConsoleText* System::rendersSkippedText = nullptr;
ConsoleText* System::updatesSkippedText = nullptr;
ConsoleText* System::averageTicksPerFrameText = nullptr;
ConsoleText* System::averageTicksPerUpdateText = nullptr;
ConsoleText* System::onlineStatusText = nullptr;

ConsoleText* System::upTimeText = nullptr;

ConsoleText* System::ticksText[amtTicksTexts] = {nullptr};

ConsoleText* System::mxThreadCountText = nullptr;

ConsoleText* System::memoryText = nullptr;
ConsoleText* System::texturesLoadedText = nullptr;
ConsoleText* System::textureBytesLoadedText = nullptr;

void System::initSystemInfo()
{ //=========================================================================================================================

	log.debug("Init system info");

#ifndef ORBIS
	uint64_t start=0, now=0, totalStart, totalNow;
	start = System::getPerformanceCounter();
	totalStart = System::getPerformanceCounter();

	// Load Version
	string versionPath = Main::getPath() + "VERSION.md";
	shared_ptr<ByteArray> versionData = FileUtils::loadByteFileFromExePath(versionPath);
	if (versionData && versionData->size() > 0)
	{
		string s((char*)versionData->data(), versionData->size());
		// Trim whitespace
		size_t first = s.find_first_not_of(" \t\n\r");
		size_t last = s.find_last_not_of(" \t\n\r");
		if (first != string::npos && last != string::npos)
		{
			bobVersion = s.substr(first, (last - first + 1));
		}
		else
		{
			bobVersion = s;
		}
		log.info("BobsGame Version: " + bobVersion);
	}
	else
	{
		log.warn("Could not load VERSION.md");
	}


	//audio
	int devices_count = 0;
	SDL_AudioDeviceID *devices = SDL_GetAudioOutputDevices(&devices_count);
	if (devices) {
		for (int i = 0; i < devices_count; i++)
		{
			log.info("SDL_AudioOutputDevice" + to_string(i) + ":" + SDL_GetAudioDeviceName(devices[i]));
		}
		SDL_free(devices);
	}

	int drivers_count = 0;
	SDL_GetAudioDrivers(&drivers_count);
	log.info("SDL_GetNumAudioDrivers:" + to_string(drivers_count));
	for (int i = 0; i < drivers_count; i++)
	{
		log.info("SDL_GetAudioDriver" + to_string(i) + ":" + SDL_GetAudioDriver(i));
	}

	log.info("SDL_GetCurrentAudioDriver:" + string(SDL_GetCurrentAudioDriver()));


	//os
	log.info("SDL_GetBasePath:" + string(SDL_GetBasePath()));

	log.info("Main::GetPerformanceCounter:" + to_string(System::getPerformanceCounter()));
	log.info("Main::GetPerformanceFrequency:" + to_string(System::GetPerformanceFrequency()));
	log.info("SDL_GetPlatform:" + string(SDL_GetPlatform()));
	log.info("SDL_GetPrefPath:" + string(SDL_GetPrefPath("Bob Corporation", "bob's game")));
	log.info("SDL_GetRevision:" + string(SDL_GetRevision()));
	log.info("SDL_GetRevisionNumber:" + to_string(SDL_GetRevisionNumber()));
	log.info("SDL_GetSystemRAM:" + to_string(SDL_GetSystemRAM()));


	//log.info("SDL_GetVersion" + string(SDL_GetVersion()));
	SDL_version compiled;
	SDL_version linked;
	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	log.info("Compiled against SDL version:" + to_string(compiled.major) + to_string(compiled.minor) + to_string(compiled.patch));
	log.info("Linked against SDL version:" + to_string(linked.major) + to_string(linked.minor) + to_string(linked.patch));


	//window
	log.info("SDL_GetWindowBrightness:" + to_string(SDL_GetWindowBrightness(GLUtils::window)));
	log.info("SDL_GetDisplayForWindow:" + to_string(SDL_GetDisplayForWindow(GLUtils::window)));
	log.info("SDL_GetWindowFlags:" + to_string(SDL_GetWindowFlags(GLUtils::window)));
	log.info("SDL_GetWindowGrab:" + to_string(SDL_GetWindowGrab(GLUtils::window)));
	log.info("SDL_GetWindowID:" + to_string(SDL_GetWindowID(GLUtils::window)));
	log.info("SDL_GetWindowPixelFormat:" + to_string(SDL_GetWindowPixelFormat(GLUtils::window)));
	log.info("SDL_GetWindowTitle:" + string(SDL_GetWindowTitle(GLUtils::window)));


	//mouse
	log.info("SDL_GetNumTouchDevices:" + to_string(SDL_GetNumTouchDevices()));
	log.info("SDL_GetRelativeMouseMode:" + to_string(SDL_GetRelativeMouseMode()));

	//key
	log.info("SDL_HasScreenKeyboardSupport:" + to_string(SDL_HasScreenKeyboardSupport()));

	//cpu
	log.info("SDL_GetCPUCacheLineSize:" + to_string(SDL_GetCPUCacheLineSize()));
	log.info("SDL_GetCPUCount:" + to_string(SDL_GetCPUCount()));
	log.info("SDL_Has3DNow:" + to_string(SDL_Has3DNow()));
	log.info("SDL_HasAVX:" + to_string(SDL_HasAVX()));
	log.info("SDL_HasAltiVec:" + to_string(SDL_HasAltiVec()));
	log.info("SDL_HasMMX:" + to_string(SDL_HasMMX()));
	log.info("SDL_HasRDTSC:" + to_string(SDL_HasRDTSC()));
	log.info("SDL_HasSSE:" + to_string(SDL_HasSSE()));
	log.info("SDL_HasSSE2:" + to_string(SDL_HasSSE2()));
	log.info("SDL_HasSSE3:" + to_string(SDL_HasSSE3()));
	log.info("SDL_HasSSE41:" + to_string(SDL_HasSSE41()));
	log.info("SDL_HasSSE42:" + to_string(SDL_HasSSE42()));


	//video
	int render_drivers_count = 0;
	SDL_GetRenderDrivers(&render_drivers_count);
	log.info("SDL_GetNumRenderDrivers:" + to_string(render_drivers_count));

	int displays_count = 0;
	SDL_GetDisplays(&displays_count);
	log.info("SDL_GetNumVideoDisplays:" + to_string(displays_count));

	int video_drivers_count = 0;
	SDL_GetVideoDrivers(&video_drivers_count);
	log.info("SDL_GetNumVideoDrivers:" + to_string(video_drivers_count));

	now = System::getPerformanceCounter();
	log.debug("SDL info took " + to_string((double)((now - start) * 1000) / System::GetPerformanceFrequency()) + "ms");
	start = System::getPerformanceCounter();


	log.info("Poco::libraryVersion:" + to_string(Environment::libraryVersion()));
	log.info("Poco::osName:" + string(Environment::osName()));
	log.info("Poco::osVersion:" + string(Environment::osVersion()));
	log.info("Poco::processorCount:" + to_string(Environment::processorCount()));

	totalNow = System::getPerformanceCounter();
	log.debug("Init system info took " + to_string((double)((totalNow - totalStart) * 1000) / System::GetPerformanceFrequency()) + "ms");
#endif

}


void System::initClockAndTimeZone()
{ //=========================================================================================================================

	log.debug("Init clock");
	
	time_t t = time(0); 
	struct tm * now = localtime(&t);

	log.info("Local time: "+to_string(now->tm_year + 1900)+"-"+to_string((now->tm_mon + 1))+"-"+to_string(now->tm_mday)+" "+ to_string(now->tm_hour)+":"+ to_string(now->tm_min)+":"+ to_string(now->tm_sec));
}

long long System::highResolutionTicksPerSecond;
long long System::highResTimer;
long long System::currentHighResTime = 0;

int System::averageRendersPerSecond = 0;
int System::totalSecondsPassed = 0;
int System::averageFPSTestSecondsPassed = 0;
int System::totalRenders = 0;
int System::averageFPSTestTotalRenders = 0;
int System::totalUpdates = 0;

long long System::lastUpdateHighResTime = 0;
long long System::lastRenderHighResTime = 0;

int System::ticksPassedThisRender = 0;
int System::ticksPassedThisUpdate = 0;

int System::updatesThisSecond = 0;
int System::rendersThisSecond = 0;

long long System::totalUpdateTicks = 0;
long long System::totalRenderTicks = 0;

int System::rendersSkipped = 0;
int System::updatesSkipped = 0;

long long System::lastSecondTime = 0;

double System::cpuFreq = 0;

long long System::timerOffset = 0;

void System::initTimers()
{ //=========================================================================================================================

	highResolutionTicksPerSecond = System::GetPerformanceFrequency();
	cpuFreq = double(highResolutionTicksPerSecond) / 1000.0;

	timerOffset = System::getPerformanceCounter();
	timerOffset = System::getPerformanceCounter();

	highResTimer = getPerformanceCounter();
	currentHighResTime = highResTimer;
	lastRenderHighResTime = highResTimer;
	lastUpdateHighResTime = highResTimer;
	lastSecondTime = highResTimer;
}

void System::updateRenderTimers()
{ //=========================================================================================================================
	rendersThisSecond++;
	totalRenders++;

	if (Main::mainLoopStarted && totalSecondsPassed > 15)
	{
		averageFPSTestTotalRenders++;
	}

	highResTimer = getPerformanceCounter();
	currentHighResTime = highResTimer;

	ticksPassedThisRender = (int)(System::getTicksBetweenTimes(lastRenderHighResTime, currentHighResTime));

	lastRenderHighResTime = currentHighResTime;
	totalRenderTicks += ticksPassedThisRender;

	if (ticksPassedThisRender > (int)(16 * 1.5))
	{
		rendersSkipped++; 
	}
}

void System::updateUpdateTimers()
{ //=========================================================================================================================

	updatesThisSecond++;
	totalUpdates++;

	ticksPassedThisUpdate = (int)(System::getTicksBetweenTimes(lastUpdateHighResTime, currentHighResTime));

	lastUpdateHighResTime = currentHighResTime;
	totalUpdateTicks += ticksPassedThisUpdate;
	
	if (ticksPassedThisUpdate > (int)(16 * 1.5))
	{
		updatesSkipped++; 
	}
}

long long System::lastRenderTime = 0;
long long System::lastUpdateTime = 0;

int System::ticksTextCount = 0;

int System::averageTicksPerRenderLastSecond = 0;
int System::averageTicksPerUpdateLastSecond = 0;

int System::mb = 1024 * 1024;
long long System::usedMemory = 0;
long long System::maxUsedMemory = 0;
long long System::totalMemory = 0;
long long System::freeMemory = 0;
long long System::maxMemory = 0;


void System::initStats()
{ //=========================================================================================================================

	upTimeText = Main::console->debug(" ");

	totalRendersText = Main::console->debug(" ");
	totalUpdatesText = Main::console->debug(" ");

	rendersPerSecondText = Main::console->add(" ");
	updatesPerSecondText = Main::console->debug(" ");
	averageRendersPerSecondText = Main::console->add(" ");
	onlineStatusText = Main::console->add(" ");

	rendersSkippedText = Main::console->debug(" ");
	updatesSkippedText = Main::console->debug(" ");

	averageTicksPerFrameText = Main::console->debug(" ");
	averageTicksPerUpdateText = Main::console->debug(" ");

#ifdef _DEBUG
	for (int i = 0; i < amtTicksTexts; i++)
		ticksText[i] = Main::console->debug(" ");
#endif

	texturesLoadedText = Main::console->debug(" ");
	textureBytesLoadedText = Main::console->debug(" ");

	totalMemory = 0;
	freeMemory = 0;
	maxMemory = 0;
}

void System::updateStats()
{ //=========================================================================================================================

	upTimeText->text = "Uptime: " + to_string(totalUpdateTicks / 1000) + "s (" + to_string(totalUpdateTicks) + "ms)";

	totalRendersText->text = "Total Renders: " + to_string(totalRenders);
	totalUpdatesText->text = "Total Updates: " + to_string(totalUpdates);

	rendersSkippedText->text = "Renders Skipped: " + to_string(rendersSkipped);
	updatesSkippedText->text = "Updates Skipped: " + to_string(updatesSkipped);

	if(Main::bobNet->tcpServerConnection.getConnectedToServer_S()==true)
	{
		if (Main::bobNet->tcpServerConnection.serverStats != nullptr)
		{
			int usersOnline = Main::bobNet->tcpServerConnection.serverStats->usersOnline;
			if(usersOnline==1)onlineStatusText->text = "Connected: " + to_string(usersOnline) + " player online";
			else onlineStatusText->text = "Connected: " + to_string(usersOnline) + " players online";
			onlineStatusText->color = BobColor::green;
		}
		else
		{
			onlineStatusText->text = "Connected";
			onlineStatusText->color = BobColor::green;
		}
	}
	else
	{
		onlineStatusText->text = "Offline";
		onlineStatusText->color = ConsoleText::defaultColor;
	}

	int ticksPassedThisSecond = (int)(System::getTicksBetweenTimes(lastSecondTime, currentHighResTime));
	if (ticksPassedThisSecond >= 1000)
	{
		
		if (rendersThisSecond>0)averageTicksPerRenderLastSecond = ticksPassedThisSecond / rendersThisSecond;
		if (updatesThisSecond>0)averageTicksPerUpdateLastSecond = ticksPassedThisSecond / updatesThisSecond;

		if (rendersThisSecond >= 60)
		{
			rendersPerSecondText->color = ConsoleText::defaultColor;
		}
		else
			if (rendersThisSecond >= 30)
			{
				rendersPerSecondText->color = BobColor::yellow;
			}
			else
			{
				rendersPerSecondText->color = BobColor::red;
			}


		if (updatesThisSecond >= 60)
		{
			updatesPerSecondText->color = ConsoleText::defaultColor;
		}
		else
			if (updatesThisSecond >= 30)
			{
				updatesPerSecondText->color = BobColor::yellow;
			}
			else
			{
				updatesPerSecondText->color = BobColor::red;
			}


		rendersPerSecondText->text = "FPS: " + to_string(rendersThisSecond);
		updatesPerSecondText->text = "Updates/sec: " + to_string(updatesThisSecond);

		averageTicksPerFrameText->text = "Average Ticks Per Frame (Last Second): " + to_string(averageTicksPerRenderLastSecond);
		averageTicksPerUpdateText->text = "Average Ticks Per Update (Last Second): " + to_string(averageTicksPerUpdateLastSecond);

		lastSecondTime += (long long)(1000 * cpuFreq);
		rendersThisSecond = 0;
		updatesThisSecond = 0;

		totalSecondsPassed++;

		averageRendersPerSecond = totalRenders / totalSecondsPassed;

		if (Main::mainLoopStarted && totalSecondsPassed > 15)
		{
			averageFPSTestSecondsPassed++;
			int averageFPSTestRendersPerSecond = averageFPSTestTotalRenders / averageFPSTestSecondsPassed;

			averageRendersPerSecondText->text = "Average FPS: " + to_string(averageFPSTestRendersPerSecond);

			if (averageFPSTestRendersPerSecond < 50)
			{
				averageFPSTestTotalRenders = 0;
				averageFPSTestSecondsPassed = 0;
				if (GLUtils::SHADER_FBO_SCALE == 1.0f)
				{
					log.debug("Downscaled shaders to try for higher framerate");
					GLUtils::SHADER_FBO_SCALE = 0.5f;
					GLUtils::doResize();
				}
				else
					if (GLUtils::SHADER_FBO_SCALE == 0.5f)
					{
						log.debug("Downscaled shaders again to try for higher framerate");
						GLUtils::SHADER_FBO_SCALE = 0.25f;
						GLUtils::doResize();
					}
			}
		}
	}


#ifdef _DEBUG
	long long thisRenderTime = currentHighResTime;
	int debugTicksPassed = (int)(System::getTicksBetweenTimes(lastRenderTime, thisRenderTime));
	lastRenderTime = thisRenderTime;

	for (int i = 0; i < amtTicksTexts; i++)
	{
		if (ticksTextCount == i)
		{
			ticksText[i]->text = string("Ticks Passed " + to_string(i) + ": ") + to_string(debugTicksPassed);
			if (debugTicksPassed > 17)
			{
				ticksText[i]->color = BobColor::red;
			}
			else
			{
				ticksText[i]->color = ConsoleText::defaultColor;
			}
		}
	}

	ticksTextCount++;
	if (ticksTextCount >= amtTicksTexts)
	{
		ticksTextCount = 0;
	}
#endif

	texturesLoadedText->text = "Textures Loaded: " + to_string(GLUtils::texturesLoaded);
	textureBytesLoadedText->text = "Texture MBs Loaded: " + to_string(GLUtils::textureBytesLoaded / 1024 / 1024);
}

uint64_t System::GetPerformanceFrequency()
{
#ifndef ORBIS
	return SDL_GetPerformanceFrequency();
#else
	return 1000*1000*1000;
#endif
}

long long System::getPerformanceCounter()
{
#ifndef ORBIS
	return SDL_GetPerformanceCounter() - timerOffset;
#else
	SceFiosTime time = sceFiosTimeGetCurrent();
	return time - timerOffset;
#endif
}

long long System::currentHighResTimer()
{
	return currentHighResTime;
}

double System::getTicksBetweenTimes(long long start, long long finish)
{
	return ((double)(finish - start) / cpuFreq);
}

int System::getTotalRenderTicksPassed()
{
	return (int)totalRenderTicks;
}

void System::resetTotalRenderTicksPassed()
{
	totalRenderTicks = 0;
}
