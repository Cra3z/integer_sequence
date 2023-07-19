# Integer_sequence
Implement for `std::integer_sequence` and related algorithms(minimum required c++ standard: C++11)
实现了`std::integer_sequence`及相关模板并进行了扩充(要求c++11或更新的c++标准)
# Examples
* 直接包含all.hpp这个头文件即可
 
* `std::integer_sequence`与`ccat::integer_sequence`之间的转换
```c++
using ccat_seq1 = ccat::integer_sequence<int, 23, 56, -34, 11>;

//使用模板别名`ccat::to_std_integer_sequence_t`或`ccat::integer_sequence`的别名成员`to_std`将`ccat::integer_sequence`转换成`std::integer_sequence`
using std_seq1 = ccat_seq1::to_std; // std::integer_sequence<int, 23, 56, -34, 11>
using std_seq2 = ccat::to_std_integer_sequence_t<ccat_seq1>; // std::integer_sequence<int, 23, 56, -34, 11>

//使用模板别名`ccat::from_std_integer_sequence_t`将`std::integer_sequence`转换成`ccat::integer_sequence`
using ccat_seq2 = ccat::from_std_integer_sequence_t<std_seq1>; // ccat::integer_sequence<int, 23, 56, -34, 11>
```
* 快速生成integer_sequence
```c++
using seq1 = ccat::make_integer_sequence<int, 10>; // ccat::integer_sequence<int, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9> 
using seq2 = ccat::repeat<12, int, 1>; // ccat::integer_sequence<int, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1>
```
* 获取integer_sequence的和、积
```c++
using seq = ccat::integer_sequence<int, 1, 2, 3, 4>;
constexpr int sum = ccat::sum<seq1>; // 1+2+3+4=10
constexpr int prod = ccat::; // 1x2x3x4=24
```
* 获取最值
```c++
// integer::sequence的最值
using seq = ccat::integer_sequence<int, 11, 56, -110, 234>;
constexpr int m = ccat::min<seq>; // -110
constexpr int M = ccat::max<seq>; // 234
// 多个类型中的最值(根据它们的`sizeof`)
using m_t = ccat::min_type_of_t<int, char, std::string>; // `char`
using M_t = ccat::max_type_of_t<int, char, std::string>; // `std::string`
```
* 运算: 目前仅支持integer_sequence的合并, 对应相乘, 对应相加, 对应相减
```c++
using seq1 = ccat::integer_sequence<int, 1, 2, 3, 4>;
using seq2 = ccat::integer_sequence<int, 5, 6, 7, 8>;
using concat_result = ccat::concat<seq1, seq2>; // ccat::integer_sequence<int, 1, 2, 3, 4, 5, 6, 7, 8>
using add_result = ccat::add<seq1, seq2>; // ccat::integer_sequence<int, 6, 8, 10, 12>
using subtract_result = ccat::subtract<seq1, seq2>; // ccat::integer_sequence<int, -4, -4, -4, -4>
using multi_result = ccat::multiply<seq1, seq2>; // ccat::integer_sequence<int, 5, 12, 21, 32>
```
