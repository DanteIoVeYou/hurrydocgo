#pragma once
#include "../preprocessor/preprocessor.h"
#include "../searcher/searcher.h"
#include "../third_party/cpp-httplib/httplib.h"

namespace hurrydocgo
{
    /**
     * @brief controller module
     * 
     */
    class Controller
    {
    public:
        /**
         * @brief Construct a new Controller object
         * 
         */
        Controller();
        /**
         * @brief Destroy the Controller object
         * 
         */
        ~Controller();
        /**
         * @brief Init controller 
         * 
         */
        void Init();
    private:
        /**
         * @brief preprocess html files
         * 
         */
        void BuildPreProcessor(); 
        /**
         * @brief build forword_index, inverted_index and searcher
         * 
         */
        void BuildSearcher();
        /**
         * @brief build http server and provide search service
         * 
         */
        void BuildQueryService();
    public:
        /**
         * @brief searcher object pointer
         * 
         */
        Searcher* m_searcher;
    };
} // namespace end