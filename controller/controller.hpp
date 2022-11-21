#pragma once
#include "../preprocessor/preprocessor.hpp"
#include "../searcher/searcher.h"
#include <memory>

namespace hurrydocgo
{
    class Controller
    {
    public:
        Controller(): m_searcher(std::make_shared<Searcher>()) {}

        ~Controller() {}

        void Init()
        {
            BuildPreProcessor();
            BuildSearcher();
        }

    private:

        void BuildPreProcessor()
        {
            // enumerate urls
            std::vector<std::string> file_list;
            bool ret = hurrydocgo::PreProcessor::EnumFile(hurrydocgo::g_input_path, &file_list);

            if (!ret)
            {
                std::cout << "Enumerate failing..." << std::endl;
                return;
            }

            // traverse the html directory and deal with every html file
            int ans = 0;
            std::ofstream output_file(hurrydocgo::g_output_path.c_str());
            if (!output_file.is_open())
            {
                std::cout << "open output_file failing..." << std::endl;
            }
            for (auto file_path = file_list.begin(); file_path != file_list.end(); ++file_path)
            {
                std::cout << *file_path << std::endl;
                ++ans;
                // create DocInfo structure to store every html file infomation
                DocInfo doc_info;
                //
                ret = hurrydocgo::PreProcessor::ParseFile(*file_path, &doc_info);
                if (!ret)
                {
                    std::cout << "Parse file failing:" << *file_path << std::endl;
                    continue;
                }

                // wirte dec_info into file
                hurrydocgo::PreProcessor::WriteOutput(doc_info, output_file);
            }
            std::cout << "There are " << ans << " html files in total..." << std::endl;
        }

        void BuildSearcher()
        {
            // 初始化构建索引
            m_searcher->Init(g_output_path);
        }
    };

    public:
        std::shared_ptr<Searcher> m_searcher;
} // namespace end