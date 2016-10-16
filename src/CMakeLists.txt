set(SOURCE_FILES
        Game.cpp Game.hpp
        objects.hpp
        rendering.hpp
        objects/ObjectScene.cpp
        objects/Player.cpp
        rendering/GLContextRenderer.cpp
        rendering/GLContextRenderer.hpp
        rendering/SDLWindow.cpp
        )

cxx_library(asteroids_lib ${SOURCE_FILES})
