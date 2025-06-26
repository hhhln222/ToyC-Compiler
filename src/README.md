##### Antrl4
```bash

//安装jdk
sudo apt-get install openjdk-17-jre-headless

//安装antlr4
cd /usr/local/lib
sudo curl -O https://www.antlr.org/download/antlr-4.12.0-complete.jar
`wget https://www.antlr.org/download/antlr-4.12.0-complete.jar`
export CLASSPATH=".:/usr/local/lib/antlr-4.12.0-complete.jar:$CLASSPATH"

//配置别名
alias antlr4='java -jar /usr/local/lib/antlr-4.12.0-complete.jar'
alias grun='java org.antlr.v4.gui.TestRig'

//使 bashrc 生效
source ./bashrc

//antlr4 4.12.0 C++ 运行时 安装运行时库
wget https://www.antlr.org/download/antlr4-cpp-runtime-4.12.0-source.zip
unzip antlr4-cpp-runtime-4.12.0-source.zip -d antlr4-cpp-runtime-4.12.0

//开始编译
cd antlr4-cpp-runtime-4.12.0/
mkdir build && mkdir run && cd build
cmake .. 
make install DESTDIR=../run

//把生成的文件放在系统文件中
cd ../run/usr/local/include
sudo \cp -r antlr4-runtime/* /usr/local/include
cd ../lib
sudo \cp -r * /usr/local/lib
sudo ldconfig

使用
antlr4 -Dlanguage=Cpp ToyC.g4

生成指令
antlr4 ToyC.g4 -Dlanguage=Cpp -no-listener -visitor -o generated/
```
