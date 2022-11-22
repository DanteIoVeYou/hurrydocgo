rm -rf third_party
mkdir third_party
cd third_party
# download cppjieba
wget https://github.com/yanyiwu/cppjieba/archive/refs/heads/master.zip
unzip master.zip 
mv cppjieba-master cppjieba
rm -rf master.zip
# download limonp
wget https://github.com/yanyiwu/limonp/archive/refs/heads/master.zip
unzip master.zip 
mv limonp-master/include/limonp cppjieba/include/cppjieba
rm -rf master.zip limonp-master
# download cpp-httplib
wget https://github.com/yhirose/cpp-httplib/archive/refs/heads/master.zip
unzip master.zip
mv cpp-httplib-master cpp-httplib
rm -rf master.zip
# download jsoncpp
sudo yum install jsoncpp-devel -y
# download boost lib
sudo yum install boost -y
sudo yum install boost-devel -y
sudo yum install boost-doc -y
cd ..
cd controller
make
./hurrydocgo