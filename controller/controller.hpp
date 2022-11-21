#pragma once
#include "../preprocessor/preprocessor.hpp"
#include "../searcher/searcher.h"
#include "../third_party/cpp-httplib/httplib.h"
#include <memory>

namespace hurrydocgo
{
    class Controller
    {
    public:
        Controller() : m_searcher(std::make_shared<Searcher>()) {}

        ~Controller() {}

        void Init()
        {
            BuildPreProcessor();
            BuildSearcher();
            BuildQueryService();
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

        void BuildQueryService()
        {
            using namespace httplib;
            Server server;
            server.Get("/searcher", [&searcher](const Request &req, Response &resp) {
                (void)req;
                if(!req.has_param("query")) {
                  resp.set_content("Invalid Paramenter", "text/plain; charset=utf-8");
                }
                string query = req.get_param_value("query");
                string results;
                m_searcher.Search(query, &results);
                resp.set_content(results, "application/json; charset=utf-8"); 
            });
            // set static resources path
            server.set_base_dir("../wwwroot");
            // 3.Start Server
            server.listen("0.0.0.0", 10002);
        }
    };

public:
    std::shared_ptr<Searcher> m_searcher;
} // namespace end