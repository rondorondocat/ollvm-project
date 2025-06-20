# The OLLVM patch for LLVM Project

## 前言
<summary>这个项目致力于提供最新版本的完整功能的ollvm支持</summary>
<summary>目前已适配19.1.7 Release,之后会跟随llvm-project主线大版本更新</summary>

## 捐赠


<summary>如你所见，ollvm官方的llvm版本一直停留在llvm 4.0</summary>
<summary>维护新版本的代码是一件劳形苦心的事情，需要长期的人力投入</summary>
<summary>如果这个项目有帮助到你，可以考虑请我喝杯咖啡</summary>
<img src="https://github.com/rondorondocat/ollvm-project/blob/master/tutorial_demo/res/paymecoffee.jpg"/>


## 编译与安装

```bash
git clone https://github.com/rondorondocat/ollvm-project.git
cd llvm-project
mkdir build
cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_EH=OFF -DLLVM_ENABLE_RTTI=OFF -DLLVM_ENABLE_ASSERTIONS=ON -DLLVM_TARGETS_TO_BUILD="X86" -DLLVM_ENABLE_PROJECTS="clang;lld" ../llvm
make
sudo make install
clang --version
```

## 功能介绍与使用
我们考虑一个简单的例子,TEA加密,示例代码位于./tutorial_demo/demo.c，请自行编译尝试

### 正常编译：
```bash
cd tutorial_demo
mkdir build
clang demo.c -o ./build/demo
./build/demo
```

<details> 
<summary> 预期结果：</summary>

```bash
Original : 0123456789ABCDEF
Encrypted: F7B3522EA0CA479A
Decrypted: 0123456789ABCDEF
GlobalVar: 5
```

</details>

<details> 
<summary> IDA:</summary>
<img src="https://github.com/rondorondocat/ollvm-project/blob/master/tutorial_demo/res/demo.png"/>
</details>


### 1.控制流平坦化(FLA):

```bash
clang -mllvm -fla demo.c -o ./build/FLA
./build/FLA
``` 

<details> 
<summary> IDA:</summary>
<img src="https://github.com/rondorondocat/ollvm-project/blob/master/tutorial_demo/res/FLA.png"/>
</details>

### 2.虚假控制流(BCF):
```bash
clang -mllvm -bcf -mllvm -bcf_prob=50 -mllvm -bcf_loop=3 demo.c -o ./build/BCF
./build/BCF
``` 

<details> 
<summary> IDA:</summary>
<img src="https://github.com/rondorondocat/ollvm-project/blob/master/tutorial_demo/res/BCF.png"/>
</details>

### 3.指令替换(SUB):

```bash
clang -mllvm -sub -mllvm -sub_loop=2 demo.c -o ./build/SUB
./build/SUB
``` 

<details> 
<summary> IDA:</summary>
<img src="https://github.com/rondorondocat/ollvm-project/blob/master/tutorial_demo/res/SUB.png"/>
</details>

### 4.字符串混淆(SOBF): 
```bash
clang -mllvm -sobf demo.c -o ./build/SOBF
./build/SOBF
``` 

<details> 
<summary> IDA:</summary>
<img src="https://github.com/rondorondocat/ollvm-project/blob/master/tutorial_demo/res/SOBF.png"/>
</details>

### 5.基本块分割(SPLIT):
```bash
clang -mllvm -split -mllvm -split_num=5 demo.c -o ./build/SPLIT
./build/SPLIT
``` 
<details> 
<summary> IDA:</summary>
<img src="https://github.com/rondorondocat/ollvm-project/blob/master/tutorial_demo/res/SPLIT.png"/>
</details>

### 6.间接分支(IBR):
```bash
clang -mllvm -ibr demo.c -o ./build/IBR
./build/IBR
``` 

<details> 
<summary> IDA:</summary>
<img src="https://github.com/rondorondocat/ollvm-project/blob/master/tutorial_demo/res/IBR.png"/>
</details>

### 7.间接调用(ICALL):
```bash
clang -mllvm -icall demo.c -o ./build/ICALL
./build/ICALL
``` 

<details> 
<summary> IDA:</summary>
<img src="https://github.com/rondorondocat/ollvm-project/blob/master/tutorial_demo/res/ICALL.png"/>
</details>

### 8.间接全局变量():
```bash
clang -mllvm -igv demo.c -o ./build/IGV
./build/IGV
```

<details> 
<summary> IDA:</summary>
<img src="https://github.com/rondorondocat/ollvm-project/blob/master/tutorial_demo/res/IGV.png"/>
</details>

### 9.Annotate:
```bash
clang annotate.c -o ./build/Annotate
./build/Annotate
```

<details> 
<summary> IDA:</summary>
<img src="https://github.com/rondorondocat/ollvm-project/blob/master/tutorial_demo/res/Annotate.png"/>
</details>

## 参考与引用

[LLVM](https://github.com/llvm/llvm-project)

[obfuscator](https://github.com/obfuscator-llvm/obfuscator/tree/llvm-4.0?tab=readme-ov-file)