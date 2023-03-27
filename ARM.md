1. X86 和 ARM 都是一种 CPU 指令集架构。其中 Intel 和 AMD 都是 X86 架构 CPU 的生产厂商，在 PC 端拥有霸主低位；ARM 公司提供授权服务，大多手机厂商都是使用 ARM 公司的 ARM 指令集架构，在移动端拥有霸主低位。

2. 每一种指令集架构都对应自己的<u>汇编器</u>，汇编语言可以使用 CPU 的<u>指令集</u>进行编程。

3. 由于 CPU 架构的不同，在 X86 上运行的二进制包是不能直接运行在 ARM 上的，因为二进制包已经被编译成使用某一种指令集的机器语言，不具有可移植性；但是如果拥有<u>只用高级语言</u>（高级语言都掩盖了指令集的特性，大部分情况下开发者都不需要知道底层是什么指令集）编写的源码包，就可以在 X86 或者 ARM 上进行编译运行。

4. 为什么 ARM 在 PC 端的生态这么贫瘠……我想主要原因也是因为 X86 在 PC 端的霸主地位原因，厂商都根据 X86 架构来进行软件设计。

5. 计算机抽象层的基础是原子，这些原子结合形成硅这样的材料，然后用来制造微小的「晶体管」。这些晶体管就像开关一样，通过施加电流或电压信号来控制开或关状态。通过将开关按照特定的排列方式连接在一起，就形成了用来执行计算的所谓基本布尔逻辑运算符：与、或、非。例如，一个开关本身可以将 1 转换为 0，在其输出端，称作逻辑"非"或反相运算符；两个串联开关组成一个逻辑"与"运算符。如果把开关并联起来，就会在输出端得到逻辑"或"运算符。这些开关排列就叫做逻辑门。我们现在可以将 1 和 0 组织起来或抽象成逻辑语言，这种语言比物理语言和电子流更容易理解。用晶体管作为开关，将一个开关的输出端与另一个的输入端相连，就能构建成各种逻辑电路或「功能块」。这些功能块采用的形式包括加法器、多路复用器、解码器、锁存器、触发器、寄存器、计数器、等等。抽象拥有不可思议的力量。如大家所料，将功能块链接在一起可以实现更复杂的逻辑功能。我们可以使用他们构建自定义执行单元来执行特定的计算。例如，CPU 中最重要的执行单元之一是算术逻辑单元，简称 ALU。<u>设计整个 CPU 归根结底额就是构建多个「专用处理单元」</u>，并用多种方式将它们连接起来，从而实现复杂的计算。将这些处理单元组成一种设计，从内存中获取指令、解码指令、执行指令，并将结果存回内存，这就是我们所说的「微架构」，或者在硬件中实现架构实例化。

   那么如何从硬件到软件呢？当然是再添加一个抽象层——指令集架构。指令集架构或 ISA 是一组指令，定义在硬件中可以执行哪些类型的操作。ISA 就是计算机的语言。就像英语或西班牙语是语言一样，大多数语言都有字典，字典向使用这些语言交流的人们描述了单词、格式、语法和含义。ISA 是计算机的抽象模型，有时也成为「架构」或「计算机架构」。ISA 描述了内存模型、支持的数据类型、寄存器和机器代码的行为，即 CPU 必须执行的 0、1 序列。你们可能听说过几类 ISA，比如 x86、ARM 或 MIPS。ISA就像连接软件和硬件的桥梁。在软件方面，编译器使用 ISA 将用 C、Perl 或 Java 等高级语言编写的代码转换为机器代码指令，也就是 CPU 可以处理的语言。ISA 就是字典，描述了指令、数据类型以及遵循这个 ISA 的 CPU 必须执行的格式。<u>因此，程序员通常可以忽略 ISA，而专注于编程语言能实现哪些功能</u>。就硬件而言，在设计 CPU 微架构时，ISA 用作设计规范，告诉工程师它需要执行哪些操作。有了这一抽象层，ISA 中的指令就与实现彼此独立。<u>这意味着，即使不同的公司创造了不同的微架构设计，也可以运行基于相同 ISA 的代码</u>。计算机架构师会通过扩展指令集来持续发展 ISA。就像经常往字典里添加新词一样。创造新指令往往是为了更高效地执行某些操作，并利用微架构中的新处理元件。这些 ISA 扩展可以为特定排列的处理元件简化操作，以此提高 CPU 的性能。现在 CPU 支持数千条不同的指令，但其中很多都与加、减、乘等算术运算，与、或、非等逻辑运算，加载、存储、移动等内存操作，以及分支等流控制有关。指令通常由一个操作码和一些操作数组成，操作码规定了要执行的操作数，比如 ADD；操作数指定了要运算的数据，比如将寄存器 X 中的 A与内存位置 Y 中的 B 相加。ISA 指令往往还包括额外的数据位，这些数据位为 CPU 提供更多与操作相关的信息。CPU 根据其微架构，以高效的方式来解码并执行指令。当然，这些只是极其简单地介绍了指令集架构，必须要知道的是，现在 ISA 的复杂程序远远超过这个简短视频中的解释。ISA 是现代 CPU 设计中最重要的部分之一，因为它是连接软件和硬件的关键环节，能在各种 CPU 微架构上实现高效、高性能的计算和无缝的软件体验。

6. 采用 ARM 核（RISC）的处理器多种多样，面向不同领域的不同应用，针对特定应用可以设计出相应的「微架构」来加速应用程序的执行。