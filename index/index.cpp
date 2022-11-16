#include "index.h"
#include <algorithm>
namespace hurrydocgo{

  const static size_t PROCESS_BAR_LENGTH = 102;

  Index::Index()
    : jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH){}

  void ProcessBar(int64_t line_amount, int64_t doc_id) {
    char pb[PROCESS_BAR_LENGTH] = {0};
    char state[4] = {'-', '\\', '|', '/'};
    pb[0] = '[';
    pb[PROCESS_BAR_LENGTH - 1] = ']';
    int64_t mark_amount = (doc_id + 2) * 100 / line_amount;
    for(int i = 1; i <= mark_amount; i++) {
      pb[i] = '#';
    }
    for(int i = 0; i < PROCESS_BAR_LENGTH; i++) {
      if(pb[i] != 0) {
        cout << pb[i];
      }
      else {
        cout << " ";
      }
    }
    cout << " [%" << mark_amount << "] [" << state[mark_amount % 4] << "]";
    if(mark_amount == 100) {
      sleep(1);
    }
    std::fflush(stdout);
    cout << '\r';
  }

  const DocInfo* Index::GetDocInfo(int64_t doc_id) {

    if(doc_id < 0 || doc_id > forward_index.size()) {
      return nullptr;
    }
    return &forward_index[doc_id];

  }

  const InvertedList* Index::GetInvertedList(const std::string& key) {
    unordered_map<string, InvertedList>::iterator it = inverted_index.find(key);
    if(it == inverted_index.end()) {
      return nullptr;
    }
    return &it->second;
  }

  bool Index::Build(const std::string& input_path) {

    // 1. read raw_input file, which is a line txt that means each line stands for a html file 
    std::cout << "Start Build Index..." << std::endl; 
    std::ifstream file(input_path.c_str());
    if(!file.is_open()) {
      std::cout << "Read raw_input Failing..." << std::endl;
      return false;
    }

    // get number of lines in line 
    std::ifstream tmpfile(input_path.c_str());
    string tmpline;
    int64_t line_amount = 0;
    while(std::getline(tmpfile, tmpline)) {
      line_amount++;
    }
    string line;
    while(std::getline(file, line)) {

      // 2. convert each line to  DocInfo , construct ForwardIndex
      DocInfo* doc_info = BuildForward(line);
      if(!doc_info) {
        std::cout << "Construct Failing..." << std::endl;
        continue;
      }
      // 3. using ForwardIndex to Build Inverted Index
      BuildInverted(*doc_info);
      // print process bar
      ProcessBar(line_amount, (*doc_info).doc_id);
      
    }
    

    std::cout << "Finish Build Index..." << std::endl;
    file.close();
    return true;
  }


  // use '\3' to cut title, url, content and convert to DocInfo
  DocInfo* Index::BuildForward(const std::string& line) {
    vector<string> tokens;
    // 1.Split raw_input with "\3"
    common::Util::Split(line, "\3", &tokens);
    if(tokens.size() != 3) {
      // Split failed if string is not consisted of 3 strings
      return nullptr;
    }
    // 2.put token into DocInfo 
    DocInfo doc_info;
    doc_info.doc_id = forward_index.size();
    doc_info.title = tokens[0];
    doc_info.url = tokens[1];
    doc_info.content = tokens[2];
    forward_index.push_back(std::move(doc_info));
    return &forward_index.back();
  }

  void Index::BuildInverted(const DocInfo& doc_info) {
    struct WordCut{
      int title_cnt;
      int content_cnt;

      WordCut()
        :title_cnt(0)
        ,content_cnt(0){}
    };
    unordered_map<string, WordCut> word_cut_map;
    //1.title segment
    vector<string> title_token;
    CutWord(doc_info.title, &title_token);
    //2.traversal, count frequency of title words
    for(string word: title_token) {
      boost::to_lower(word); // convert all character to lower
      ++word_cut_map[word].title_cnt;
    }
    //3.content segment
    vector<string> content_token;
    CutWord(doc_info.content, &content_token);
    //4.traversal, count frequency of content words
    for(string word: content_token) {
      boost::to_lower(word);
      ++word_cut_map[word].content_cnt;
    }

    //5.deal with weight
    for(const auto& word_pair: word_cut_map) {
      Weight weight;
      weight.doc_id = doc_info.doc_id;
      // weight = title_cnt * 10 + content_cnt * 1
      weight.weight = 10 * word_pair.second.title_cnt + word_pair.second.content_cnt;
      weight.word = word_pair.first;
      //insert word into inverted_index
      InvertedList& invert_list = inverted_index[word_pair.first];
      invert_list.push_back(weight);
    }

  }
  
  void Index::CutWord(const std::string& input, std::vector<std::string>* output) {
    jieba.CutForSearch(input, *output);
  }
 

} // namespace end