set(SOURCE_FILES
        Game.cpp Game.hpp
        util.cpp util.hpp
        logging.hpp
        rendering.hpp
        objects/GameTicker.cpp
        objects/GameTicker.hpp
        objects/ObjectScene.cpp
        objects/ObjectScene.hpp
        objects/Player.cpp
        objects/Player.hpp
        objects/Asteroid.cpp
        objects/Asteroid.hpp
        objects/LaserShot.cpp
        objects/LaserShot.hpp
        objects/collision.cpp
        objects/collision.hpp
        rendering/GLContextRenderer.cpp
        rendering/GLContextRenderer.hpp
        rendering/PlayerRenderer.cpp
        rendering/PlayerRenderer.hpp
        rendering/AsteroidRenderer.cpp
        rendering/AsteroidRenderer.hpp
        rendering/LaserShotRenderer.cpp
        rendering/LaserShotRenderer.hpp
        rendering/SDLWindow.cpp
        rendering/Shader.cpp
        rendering/Shader.hpp
        rendering/SimpleTextOverlay.cpp
        rendering/SimpleTextOverlay.hpp
        )

cxx_library(asteroids_lib ${SOURCE_FILES})
