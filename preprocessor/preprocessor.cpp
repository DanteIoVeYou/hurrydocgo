#include "preprocessor.h"
namespace hurrydocgo
{
    /**
     * @brief Enumerate html file names recursively
     * 
     * @param g_input_path 
     * @param file_list 
     * @return true 
     * @return false 
     */
    bool PreProcessor::EnumFile(const std::string &g_input_path, std::vector<std::string> *file_list) {
      std::cout << g_input_path << std::endl;
      namespace fs = std::filesystem;
      // 输入文件路径类
      fs::path entry_path(g_input_path);
      // 检查输入路径对象是否存在
      if (!fs::exists(entry_path))
      {
        std::cout << "Input path is invalid" << std::endl;
        return false;
      }
      // 指向一个目录及其子目录的内容的迭代器，默认构造函数。构造尾迭代器
      fs::recursive_directory_iterator end_iter;
      for (fs::recursive_directory_iterator iter(entry_path); iter != end_iter; ++iter)
      {
        // 检查给定文件状态或路径是否对应常规文件。
        if (!fs::is_regular_file(*iter))
        {
          continue;
        }
        // 判断文件后缀是否为.html
        if (iter->path().extension() != HTML)
        {
          continue;
        }
        // 将文件名添加到文件名列表中
        file_list->push_back(iter->path().string());
      }
      return true;
    }

    /**
     * @brief Get title from a html file
     * 
     * @param html 
     * @param title 
     * @return true 
     * @return false 
     */
    bool PreProcessor::ParseTitle(const std::string &html, std::string *title) {

      size_t begin = html.find(TITLE_BEGIN_LABEL);
      if (begin == std::string::npos)
      {
        std::cout << "<title> is not found" << std::endl;
        return false;
      }

      size_t end = html.find(TITLE_END_LABEL);
      if (end == std::string::npos)
      {
        std::cout << "</title> is not found" << std::endl;
        return false;
      }

      begin += TITLE_BEGIN_LABEL.size();
      if (begin >= end)
      {
        std::cout << "Title is invalid" << std::endl;
        return false;
      }

      *title = html.substr(begin, end - begin);

      return true;
    }

    // local path: ../data/input/html/xxx.html
    // online path: https://www.boost.org/doc/libs/1_80_0/doc/html/xxx.html
    /**
     * @brief Get html url and concatenate after prefix url
     * 
     * @param file_path 
     * @param url 
     * @return true 
     * @return false 
     */
    bool PreProcessor::ParseUrl(const std::string &file_path, std::string *url) {
      std::string url_head = "https://www.boost.org/doc/libs/1_80_0/doc";
      std::string url_tail = file_path.substr(g_input_path.size());
      *url = url_head + url_tail;
      return true;
    }

    // 
    /**
     * @brief Remove html label in html string
     * 
     * @param html 
     * @param content 
     * @return true 
     * @return false 
     */
    bool PreProcessor::ParseContent(const std::string &html, std::string *content) {
      bool is_content = true;
      for (auto e : html)
      {
        if (is_content == true)
        {
          if (e == '<')
          {
            is_content = false;
          }
          else
          {
            // deal with '\n'
            if (e == '\n')
            {
              e = ' ';
            }
            // common char
            content->push_back(e);
          }
        }
        else
        {
          if (e == '>')
          {
            is_content = true;
          }
        }
      }
      return true;
    }

    /**
     * @brief Get title, url and content of a html file
     * 
     * @param file_path 
     * @param doc_info 
     * @return true 
     * @return false 
     */
    bool PreProcessor::ParseFile(const std::string &file_path, DocInfo *doc_info) {
      // 1.read file content
      std::string html;
      bool ret = Util::ReadFile(file_path, &html);

      if (!ret)
      {
        std::cout << file_path << " :read file content failing..." << std::endl;
        return false;
      }
      // 2.extract title according to <title></title>
      ret = ParseTitle(html, &doc_info->title);
      if (!ret)
      {
        std::cout << file_path << " :title extracted failing..," << std::endl;
        return false;
      }
      // 3.construct online document url on the basis of file path
      ret = ParseUrl(file_path, &doc_info->url);
      if (!ret)
      {
        std::cout << file_path << " :extract url failing..." << std::endl;
        return false;
      }
      // 4.remove html label
      ret = ParseContent(html, &doc_info->content);
      if (!ret)
      {
        std::cout << file_path << " :remove html label failing..." << std::endl;
        return false;
      }
      return true;
    }

    /**
     * @brief Write a doc_info struct with line text form into new file
     * 
     * @param doc_info 
     * @param ofstream 
     */
    void PreProcessor::WriteOutput(const DocInfo &doc_info, std::ofstream &ofstream) {
      ofstream << doc_info.title << '\3' << doc_info.url << '\3' << doc_info.content << std::endl;
    }

} // namespace end