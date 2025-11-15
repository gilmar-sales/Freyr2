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
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED: {
            Application::Get().getWindow().close();
        }
        case SDL_EVENT_WINDOW_RESIZED: {
            Application::Get().getWindow().updateSize(event.window.data1, event.window.data2);
            break;
        }
        case SDL_EVENT_KEY_DOWN: {
            auto key = (KeyCode)event.key.scancode;

            if (!m_pressedKeys.contains(key))
            {
                notify(KeyDownEvent{.key = key});

                m_pressedKeys.insert(key);
            }
            break;
        }
        case SDL_EVENT_KEY_UP: {
            auto key = (KeyCode)event.key.scancode;

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
