//
// Created by mazrog on 05/01/18.
//

#ifndef ENGINE_MAINGUIMANAGER_HPP
#define ENGINE_MAINGUIMANAGER_HPP

#include <functional>
#include <gui/guiManager.hpp>
#include <gamestate.hpp>

using GuiEvents = std::function<void(GuiManager *, GameState *)>;

class MainGuiManager : public GuiManager {
public:
    explicit MainGuiManager(GameState * state, GuiEvents events = [](GuiManager *, GameState *) {});
    ~MainGuiManager();

    void spread_events() override;

private:
    GameState     * state;
    GuiEvents       events;
};


#endif //ENGINE_MAINGUIMANAGER_HPP
