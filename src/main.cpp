#include <iostream>
#include <dpp/dpp.h>
#include <cstdlib>

#include "../res/envs.hpp"
#include "dpp/dispatcher.h"
#include "dpp/once.h"

int main()
{

    dpp::cluster bot(DISCORD_TOKEN);
    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(
                dpp::slashcommand("ping", "ping pong", bot.me.id)
            );
        }
    });

    bot.start(dpp::st_wait);
    return 0;
}
