#pragma once

#include "dpp/message.h"
#include "dpp/nlohmann/json_fwd.hpp"
#include <string>
#include <nlohmann/json.hpp>

class SpellReader {
    private:
        const std::string p_Url = "https://api.potterdb.com/v1/spells" ;
    
    public:
        nlohmann::json spells;

    public:
        SpellReader();
        void get_json_spells();
        std::string all_spells_to_string();
        dpp::embed spec_spell_to_embed();
        
};