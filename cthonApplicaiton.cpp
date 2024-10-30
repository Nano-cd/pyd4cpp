// cthonApplicaiton.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <python.h>
#include <vector>

using namespace std;

int main() {

	vector<string> data = {"ss"};

	Py_Initialize();
	// 检查Python是否初始化成功
	if (!Py_IsInitialized()) {
		fprintf(stderr, "Python解释器初始化失败！\n");
		return 1;
	}

	// 添加 .pyd 文件所在目录到 Python 路径
	PyObject* sysPath = PySys_GetObject("path");
	if (!sysPath) {
		PyErr_Print();
		fprintf(stderr, "无法获取sys.path\n");
		return 1;
	}
	// 下面是为导入.pyd文件做准备
	PyObject* pPath = PyUnicode_FromString("E:/project_pycharm/cythondll"); // 这里改成.pyd文件所在目录的路径，原理类似于环境变量
	// 下面是导入python脚本引入的第三方包
	PyObject* pPath_packages = PyUnicode_FromString("E:/project_pycharm/cythondll/venv/Lib/site-packages"); // 将路径改为你调用的python脚本的解释器的 Lib/site-packages 目录

	// 将上述路径加入python系统路径
	PyList_Append(sysPath, pPath);
	Py_DECREF(pPath);
	PyList_Append(sysPath, pPath_packages);
	Py_DECREF(pPath_packages);

	// 导入 Python 模块
	PyRun_SimpleString("print('Hello Python!')\n");
	// 导入 Python 模块
	PyObject* pModule = PyImport_ImportModule("my_python_module");
	if (pModule != NULL) {
		// 获取 Python 函数
		PyObject* pFunction = PyObject_GetAttrString(pModule, "process_data");

		if (pFunction != NULL && PyCallable_Check(pFunction)) {
			// 调用 Python 函数
		


			// 创建参数，由于c++和python的类型不对应，所以要转化
			// 这里根据传入的vector类型的data来创建一个对应列表list
			PyObject* pData = PyList_New(data.size());
			for (int i = 0; i < data.size(); ++i) {
				PyList_SetItem(pData, i, PyBytes_FromString(data[i].c_str())); // 这里要对data[i]转化为python类型
			}

			// 构建一个参数列表，第一个参数为参数列表的参数数量，这里为1
			PyObject* pArgs = PyTuple_Pack(1, pData);
			PyObject* pValue = PyObject_CallObject(pFunction, pArgs);

			Py_DECREF(pArgs);
			if (pValue != nullptr) {
				// 声明一个结果的数组
				std::vector<long> result{};
				// 从pValue中取值
				PyObject* returnvalue1 = PyTuple_GetItem(pValue, 0);
				PyObject* returnvalue2 = PyTuple_GetItem(pValue, 1);
				PyObject* returnvalue3 = PyTuple_GetItem(pValue, 2);
				PyObject* returnvalue4 = PyTuple_GetItem(pValue, 3);

				double result1 = PyFloat_AsDouble(returnvalue1);
				double result2 = PyFloat_AsDouble(returnvalue2);
				double result3 = PyFloat_AsDouble(returnvalue3);
				double result4 = PyFloat_AsDouble(returnvalue4);

				std::cout << "Out put a: " << result1 << std::endl;
				std::cout << "Out put b: " << result2 << std::endl;
				std::cout << "Out put c: " << result3 << std::endl;
				std::cout << "Out put d: " << result4 << std::endl;
				Py_DECREF(pValue);
			}
			else {
				PyErr_Print();
			}
			Py_DECREF(pFunction);
		}
		else {
			PyErr_Print();
		}

		Py_DECREF(pModule);
	}
	else {
		PyErr_Print();
	}

	Py_Finalize();

	return 0;
}
