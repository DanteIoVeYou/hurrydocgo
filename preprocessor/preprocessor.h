/*
 * @Description: 
 * @version: 
 * @Author: @imdanteking
 * @Date: 2022-11-24 19:43:38
 * @LastEditTime: 2022-11-26 01:24:08
 */

#pragma once
// The model is to pretreat
// - read and analyse htmls from boost
// - get title. url and contents wuthout html labels
// - output is texts

#include <filesystem>
#include "../common/util.hpp"

//   core steps
// 1.get all the urls of html files
// 2.read contents of all html files following urls and analyse them
// 3.write contents into output files

namespace hurrydocgo
{

  /**
   * @brief Preprocessor module
   * 
   */
  class PreProcessor
  {
  public:

    /**
     * @brief Enumerate html file names recursively
     * 
     * @param g_input_path 
     * @param file_list 
     * @return true 
     * @return false 
     */
    static bool EnumFile(const std::string &g_input_path, std::vector<std::string> *file_list); 

    /**
     * @brief Get title from a html file
     * 
     * @param html 
     * @param title 
     * @return true 
     * @return false 
     */
    static bool ParseTitle(const std::string &html, std::string *title);

    /**
     * @brief Get html url and concatenate after prefix url
     * 
     * @param file_path 
     * @param url 
     * @return true 
     * @return false 
     */
    static bool ParseUrl(const std::string &file_path, std::string *url);

    /**
     * @brief Remove html label in html string
     * 
     * @param html 
     * @param content 
     * @return true 
     * @return false 
     */
    static bool ParseContent(const std::string &html, std::string *content);

    /**
     * @brief Get title, url and content of a html file
     * 
     * @param file_path 
     * @param doc_info 
     * @return true 
     * @return false 
     */
    static bool ParseFile(const std::string &file_path, DocInfo *doc_info);

    /**
     * @brief Write a doc_info struct with line text form into new file
     * 
     * @param doc_info 
     * @param ofstream 
     */
    static void WriteOutput(const DocInfo &doc_info, std::ofstream &ofstream);

  };
} // namespace end
