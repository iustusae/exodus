/**
 * @file main.cpp
 * @author iustus (lindgreiae@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-06-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <cstdlib>
#include <dpp/dpp.h>
#include <iostream>
#include <string>

#include "../res/envs.hpp"
#include "dpp/dispatcher.h"
#include "dpp/intents.h"
#include "dpp/message.h"
#include "dpp/once.h"

#include "core/SpellReader.hpp"

int main() {
  dpp::cluster bot(DISCORD_TOKEN,
                   dpp::i_default_intents | dpp::i_message_content);

  bot.on_log(dpp::utility::cout_logger());

  bot.on_slashcommand([](const dpp::slashcommand_t &event) {
    if (event.command.get_command_name() == "ping") {
      auto start_time = std::chrono::steady_clock::now();

      auto end_time = std::chrono::steady_clock::now();
      auto ping_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                           end_time - start_time)
                           .count();

      std::string response;
      if (ping_time < 50) {
        response = "**Ping time**: " + std::to_string(ping_time) + "ms\n";
        response += "That's faster than a Golden Snitch! :zap:";
      } else if (ping_time < 100) {
        response = "**Ping time**: " + std::to_string(ping_time) + "ms\n";
        response += "As fast as a lightning-quick owl! :owl: ⚡";
      } else if (ping_time < 200) {
        response = "**Ping time**: " + std::to_string(ping_time) + "ms\n";
        response += "oof... You got yourself an *Errol* internet...";
      } else {
        response = "**Ping time**: " + std::to_string(ping_time) + "ms\n";
        response += "Slower than the troll in the dungeons... :snail:";
      }

      event.reply(dpp::message(response).set_flags(dpp::m_ephemeral));
    }
  });

  bot.on_ready([&bot](const dpp::ready_t &event) {
    if (dpp::run_once<struct register_bot_commands>()) {
      bot.global_command_create(
          dpp::slashcommand("ping", "owl speed meter", bot.me.id));
          
    }
  });

  bot.start(dpp::st_wait);

  return 0;
}
