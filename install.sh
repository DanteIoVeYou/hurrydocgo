#!/bin/bash
###
 # @Description: Auto install script 
 # @Author: @imdanteking
 # @Date: 2022-11-27 01:45:54
 # @LastEditTime: 2022-11-30 10:50:24
### 
CreateThirdPartyDir() {
    rm -rf third_party
    mkdir third_party
    cd third_party
}

DownloadFromGithub() { 
    URL=${1}
    NAME=${2}
    BRANCH="${URL}-master"
    wget ${URL}
    unzip master.zip
    mv ${BRANCH} ${NAME}
    rm -rf master.zip
}

# create third_party directory
CreateThirdPartyDir
# download cppjieba
DownloadFromGithub https://github.com/yanyiwu/cppjieba/archive/refs/heads/master.zip cppjieba
# download limonp
DownloadFromGithub https://github.com/yanyiwu/limonp/archive/refs/heads/master.zip limonp
mv limonp/include/limonp cppjieba/include/cppjieba
rm -rf master.zip limonp
# download cpp-httplib
DownloadFromGithub https://github.com/yhirose/cpp-httplib/archive/refs/heads/master.zip cpp-httplib
# download jsoncpp
sudo yum install jsoncpp-devel -y
# download boost lib
sudo yum install boost -y
sudo yum install boost-devel -y
sudo yum install boost-doc -y
# compile source files
cd ..
cd controller
make
# execute
./hurrydocgo