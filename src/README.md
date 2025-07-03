##### Antrl4
```bash

//安装jdk
sudo apt-get install openjdk-17-jre-headless

//删除旧版本（可选）
sudo rm /usr/local/lib/antlr-4.12.0-complete.jar

//安装antlr4
cd /usr/local/lib
sudo curl -O https://www.antlr.org/download/antlr-4.13.1-complete.jar

export CLASSPATH=".:/usr/local/lib/antlr-4.13.1-complete.jar:$CLASSPATH"
//配置别名
alias antlr4='java -jar /usr/local/lib/antlr-4.13.1-complete.jar'
alias grun='java org.antlr.v4.gui.TestRig'

//使 bashrc 生效
source ./bashrc

//antlr4 4.12.0 C++ 运行时 安装运行时库
wget https://www.antlr.org/download/antlr4-cpp-runtime-4.13.1-source.zip
unzip antlr4-cpp-runtime-4.13.1-source.zip -d antlr4-cpp-runtime-4.13.1

//开始编译
cd antlr4-cpp-runtime-4.13.1
mkdir build && mkdir run && cd build
cmake .. 
make install DESTDIR=../run

//把生成的文件放在系统文件中
cd ../run/usr/local/include
sudo \cp -r antlr4-runtime/* /usr/local/include
cd ../lib
sudo \cp -r * /usr/local/lib
sudo ldconfig

//生成指令
antlr4 ToyC.g4 -Dlanguage=Cpp -no-listener -visitor -o generated/

//编译
mkdir build && cd build
cmake ..
make

//对目标文件进行处理
./parser ../test.tc

```
