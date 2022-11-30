# hurrydocgo! A quick site search engine builder
 **English** | [Chinese](./README.md)   

---
## Development Environment 
> The project is developed and debugged with centos7.5, boost and jsoncpp is dependent on yum, if you want to deploy it on other release versions, please install them with appropriate package manager.
- compiler: g++ 9.3.1 (support C++17)
- linux kernel：3.10.0-862.el7.x86_64
- Third party library：boost, cppjieba, jsoncpp, cpp-httplib

## Modules 
- Spider: `wget -r -np -k url`
- Controller 
- html File Preprocessor
- Index Builder 
- Searcher 
- httpd

