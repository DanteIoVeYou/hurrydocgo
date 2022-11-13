rm -rf third_party
mkdir third_party
cd third_party
# download cppjieba
wget https://github.com/yanyiwu/cppjieba/archive/refs/heads/master.zip
unzip master.zip 
mv cppjieba-master cppjieba
rm -rf master.zip
# download jsoncpp
wget https://github.com/open-source-parsers/jsoncpp/archive/refs/heads/master.zip
unzip master.zip
mv jsoncpp-master jsoncpp
rm -rf master.zip
#



# cd controller
# make
# ./hurrydocgo