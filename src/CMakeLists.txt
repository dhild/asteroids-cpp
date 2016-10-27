set(SOURCE_FILES
        Game.cpp Game.hpp
        util.cpp util.hpp
        logging.hpp
        rendering.hpp
        objects/GameTicker.cpp
        objects/GameTicker.hpp
        objects/ObjectScene.cpp
        objects/ObjectScene.hpp
        player/Player.hpp
        player/DrawablePlayer.cpp
        player/DrawablePlayer.hpp
        player/PlayerRenderer.cpp
        player/PlayerRenderer.hpp
        asteroid/Asteroid.hpp
        asteroid/CircularAsteroid.cpp
        asteroid/CircularAsteroid.hpp
        asteroid/AsteroidRenderer.cpp
        asteroid/AsteroidRenderer.hpp
        shot/Shot.hpp
        shot/LaserShot.cpp
        shot/LaserShot.hpp
        shot/LaserShotRenderer.cpp
        shot/LaserShotRenderer.hpp
        rendering/GLContextRenderer.cpp
        rendering/GLContextRenderer.hpp
        rendering/SDLWindow.cpp
        rendering/Shader.cpp
        rendering/Shader.hpp
        rendering/SimpleTextOverlay.cpp
        rendering/SimpleTextOverlay.hpp
        )

cxx_library(asteroids_lib ${SOURCE_FILES})
