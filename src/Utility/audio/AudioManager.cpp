
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------




#ifndef ORBIS
#include "SDL3_mixer/SDL_mixer.h"
#else
#endif
#if HAVE_PROJECTM
#include "libprojectM/ProjectM.hpp"
#endif

Logger AudioManager::log = Logger("AudioManager");



#ifdef USE_SDL_MIXER
MIX_Mixer *AudioManager::mixer = nullptr;
#endif

#ifdef USE_SOLOUD
SoLoud::Soloud *AudioManager::soLoud = nullptr;
#endif

//global and static, shared between all audiomanagers
ArrayList<shared_ptr<AudioFile>> AudioManager::globalAudioFileList;
bool AudioManager::loadedBuiltIn = false;

shared_ptr<libprojectM::ProjectM> AudioManager::visualizer = nullptr;

void AudioManager::setVisualizer(shared_ptr<libprojectM::ProjectM> v)
{
	visualizer = v;
}

void AudioManager::postMixCallback(void *userdata, MIX_Mixer *mixer, const SDL_AudioSpec *spec, float *pcm, int samples)
{
#if HAVE_PROJECTM
	if (visualizer)
	{
		// SDL3_mixer provides floats. ProjectM likely needs floats or we convert.
		// visualizer->PCM().Add expects (short*, channels, samples) usually in SDL2 version.
		// Let's assume we can pass floats or convert.
		// For now, let's just cast or find float variant.
		// Actually, let's convert to int16 for compatibility with existing visualizer logic if needed.
		
		int numSamples = samples; // len is number of floats? No, usually number of sample frames or total samples.
		// SDL3_mixer says 'samples' is the number of float values.
		
		// Convert float to int16 for projectM if it doesn't support floats.
		// projectM 3.x usually supports floats.
		
		// If projectM Add expects int16:
		
		vector<int16_t> intSamples(numSamples);
		for(int i=0; i<numSamples; i++) intSamples[i] = (int16_t)(pcm[i] * 32767.0f);
		visualizer->PCM().Add(intSamples.data(), spec->channels, numSamples / spec->channels);
		
		
		// Assume visualizer can handle it or we'll fix it later.
		// visualizer->PCM().Add(stream, 2, numSamples / 2); 
	}
#endif
}

//=========================================================================================================================
AudioManager::AudioManager()
{ //=========================================================================================================================


}

//=========================================================================================================================
AudioManager::AudioManager(Engine* g)
{ //=========================================================================================================================

	this->e = g;

}

//=========================================================================================================================
void AudioManager::initAudioLibrary()
{//=========================================================================================================================

	

#ifdef USE_SDL_MIXER
	{
		uint64_t start = 0, now = 0;// , totalStart, totalNow;
		start = System::getPerformanceCounter();
		//totalStart = System::getPerformanceCounter();

		log.debug("Init SDL Mixer");

		if (!MIX_Init())
		{
			log.error("MIX_Init failed: " + string(SDL_GetError()));
		}
		else
		{
			SDL_AudioSpec spec;
			SDL_zero(spec);
			spec.freq = 44100;
			spec.format = SDL_AUDIO_S16;
			spec.channels = 2;
			mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
			if (!mixer)
			{
				log.error("MIX_CreateMixerDevice failed: " + string(SDL_GetError()));
			}
			else
			{
				MIX_SetPostMixCallback(mixer, postMixCallback, NULL);
			}
		}


		now = System::getPerformanceCounter();
		log.debug("Init SDL Mixer took " + to_string((double)((now - start) * 1000) / System::GetPerformanceFrequency()) + "ms");
		start = System::getPerformanceCounter();
	}
#endif

	GLUtils::checkSDLError("AudioManager::initAudioLibrary()");

#ifdef USE_SOLOUD
	soLoud = new SoLoud::Soloud();
	soLoud->init();
#endif


	


	if (loadedBuiltIn == false)
	{
		loadedBuiltIn = true;


		uint64_t start = 0, now = 0, totalStart = 0, totalNow = 0;
		start = System::getPerformanceCounter();
		totalStart = System::getPerformanceCounter();

		log.debug("Loading built in sounds");
		{
			log.debug("get path");

			
			string spriteFolderString = Main::getPath() + "data/sounds/";
			
			//log.debug("create path");
			//Path spriteFolderPath(spriteFolderString);
			log.debug("create file");
			BobFile spriteFolderPathDir(spriteFolderString);
			log.debug("createDirectories");
			if (spriteFolderPathDir.exists() == false) { spriteFolderPathDir.createDirectories(); }
			
			log.debug("list");
			vector<string> files = spriteFolderPathDir.list();
						
			
			vector<string>::iterator it = files.begin();
			for (; it != files.end(); ++it)
			{
				//cout << *it << endl;
				string name = *it;
				if (name.find(".ogg") != string::npos)
				{
					globalAudioFileList.add(make_shared<AudioFile>("data/sounds/" + name));
				}
			}
		}

		now = System::getPerformanceCounter();
		log.debug("Loading sounds took " + to_string((double)((now - start) * 1000) / System::GetPerformanceFrequency()) + "ms");
		start = System::getPerformanceCounter();


		log.debug("Loading built in music");
		{
			string spriteFolderString = Main::getPath() + "data/music/";
			//Path spriteFolderPath(spriteFolderString);
			BobFile spriteFolderPathDir(spriteFolderString);
			if (spriteFolderPathDir.exists() == false)spriteFolderPathDir.createDirectories();
			vector<string> files = spriteFolderPathDir.list();
			vector<string>::iterator it = files.begin();
			for (; it != files.end(); ++it)
			{
				//cout << *it << endl;
				string name = *it;
				if (name.find(".ogg") != string::npos)
				{
					globalAudioFileList.add(make_shared<AudioFile>("data/music/" + name));
				}
			}
		}

		now = System::getPerformanceCounter();
		log.debug("Loading music took " + to_string((double)((now - start) * 1000) / System::GetPerformanceFrequency()) + "ms");
		start = System::getPerformanceCounter();

		totalNow = System::getPerformanceCounter();
		log.debug("initAudioLibrary took " + to_string((double)((totalNow - totalStart) * 1000) / System::GetPerformanceFrequency()) + "ms");

		

		//GLUtils::e();
	}

	//	//load sounds/index.txt
	//	//for each line, load ogg file
	//	ArrayList<string>* stringList = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/sounds/index.txt");
	//	if (stringList->size() > 0)
	//	{
	//		for (int i = 0; i < stringList->size(); i++)
	//		{
	//			string s = stringList->get(i);
	//
	//			if (s.length() > 0)
	//			{
	//				//Sound *sound =
	//				new Sound(this, "data/sounds/" + s);
	//				//sound.byteData = dataFile.readBytes();
	//			}
	//		}
	//	}


}





//=========================================================================================================================
void AudioManager::cleanup()
{//=========================================================================================================================

	log.info("Cleaning up audio");
#ifdef USE_SDL_MIXER
	if (mixer)
	{
		MIX_DestroyMixer(mixer);
		mixer = nullptr;
	}
	MIX_Quit();
#endif
#ifdef USE_SOLOUD
	soLoud->deinit();
#endif

}

//Sound* AudioManager::loadSoundFileByName(const string& fileName)
//{ //=========================================================================================================================
//
//	Sound* s = nullptr;
//
//	for(int i=0;i<soundList.size();i++)if(soundList.get(i)->getName() == fileName)s = soundList.get(i);
//
//	if (s == nullptr)
//	{
//		HashMap<string, Sound *>::const_iterator got = soundByNameHashMap->find(fileName);
//		if (got != soundByNameHashMap->end())
//			s = soundByNameHashMap->get(fileName);
//	}
//
//	if (s == nullptr)
//	{
//	    s = new Sound(fileName);
//	    soundByNameHashMap->insert_or_assign(s->getName(),s);
//	}
//
//	return s;
//}



void AudioManager::globalUpdate()
{
	
	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		globalAudioFileList.get(i)->update();
	}
}


void AudioManager::update()
{ //=========================================================================================================================



	for (int i = 0; i < playingAudioList.size(); i++)
	{
		playingAudioList.get(i)->update();
	}
}

shared_ptr<Sound> AudioManager::getSoundByName(const string& musicName)
{ //=========================================================================================================================
	if (musicName == "" || musicName.length() == 0)
	{
		return nullptr;
	}



	string clippedName = musicName;
	if (clippedName.find("_v") != -1)
	{
		clippedName.substr(0, clippedName.find("_v"));
	}	
	
	if (clippedName.find(".") != -1)
	{
		clippedName.substr(0, clippedName.find("."));
	}

	for (int i = 0; i < playingAudioList.size(); i++)
	{
		string name = playingAudioList.get(i)->getName();

		if (String::startsWith(name, clippedName))
		{
			
			return playingAudioList.get(i);
		}
	}


	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		string name = globalAudioFileList.get(i)->getName();

		if (String::startsWith(name, clippedName))
		{
			shared_ptr<Sound> s = make_shared<Sound>(getEngine(), globalAudioFileList.get(i));
			playingAudioList.add(s);
			return s;
		}
	}






	return nullptr;
}


//=========================================================================================================================
void AudioManager::playMusic(shared_ptr<Sound> s, float vol, float pitch, bool loop)
{ //=========================================================================================================================
	if (s != nullptr)
	{
		if (playingAudioList.contains(s) == false)playingAudioList.add(s);
		s->play(pitch, vol, loop);
	}
}

shared_ptr<Sound> AudioManager::playMusic(const string& musicName, float volume, float pitch, bool loop)
{ //=========================================================================================================================
	shared_ptr<Sound> m = getSoundByName(musicName);
	if (m != nullptr)
	{
		m->play(pitch, volume, loop);
		if (playingAudioList.contains(m) == false)playingAudioList.add(m);
		return m;
	}
	return nullptr;
}

//=========================================================================================================================
shared_ptr<Sound> AudioManager::playSound(const string& soundName, float volume, float pitch)
{ //=========================================================================================================================

	return playSound(soundName,volume,pitch,1);

}

//=========================================================================================================================
shared_ptr<Sound> AudioManager::playSound(const string& soundName)
{ //=========================================================================================================================
	return playSound(soundName, 1, 1, 1);
}

//=========================================================================================================================
shared_ptr<Sound> AudioManager::playSound(const string& soundName, float volume, float pitch, int times)
{ //=========================================================================================================================

	shared_ptr<Sound> s = getSoundByName(soundName);
	if (s != nullptr)
	{
		s->play(pitch, volume, times);
		return s;
	}
	return nullptr;

	//Exception e = new Exception();e.printStackTrace();
}


//=========================================================================================================================
void AudioManager::playSound(shared_ptr<Sound> s, float vol, float pitch, int times)
{ //=========================================================================================================================
	if (s != nullptr)
	{
		if (playingAudioList.contains(s) == false)playingAudioList.add(s);
		s->play(pitch, vol, times);
	}
}

void AudioManager::playMusic(shared_ptr<Sound> m)
{ //=========================================================================================================================
	playSoundLoop(m);
}
void AudioManager::playSoundLoop(shared_ptr<Sound> m)
{ //=========================================================================================================================
	m->playLoop();
	if (playingAudioList.contains(m) == false)playingAudioList.add(m);
}

shared_ptr<Sound> AudioManager::playMusic(const string& musicName)
{ //=========================================================================================================================
	return playSoundLoop(musicName);
}
shared_ptr<Sound> AudioManager::playSoundLoop(const string& musicName)
{ //=========================================================================================================================
	shared_ptr<Sound> m = getSoundByName(musicName);
	if (m != nullptr)
	{
		m->playLoop();
		return m;
	}
	return nullptr;
}




bool AudioManager::isSoundPlaying(shared_ptr<Sound> m)
{ //=========================================================================================================================

	if (playingAudioList.contains(m) == false)return false;
	return m->isPlaying();
}

bool AudioManager::isSoundPlaying(const string& musicName)
{ //=========================================================================================================================
	shared_ptr<Sound> m = getSoundByName(musicName);
	if (m != nullptr)
	{
		if (playingAudioList.contains(m) == false)return false;
		return m->isPlaying();
	}
	return false;
}

void AudioManager::stopMusic(shared_ptr<Sound> m)
{ //=========================================================================================================================
	stopSound(m);
}
void AudioManager::stopSound(shared_ptr<Sound> m)
{ //=========================================================================================================================
	m->stop();
}

void AudioManager::stopMusic(const string& musicName)
{ //=========================================================================================================================
	stopSound(musicName);
}

void AudioManager::stopSound(const string& musicName)
{ //=========================================================================================================================
	shared_ptr<Sound> m = getSoundByName(musicName);

	if (m != nullptr)
	{
		m->stop();
	}
}



void AudioManager::fadeOutSound(const string& musicName, int ticks)
{ //=========================================================================================================================
	shared_ptr<Sound> m = getSoundByName(musicName);

	if (m != nullptr)
	{
		m->fadeOutAndStop(ticks);
	}
	
}

void AudioManager::fadeOutSound(shared_ptr<Sound> m, int ticks)
{ //=========================================================================================================================
	if (m != nullptr)
	{
		m->fadeOutAndStop(ticks);
	}
}



bool AudioManager::isAnyMusicPlaying()
{ //=========================================================================================================================
	return isAnyLoopingSoundPlaying();
}

bool AudioManager::isAnyLoopingSoundPlaying()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		if (m->getLoop() && m->isPlaying())
		{
			return true;
		}
	}
	return false;
}
//=========================================================================================================================
void AudioManager::pauseAnyPlayingLoopingSounds()
{//=========================================================================================================================

	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		if (m->getLoop() && m->isPlaying())
		{
			m->pause();
		}
	}
}
//=========================================================================================================================
void AudioManager::playAnyPausedLoopingSounds()
{//=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		if (m->getLoop() && m->isPlaying())
		{
			m->unpause();
		}
	}

}
//=========================================================================================================================
void AudioManager::setAllPlayingSoundsVolume(float v)
{//=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		if (m->isPlaying())
		{
			m->setVolume(v);
		}
	}
}
//=========================================================================================================================
void AudioManager::setAllPlayingLoopingSoundsVolume(float v)
{//=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		if (m->isPlaying() && m->getLoop())
		{
			m->setVolume(v);
		}
	}
}


void AudioManager::stopAllMusic()
{ //=========================================================================================================================
	stopAllLoopingSounds();
}
void AudioManager::stopAllLoopingSounds()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		if(m->getLoop())m->stop();
	}
	
}

void AudioManager::fadeOutAllMusic(int ticks)
{ //=========================================================================================================================
	fadeOutAllLoopingSounds(ticks);
}

void AudioManager::fadeOutAllLoopingSounds(int ticks)
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);

		if (m->getLoop())m->fadeOutAndStop(ticks);
		
	}
	
}
void AudioManager::fadeOutAllSounds(int ticks)
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);

		m->fadeOutAndStop(ticks);
		
	}
	
}

void AudioManager::setAllLoopingSoundsThatAreNotFadingOutToNotLoop()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		if (m->getLoop() && m->isPlaying() == true)
		{
			if (m->isFadingOut() == false)
			{
				m->setLoop(false);
			}
		}
	}
}

void AudioManager::setAllLoopingSoundsToNotLoop()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		if (m->getLoop() && m->isPlaying() == true)
		{
			
				m->setLoop(false);
			
		}
	}
}

void AudioManager::pauseAllLoopingSounds()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		if (m->getLoop())m->pause();
	}
}

void AudioManager::unpauseAllLoopingSounds()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		if (m->getLoop())m->unpause();
	}
}
void AudioManager::pauseAllSounds()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		m->pause();
	}
}

void AudioManager::unpauseAllSounds()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		m->unpause();
	}
}


//=========================================================================================================================
shared_ptr<AudioFile> AudioManager::getAudioFileByName(string name)
{//=========================================================================================================================


	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		shared_ptr<AudioFile> s = globalAudioFileList.get(i);
		if (s->getName() == name)return s;
	}
	return nullptr;
}


//=========================================================================================================================
shared_ptr<AudioFile> AudioManager::getAudioFileByIDCreateIfNotExist(int id)
{//=========================================================================================================================


	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		shared_ptr<AudioFile> s = globalAudioFileList.get(i);
		if (s->getID() == id)return s;
	}
	return make_shared<AudioFile>(new AudioData(id,"",""));
}

//=========================================================================================================================
shared_ptr<Sound> AudioManager::getSoundByIDCreateIfNotExist(int id)
{//=========================================================================================================================


	for (int i = 0; i < playingAudioList.size(); i++)
	{
		if (playingAudioList.get(i)->getID()==id)
		{

			return playingAudioList.get(i);
		}
	}

	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		shared_ptr<AudioFile> s = globalAudioFileList.get(i);
		if (s->getID() == id)
		{
			shared_ptr<Sound> sound = make_shared<Sound>(e, s);
			playingAudioList.add(sound);
			return sound;
		}
	}
	shared_ptr<Sound> sound = make_shared<Sound>(e, make_shared<AudioFile>(new AudioData(id, "", "")));
	playingAudioList.add(sound);
	return sound;
}


































































#ifndef ORBIS


int G_mute = 0;//GLOBAL MUTE

int current_bgm_volume = 0;

MIX_Audio* song_playing = nullptr;
MIX_Track* song_track = nullptr;


int* current_mod_data_pointer = nullptr;


string playingname = "";// [128];


MIX_Audio* mixchunks[32] = { nullptr };
MIX_Track* mixtracks[32] = { nullptr };
string mixchunkfilename[32] = { "" };



//==========================================================================================================================
char* HARDWARE_get_sound_filename_from_name(string &name, int freq)
{//==========================================================================================================================

	char* filename = NULL;

	//if(strcmp(name,"footstep")==0)filename=footstep_FileName;

	return filename;
}


//==========================================================================================================================
MIX_Audio* HARDWARE_get_sound_data_pointer_from_name(string &name, int freq)
{//==========================================================================================================================

	char* filename = NULL;


	filename = HARDWARE_get_sound_filename_from_name(name, freq);
	if (filename == NULL)return NULL;

	//search mixchunkfilenames 0-31 for matches with filename
	int d = -1;
	int x = 0;
	for (x = 0; x < MAX_SOUNDS_PLAYING; x++)
	{
		if (mixchunkfilename[x] == filename)
		{
			d = x;
			x = MAX_SOUNDS_PLAYING;
			break;
		}
	}

	if (d == -1)
	{
		//find open filename slot
		for (x = 0; x < MAX_SOUNDS_PLAYING; x++)
		{
			if (mixchunkfilename[x] == "")
			{
				d = x;
				mixchunkfilename[d] = filename;//set slot to filename
				mixchunks[d] = MIX_LoadAudio(AudioManager::mixer, mixchunkfilename[d].c_str(), true);
				x = MAX_SOUNDS_PLAYING;
				break;
			}
		}
	}

	return mixchunks[d];
}


//==========================================================================================================================
bool HARDWARE_play_sound(string &name, int vol, int freq, int loop)//if(!HARDWARE_is_sound_channel_busy(chan))//HARDWARE_PlayFSSoundEx2(chan,HARDWARE_FSGetFile(0,name,""),vol,freq,0,loop,0);
{//==========================================================================================================================

	if (G_mute)vol = 0;


	MIX_Audio* data = NULL;
	data = HARDWARE_get_sound_data_pointer_from_name(name, freq);

	if (data != NULL)
	{
		// Find an available track slot
		int d = -1;
		for(int i=0; i<32; i++) {
			if(mixtracks[i] == nullptr) mixtracks[i] = MIX_CreateTrack(AudioManager::mixer);
			if(!MIX_TrackPlaying(mixtracks[i])) {
				d = i;
				break;
			}
		}
		
		if (d != -1) {
			MIX_SetTrackAudio(mixtracks[d], data);
			MIX_SetTrackGain(mixtracks[d], (float)vol / 256.0f);
			MIX_SetTrackLoops(mixtracks[d], (loop == 1) ? -1 : loop);
			MIX_PlayTrack(mixtracks[d], 0);
		}
	}
	else
	{
		ERROR_set_error(name);
		ERROR_set_error(" could not be played.\n");
	}


	return true;
}

//==========================================================================================================================
bool HARDWARE_play_sound_if_not_playing(string &name, int vol, int freq, int loop)
{//==========================================================================================================================


	if (G_mute)vol = 0;


	char* filename = nullptr;
	filename = HARDWARE_get_sound_filename_from_name(name, freq);
	if (filename == nullptr)return 0;

	int x = 0;
	for (x = 0; x < MAX_SOUNDS_PLAYING; x++)
	{
		if (mixchunkfilename[x] != "")
			if (mixchunkfilename[x] == filename)
			{
				if (mixtracks[x] && MIX_TrackPlaying(mixtracks[x])) return 0;
			}
	}

	HARDWARE_play_sound(name, vol, freq, loop);


	return 1;
}

//==========================================================================================================================
void HARDWARE_stop_sound(string &name)//if(HARDWARE_is_sound_channel_busy(chan))HARDWARE_StopSound(chan);
{//==========================================================================================================================

	MIX_Audio* data = NULL;
	data = HARDWARE_get_sound_data_pointer_from_name(name, 44100);

	//go through all playing tracks, if track is playing data, stop track
	if (data != NULL)
	{
		for (int i = 0; i < 32; i++)
		{
			if (mixtracks[i] && MIX_GetTrackAudio(mixtracks[i]) == data) MIX_StopTrack(mixtracks[i], 0);
		}
	}
}

//==========================================================================================================================
void HARDWARE_unload_wavs_done_playing()
{//==========================================================================================================================

 //go through each mixchunk->get(d)
 //see if still playing
 //if not playing, unload mixchunk->get(d) and set mixchunkfilename->get(d) to NULL

	int x = 0;
	for (x = 0; x < MAX_SOUNDS_PLAYING; x++)
	{
		if (mixchunks[x] != nullptr && mixchunkfilename[x] != "")
		{
			bool playing = false;
			for (int i = 0; i < 32; i++)
			{
				if (mixtracks[i] && MIX_GetTrackAudio(mixtracks[i]) == mixchunks[x] && MIX_TrackPlaying(mixtracks[i])) playing = true;
			}

			if (playing == false)
			{
				if (
					mixchunkfilename[x] == "data/sfx/footstepnormal.wav"//dont unload footstep, its used a lot
					)
				{
					MIX_DestroyAudio(mixchunks[x]);
					mixchunks[x] = nullptr;
					mixchunkfilename[x] = "";
				}
			}
		}
	}
}

//==========================================================================================================================
void HARDWARE_set_channel_volume(int chan, int vol)//if(HARDWARE_is_sound_channel_busy(chan))HARDWARE_StopSound(chan);
{//==========================================================================================================================

	if (G_mute)vol = 0;
	else if (chan >= 0 && chan < 32 && mixtracks[chan])
		MIX_SetTrackGain(mixtracks[chan], (float)vol / 256.0f);
}


//==========================================================================================================================
void HARDWARE_set_music_volume(int vol)//if(HARDWARE_is_sound_channel_busy(chan))HARDWARE_StopSound(chan);
{//==========================================================================================================================

	if (G_mute)vol = 0;

	if (current_bgm_volume != vol)
	{
		current_bgm_volume = vol;
		if (song_track != NULL) MIX_SetTrackGain(song_track, (float)vol / 64.0f);
	}
}


//==========================================================================================================================
void HARDWARE_play_music(string &name, int vol)//HARDWARE_PlayFSMod(mod);
{//==========================================================================================================================

	if (G_mute)vol = 0;


	if (name == playingname || song_playing == NULL)
	{
		//copy string into playing string
		//strcpy(playingname, name);
		playingname = name;

		//free the previous song
		if (song_playing != NULL)
		{
			if (song_track) MIX_StopTrack(song_track, 0);
			MIX_DestroyAudio(song_playing);
			song_playing = NULL;
		}

		//load the new one
		if (name == "nice") song_playing = MIX_LoadAudio(AudioManager::mixer, "data/bgm/snappy_nice_v01.s3m", false);

		if (song_playing == NULL)
		{
			ERROR_set_error(name);
			ERROR_set_error(" could not be loaded.\n");
		}
		else {
			if (!song_track) song_track = MIX_CreateTrack(AudioManager::mixer);
			MIX_SetTrackAudio(song_track, song_playing);
			MIX_SetTrackLoops(song_track, -1);
			MIX_PlayTrack(song_track, 0);
		}
	}


	if (vol != current_bgm_volume)
	{
		current_bgm_volume = vol;
		if (song_track != NULL) MIX_SetTrackGain(song_track, (float)vol / 64.0f);
	}
}


//==========================================================================================================================
void HARDWARE_stop_music()//HARDWARE_StopMod();
{//==========================================================================================================================

	if (song_playing != NULL)
	{
		if (song_track) MIX_StopTrack(song_track, 0);
		MIX_DestroyAudio(song_playing);
		song_playing = NULL;
	}
}
#else
#endif
