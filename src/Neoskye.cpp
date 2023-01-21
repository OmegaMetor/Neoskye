#include "Neoskye.hpp"
#include "EngineOptions.hpp"
#include "util/Types.hpp"
#include <SFML/Window.hpp>
#include <optional>

// i have lost my c++ template virginity
template <typename T> inline T UnwrapOptional(const std::optional<T>& optional) {
    if (optional.has_value())
        return optional.value();
    throw "Failed to unwrap optional!";
}

namespace neoskye {
Neoskye::Neoskye(EngineOptions& opts) {
    auto width = UnwrapOptional(opts.GetUnsignedFlag("-width"));
    auto height = UnwrapOptional(opts.GetUnsignedFlag("-height"));
    auto title = UnwrapOptional(opts.GetStringFlag("title"));
    this->win.create(sf::VideoMode(width, height), title);
}

u16 Neoskye::Run() {
    while (this->win.isOpen()) {
        sf::Event event;
        while (this->win.pollEvent(event)) {
            if (this->HandleEvent(event))
                this->win.close();
        }
    }

    return 0;
}

// return true if the window should close
bool Neoskye::HandleEvent(sf::Event& ev) {
    switch (ev.type) {
    case sf::Event::Closed:
        return true;
    default:
        return false;
    }
}

} // namespace neoskye