# hurrydocgo! 快速站内搜索引擎构建器
| [英文](/README-EN.md)| **中文**  

## 开发环境
> 项目基于centos7.5发行版进行开发及调试，install.sh中的boost与jsoncpp库的安装基于yum包管理器，如需在其他linux发行版上部署该项目，请使用对应的包管理器进行安装
- 编译器：g++ 9.3.1（必须支持C++17语法）
- linux kernel：3.10.0-862.el7.x86_64
- 依赖的第三方库：boost, cppjieba, jsoncpp, cpp-httplib

## 项目模块
- 全站爬虫: `wget -r -np -k url`
- 控制器
- html文件预处理器
- 索引构建器
- 搜索器
- httpd

