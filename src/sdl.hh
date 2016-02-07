/** @file SDL multiplatform include instruction
 */

#ifndef SDL_HH_
# define SDL_HH_

# ifdef __linux__
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
#  include <SDL2/SDL_ttf.h>
#  include <SDL2/SDL_mixer.h>
# endif //__linux__

#endif //!SDL_HH_