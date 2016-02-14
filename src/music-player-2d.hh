/** @file MusicPlayer2D class deifinition
 */

#ifndef MUSIC_PLAYER_2D_HH_
# define MUSIC_PLAYER_2D_HH_

# include <string>
# include <map>
# include <vector>
# include "sdl.hh"

namespace opl
{

	///Handle video game background music with SDL
	class MusicPlayer2D
	{

	public:
		static MusicPlayer2D*
		instance ();

		///Returns true if there is a song, playing or paused
		bool
		is_active () const;

		bool
		is_playing () const;

		std::string
		song_get () const;

		void
		play (const std::string& song);

		void
		stop ();

		void
		pause ();

		void
		resume ();

		void
		play_chunk (const std::string& path);

		void
		preload_chunk (const std::string& path);

		void
		preload_chunks (const std::vector<std::string>& paths);


	private:

		std::string song_;
		Mix_Music* mix_;
		static MusicPlayer2D* instance_;
		std::map<std::string, Mix_Chunk*> chunks_;
		MusicPlayer2D () = default;
		MusicPlayer2D (const MusicPlayer2D&) = delete;

		Mix_Chunk*
		chunk_get_ (const std::string& path);

	};

}

#endif //!MUSIC_PLAYER_2D_HH_