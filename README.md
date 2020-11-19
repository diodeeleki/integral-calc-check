# integral-calc-check(icc)
符号あり/符号なし整数型両対応のオーバーフローアンダーフローチェック用ライブラリ  
本ライブラリはヘッダオンリーであり  
テンプレート関数のみで構成されている  
内部でコンセプトを使用しているのでc++20以降でビルドしなければならない。

## グローバル定数一覧
---
|名前|型|ヘッダ|備考|
|---|---|---|---|
|icc::success|icc::Result|<icc/icc.hpp>|オーバーフローもアンダーフローも発生しない場合返される値|
|icc::overflow|icc::Result|<icc/icc.hpp>|オーバーフローが発生する場合返される値|
|icc::underflow|icc::Result|<icc/icc.hpp>|アンダーフローが発生する場合返される値|

## 関数一覧
本ライブラリで実装されている関数はすべてicc::Resultが  
戻り値の型で引数は2つあり引数の型は共に符号あり/符号なし整数型である。

|名前|ヘッダ|備考|
|---|---|---|
|icc::Result icc::add(const Type l_arg, const Type r_arg)|<icc/icc.hpp>|加算を行う際のオーバーフローアンダーフローチェック|
|icc::Result icc::sub(const Type l_arg, const Type r_arg)|<icc/icc.hpp>|減算を行う際のオーバーフローアンダーフローチェック|
|icc::Result icc::mul(const Type l_arg, const Type r_arg)|<icc/icc.hpp>|乗算を行う際のオーバーフローアンダーフローチェック|

除算ではオーバーフローもアンダーフローも発生しないので実装していない。

## インストール方法
---
```terminal
mkdir build
cd build
cmake ..
sudo make install
```

インストール先を指定したいのなら下記のように端末に書き込めば良い。

```terminal
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=[インストール先のパス]
sudo make install
```

## プロジェクトディレクトリ内に組み込んで使う場合
---
```
.
├── CMakeLists.txt
├── lib
│   └── icc <-本ライブラリのrootフォルダ
└── main.cpp
```
上記のようなフォルダ構造で本ライブラリを使用して使う場合
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/icc)  
で本ライブラリのrootディレクトリのcmakeスクリプトを呼び出して  
target_link_libraries(a.out icc)で生成物と紐付ければ良い。

```cmake
cmake_minimum_required(VERSION 3.16.3)
project(hoge CXX)
    
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/simple_iterator)

add_executable(a.out ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(a.out icc)
```
そして#include <icc/icc.hpp>でインクルードすれば使えるようになる。
```c++
#include <iostream>
#include <limits>
#include <icc/icc.hpp>

int main()
{
    int a = std::numeric_limits<int>::max();
    int b = 1;
    
    auto res = icc::mul(a, b);
    
    switch(res)
    {
        case icc::success:
            std::cout << "success" << std::endl;
            break;
            
        case icc::overflow:
            std::cout << "overflow" << std::endl;
            break;
            
        case icc::underflow:
            std::cout << "underflow" << std::endl;
            break;
    }
    
    return 0;
}
```

## インストールして使う場合
---
```
.
├── CMakeLists.txt
├── build
└── main.cpp
```
上記のようなフォルダ構造でiccライブラリを使用して使う場合  
iccライブラリをインストールした後に  
下記のようにCMakeLists.txtではfind_package(icc)でiccライブラリを探し、  
target_link_libraries(a.out INTERFACE icc)で生成物と紐付ければ良い。
```cmake
cmake_minimum_required(VERSION 3.16.3)
project(hoge CXX)
    
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(icc)

add_executable(a.out ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(a.out INTERFACE icc)
```
そして#include <icc/icc.hpp>でインクルードすれば使えるようになる。
