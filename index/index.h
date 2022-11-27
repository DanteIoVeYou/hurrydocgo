#pragma once
#include "../common/util.hpp"
#include "../third_party/cppjieba/include/cppjieba/Jieba.hpp"

namespace hurrydocgo
{
    /**
     * @brief index module 
     * 
     */
    class Index
    {

    public:
        /**
         * @brief Construct a new Index object
         * 
         */
        Index();

        /**
         * @brief Get the Doc Info object by doc_id
         * 
         * @param doc_id 
         * @return const DocInfo, pointer to use NULL to indicate invalid situation
         */
        const DocInfo *GetDocInfo(int64_t doc_id);

        /**
         * @brief Get the Inverted List object by key
         * 
         * @param key 
         * @return const InvertedList* 
         */
        const InvertedList *GetInvertedList(const std::string &key);

        /**
         * @brief  Build the Index
         * 
         * @param input_path 
         * @return true 
         * @return false 
         */
        bool Build(const std::string &input_path);

        /**
         * @brief Cut word by jieba
         * 
         * @param input 
         * @param output 
         */
        void CutWord(const std::string &input, std::vector<std::string> *output);

    private:
        /**
         * @brief Build forward index, using '\3' to cut title, url, content and convert to DocInfo
         * 
         * @param line 
         * @return DocInfo* 
         */
        DocInfo *BuildForward(const std::string &line);

        /**
         * @brief Build inverted index
         * 
         * @param doc_info 
         */
        void BuildInverted(const DocInfo &doc_info);

    private:
        /**
         * @brief Forward Index
         * 
         */
        std::vector<DocInfo> m_forward_index;

        /**
         * @brief Inverted Index 
         * 
         */
        std::unordered_map<std::string, InvertedList> m_inverted_index;

        /**
         * @brief Jieba Object
         * 
         */
        cppjieba::Jieba m_jieba;

    };
} // namespace end