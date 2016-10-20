set(SOURCE_FILES
        Game.cpp Game.hpp
        util.cpp util.hpp
        logging.hpp
        objects.hpp
        rendering.hpp
        objects/GameTicker.cpp
        objects/GameTicker.hpp
        objects/ObjectScene.cpp
        objects/Player.cpp
        objects/Player.hpp
        rendering/GLContextRenderer.cpp
        rendering/GLContextRenderer.hpp
        rendering/PlayerRenderer.cpp
        rendering/PlayerRenderer.hpp
        rendering/SDLWindow.cpp
        rendering/Shader.cpp
        rendering/Shader.hpp
        )

cxx_library(asteroids_lib ${SOURCE_FILES})
