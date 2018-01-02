//
// Created by mazrog on 21/12/17.
//

#ifndef ENGINE_GUIMANAGER_HPP
#define ENGINE_GUIMANAGER_HPP

#include "gui.hpp"

using MapGUI = std::map<std::string, GUI *>;

class GuiManager {
public:
    GuiManager();
    ~GuiManager();

    void add(GUI * gui);

    void spread_events();

    void clear();

    /* Getters */
    MapGUI const& get_guis() const { return guis; }

protected:
    MapGUI  guis;
};


#endif //ENGINE_GUIMANAGER_HPP
