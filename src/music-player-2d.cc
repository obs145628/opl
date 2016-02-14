#include <cassert>
#include "music-player-2d.hh"

namespace opl
{

	MusicPlayer2D* MusicPlayer2D::instance_ = nullptr;

	MusicPlayer2D*
	MusicPlayer2D::instance ()
	{
		if (!instance_)
			instance_ = new MusicPlayer2D;
		return instance_;
	}

	bool
	MusicPlayer2D::is_active () const
	{
		return mix_ != nullptr;
	}

	bool
	MusicPlayer2D::is_playing () const
	{
		return Mix_PlayingMusic ();
	}

	std::string
	MusicPlayer2D::song_get () const
	{
		return song_;
	}

	void
	MusicPlayer2D::play (const std::string& song)
	{
		if(mix_)
			stop ();
		mix_ = Mix_LoadMUS (song.c_str ());
		assert (mix_);
		Mix_PlayMusic (mix_, -1);
	}

	void
	MusicPlayer2D::stop ()
	{
		assert (is_active ());
		Mix_HaltMusic ();
		Mix_FreeMusic (mix_);
	}

	void
	MusicPlayer2D::pause ()
	{
		assert (is_active ());
		assert (is_playing ());
		Mix_PauseMusic ();
	}

	void
	MusicPlayer2D::resume ()
	{
		assert (is_active ());
		assert (!is_playing ());
		Mix_ResumeMusic ();
	}

    void
	MusicPlayer2D::play_chunk (const std::string& path)
	{
		Mix_PlayChannel(-1, chunk_get_ (path), 0);
	}

	void
	MusicPlayer2D::preload_chunk (const std::string& path)
	{
		chunk_get_ (path);
	}

	void
	MusicPlayer2D::preload_chunks (const std::vector<std::string>& paths)
	{
		for (auto it = paths.begin (); it != paths.end (); ++it)
			chunk_get_ (*it);
	}

	Mix_Chunk*
	MusicPlayer2D::chunk_get_ (const std::string &path)
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