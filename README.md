# 项目目的
本项目基于C语言开发,旨在为CTFer编写C环境下的一个简单易用,且高效健壮的常用工具库,以简化exp的编写等,库预计包含以下部分:

- 一些常用的编码转换,例如Base系列等编码
- CTF中常见加密算法的加解密,并且支持自定义关键值
- 一些其他加密或编码转换,例如栅栏密码,摩斯电码等,甚至有Brainf**k的解释器
- 构建一套基本数据结构库,以减少重复造轮子

# 为什么要有这个项目
CTF比赛中,经常需要编写脚本代码来处理题目数据,生成flag,使用python语言一般即可满足大部分的需求,
但是,不是所有人都擅长(或喜欢)使用Python等语言高效解决这些问题,有人可能更愿意(希望)使用C语言解决问题.

本项目希望为CTFer提供一个基于C语言的工具库,让C语言也能够快速解决问题,同时希望能够提高工具的灵活性.

另一方面,C语言更为底层,操作起来更为自由,使用C语言作为基础也有可能使问题的解决更为灵活.

# 该项目有何特点
现在互联网上有着庞大的工具资源,任何一个领域都有着极其优秀的C语言工具库,
但是,这些库往往是为了解决更为专业严谨的问题,而不是为了解决CTF中的问题.

因此,这些库的接口往往会比较复杂,想要即写即用,往往需要花费大量的时间去阅读文档,学习使用方法.

另一方面,很多CTF题目基于的算法等并不是标准的,往往经过了一些变形,这就需要我们能够灵活的调整库的接口.
与其手动修改整个算法内部的逻辑,不如直接提供一个接口,让使用者可以自由的调整.

本项目并不追求异常卓越的性能,而是追求简单易用,高效健壮,并且尽可能的提供灵活的接口.
项目的编写者即为使用者,我希望能够让这个库更加符合CTFer的使用习惯.

欢迎广大CTFer提出宝贵意见,及时批评指正,共同完善这个项目.

# 安装
// 正在施工...

# 使用
// 正在施工...

# 功能支持列表
- 数据结构ADT
  [x] dynamic_array
  [x] list
  [x] queue
  [ ] stack
- 摘要算法Digest
  [ ] MD2
  [ ] MD3
  [x] MD4
  [x] MD5
  [x] SHA2-224
  [x] SHA2-256
  [x] SHA2-384
  [x] SHA2-512
  [x] SHA2-512/224
  [x] SHA2-512/256
  [ ] CRC32
  [ ] CRC64
- 编码转换Encode
  [x] Base64(支持编码表的自定义)
  [ ] Base32(支持编码表的自定义)
  [x] HEX_string to Byte_array
  [x] Morse Code
- 加密算法Encrypt
  [x] RC4(支持SBOX盒大小的自定义)
  [x] 国密 SM4
  [x] TEA,XTEA,XXTEA(支持各个关键key值的自定义)
  [ ] AES
  [ ] DES
  [ ] Blowfish
- 其他算法Other
  [x] Brain f**k 解释器
- 其他附加工具
  [x] 大小端序转换宏
  [x] 二进制位操作宏

# 如何贡献
- 主分支:main, 用于发布稳定版本(待发布)
- 开发分支:dev, 用于开发新功能

// 2024-3-22:
本项目正在初步开发阶段,main中无可行版本,仅放置README文档作为引导
请前往dev分支查看最新进展

# 联系我(们)
QQ交流群: 342568232