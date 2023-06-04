/**
 * @file SpellReader.cpp
 * @author iustus (lindgreiae@gmail.com)
 * @brief Implementation of the SpellReader class defined in the header
 * @version 0.1
 * @date 2023-06-03
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <cstddef>
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

#include "SpellReader.hpp"

/**
 * @brief Default constructor for SpellReader class.
 */
SpellReader::SpellReader(){};

/**
 * @brief Callback function to receive response data from libcurl.
 *
 * @param contents Pointer to the received data buffer.
 * @param size Size of each data element.
 * @param nmemb Number of data elements.
 * @param response Pointer to the response string to append the received data.
 * @return Total size of the received data.
 */
static size_t wr_callback(void *contents, size_t size, size_t nmemb,
                          std::string *response) {
  size_t total_s = size * nmemb;
  response->append(static_cast<char *>(contents), total_s);
  return total_s;
}

// /**
//  * @brief Fetches JSON spells from a remote API.
//  *
//  *
//  */
// dpp::embed SpellReader::all_spells_to_embed() {
//   dpp::embed embed = dpp::embed()
//     .set_author("Patronus Charm", "",
//     "https://cdn.discordapp.com/avatars/1113625763355295754/c30f4daf9b6cc34f7aa0dabc23dfa15d.png")
//     .set_title("All Harry Potter Spells")
//     .set_url("https://api.potterdb.com/v1/spells")
//     .set_description("(almost) all the spells mentioned in the Harry Potter
//     Series, atcha wands!")
//     .set_thumbnail("https://cdn.discordapp.com/avatars/1113625763355295754/c30f4daf9b6cc34f7aa0dabc23dfa15d.png");

//   if (!this->spells)
//   {
//     embed.add_field("An Error has occurred", "Failed to fetch the spells");
//     return embed;
//   }

//   for (const auto& spell : this->spells["data"])
//   {
//     std::string name = spell["attributes"]["name"].get<std::string>();
//     std::string description;

//     if (spell["attributes"]["effect"].is_null()) {
//       description = "No effect specified";
//     } else {
//       description = spell["attributes"]["effect"].get<std::string>();
//     }

//     embed.add_field(name, description);
//   }

//   return embed;
// }

std::string SpellReader::all_spells_to_string() {
  std::string result;

  result += "**All Harry Potter Spells**\n";
  result += "(almost) all the spells mentioned in the Harry Potter Series, atcha wands!\n\n";

  if (!this->spells) {
    result += "An Error has occurred: Failed to fetch the spells";
    return result;
  }

  for (const auto &spell : this->spells["data"]) {
    std::string name = spell["attributes"]["name"].get<std::string>();
    std::string description = " ";

    // if (spell["attributes"].contains("effect")) {
    //   if (spell["attributes"]["effect"].is_null()) {
    //     description = "No effect specified";
    //   } else if (spell["attributes"]["effect"].is_boolean()) {
    //     description = spell["attributes"]["effect"].get<bool>() ? "True" : "False";
    //   } else {
    //     description = spell["attributes"]["effect"].get<std::string>();
    //   }
    // } else {
    //   description = "Effect data not available";
    // }

    result += "**" + name + "**: " + description + "\n";
  }

  return result;
}
