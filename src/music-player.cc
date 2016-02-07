#include <cassert>
#include "music-player.hh"

namespace opl
{

	MusicPlayer* MusicPlayer::instance_ = nullptr;

	MusicPlayer*
	MusicPlayer::instance ()
	{
		if (!instance_)
			instance_ = new MusicPlayer;
		return instance_;
	}

	bool
	MusicPlayer::is_active () const
	{
		return mix_ != nullptr;
	}

	bool
	MusicPlayer::is_playing () const
	{
		return Mix_PlayingMusic ();
	}

	std::string
	MusicPlayer::song_get () const
	{
		return song_;
	}

	void
	MusicPlayer::play (const std::string& song)
	{
		if(mix_)
			stop ();
		mix_ = Mix_LoadMUS (song.c_str ());
		assert (mix_);
		Mix_PlayMusic (mix_, -1);
	}

	void
	MusicPlayer::stop ()
	{
		assert (is_active ());
		Mix_HaltMusic ();
		Mix_FreeMusic (mix_);
	}

	void
	MusicPlayer::pause ()
	{
		assert (is_active ());
		assert (is_playing ());
		Mix_PauseMusic ();
	}

	void
	MusicPlayer::resume ()
	{
		assert (is_active ());
		assert (!is_playing ());
		Mix_ResumeMusic ();
	}

    void
	MusicPlayer::play_chunk (const std::string& path)
	{
		Mix_PlayChannel(-1, chunk_get_ (path), 0);
	}

	void
	MusicPlayer::preload_chunk (const std::string& path)
	{
		chunk_get_ (path);
	}

	void
	MusicPlayer::preload_chunks (const std::vector<std::string>& paths)
	{
		for (auto it = paths.begin (); it != paths.end (); ++it)
			chunk_get_ (*it);
	}

	Mix_Chunk*
	MusicPlayer::chunk_get_ (const std::string &path)
	{
		auto it = chunks_.find (path);
		if(it == chunks_.end ())
		{
			Mix_Chunk* chunk = Mix_LoadWAV (path.c_str ());
			assert (chunk);
			chunks_[path] = chunk;
			return chunk;
		}
		return it->second;
	}

}