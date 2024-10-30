# pyd4cpp
C++ calls the pyd file so that Python can run on the C++ platform, but you also need to install the python environment, but the pyd is encrypted


python DLL
-------------
1、首先编写原始的py代码，确保该代码能够正常运行，
建议将外部库调用情况降低到最低，比如以下模块：
[my_python_module.py](my_python_module.py)

2、同时创建文件.pyx作为待编译的文件，该文件为对应py代码
的内容复制：
[my_python_module.pyx](my_python_module.pyx)

3、你可以创建requirements.txt来保证所需要用到的库：
[requirements.txt](requirements.txt)

4、编写[setup.py](setup.py)，并在命令段执行以下代码
python setup.py build_ext --inplace

5、编译完成生成[build](build)文档，与编译中间文件[my_python_module.c](my_python_module.c)
以及我们所需要使用到的目标文件：[my_python_module.pyd](my_python_module.pyd)


C++ 调用
-------------
至此python文件的准备部分就结束了。


1、C++环境配置，需要包含python的debug和realse版本的安装，且
安装的python版本与PYTHON DLL生成的版本需要一致。配置环境包含
Python的lib和include路径。

2、C++调用函数，需要包含#include <python.h>头文件，具体代码如下：
[cthonApplicaiton.cpp](cthonApplicaiton.cpp)


Python 调用
-------------

1、将生成的pyd文件直接放进python路径下的DLL文件库中：
C:\Users\Lfchengdi\AppData\Local\Programs\Python\Python38\DLLs，
然后你就可以像掉库那样直接import your_module了
