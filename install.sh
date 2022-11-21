rm -rf third_party
mkdir third_party
cd third_party
# download cppjieba
wget https://github.com/yanyiwu/cppjieba/archive/refs/heads/master.zip
unzip master.zip 
mv cppjieba-master cppjieba
rm -rf master.zip
cd ..
# download jsoncpp
sudo yum install jsoncpp-devel

# cd controller
# make
# ./hurrydocgo