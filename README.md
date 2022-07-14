# PDFpro软件设计说明

 ## 基于pdftk命令行工具开发，调用pdftk命令对pdf文件进行处理。
 1、实现PDF文件合并功能
 2、实现PDF文件拆分功能
 3、实现PDF文件加密以及权限管理
 4、点击状态栏更改默认文件存储位置
 5、未进行输出文件夹是否存在判断
 
 合成：
```cpp
pdftk input1.pdf input2.pdf cat output output.pdf///将2个文件合成一个文件
```
 加密：
 ```c++
pdftk input.pdf output output.pdf owner_pw foopass user_pw 123///给pdf文件加上管理员密码和用户密码，其中用户密码用于在阅读时需要输入改密码才能阅读
```
 解密：
 ```c++
pdftk input.pdf input_pw foopass output output.pdf ///调用pdf文件管理员密码解密文件
```
 
 ## 基于QProsses调用其他进程
 
 QProsses 获取进程输出信息，以及调用进程出错信息
 ```cpp
QProcess   *cmdProcess   =   new   QProcess(this);

   connect(cmdProcess,&QProcess::readyReadStandardOutput,this,\[=,&cmdProcess\]()mutable{   //注意我这里lambda表达式的写法，\[\]里的内容需要根据实际情况更改

   QString   Output=cmdProcess->readAllStandardOutput();

   qDebug()<<"Output:"<<Output;

   });

   connect(cmdProcess,&QProcess::readyReadStandardError,this,\[=,&cmdProcess\]()mutable{///失败

   QString   Error=cmdProcess->readAllStandardError();

   qDebug()<<"Error:"<<cmdProcess->readAllStandardError();

   });
```