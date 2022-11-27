/*
 * @Description: 
 * @version: 
 * @Author: @imdanteking
 * @Date: 2022-11-25 12:17:36
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-11-26 01:23:56
 */
#pragma once
#include <stdint.h>
#include <unistd.h>
#include <json/json.h>
#include "../index/index.h"

namespace hurrydocgo{

  /**
   * @brief searcher module 
   * 
   */
  class Searcher {

    public:
      /**
       * @brief Construct a new Searcher object
       * 
       */
      Searcher();

      /**
       * @brief initialize searcher by building index
       * 
       * @param input_path 
       * @return true 
       * @return false 
       */
      bool Init(const std::string& input_path);

      /**
       * @brief search pages by query word
       * 
       * @param query 
       * @param output 
       * @return true 
       * @return false 
       */
      bool Search(const std::string& query, std::string* output);
 
    private:

      /**
       * @brief Generate descirption for each page
       * 
       * @param content 
       * @param word 
       * @return std::string 
       */
      std::string GenerateDescription(const std::string& content, const std::string& word);

    private:

      /**
       * @brief index object pointer
       * 
       */
      Index* m_index;
  };
} // namesapce end
