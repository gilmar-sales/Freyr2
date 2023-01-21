#include "InputSystem.hpp"

#include "../Core/Application.hpp"
#include "../Events/InputEvents.hpp"

#include <execution>

void InputSystem::onUpdate()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_WINDOWEVENT_RESIZED: {
            Application::Get().getWindow().updateSize(event.window.data1, event.window.data2);
            break;
        }
        case SDL_KEYDOWN: {
            auto key = (KeyCode)event.key.keysym.scancode;

            if (!m_pressedKeys.contains(key))
            {
                notify(KeyDownEvent{.key = key});

                m_pressedKeys.insert(key);
            }
            break;
        }
        case SDL_KEYUP: {
            auto key = (KeyCode)event.key.keysym.scancode;

            notify(KeyUpEvent{.key = key});
            notify(KeyPressedEvent{.key = key, .value = 0.0f});

            m_pressedKeys.remove(key);
            break;
        }
        default:
            break;
        }
    }

    std::for_each(std::execution::par, m_pressedKeys.begin(), m_pressedKeys.end(),
                  [&](auto key) { notify(KeyPressedEvent{.key = key, .value = 1.0f}); });
}
