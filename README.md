###  初学大数据的demo 
MPI文件夹中包含了一些常见的MPI函数的用法和几个简单的应用，Hadoop文件夹中包含HDFS的java API调用，简单的Mapreduce程序的编写。
#### MPI
- mpi_array_sort.c / 2.c  对数组进行并行比较，得到最大值。
将数组的不同部分分给不同的进程，每个进程得出部分的最大值，然后汇总到根进程，进行判断，最后得到整个数组的最大值。
- mpi_sinx.c 并行求sinx的积分
采用分割法，将区域分成很多份，每个进程再对分到的区域进行细分然后计算，最后汇总到根进程。
- mpi_send_recv.c  一个进程发，另一个进程接收数据。
- mpi_gather.c 将数据从多个进程收集到一个进程。
- mpi_scatter.c  数据散播函数
- mpi_broadcast.c  聚合通信广播函数
- parrel_work.c 问题描述[戳这里](https://blog.csdn.net/sinat_22336563/article/details/70229243)
#### Hadoop
 HDFS
- LocalToHDFS.java 本地文件上传到HDFS
- Multiupload.java 将本地的文件夹上传至HDFS
-  Write.java 		在HDFS中创建新文件
- iris.data： 鸢尾花数据集，测试之用。

 MapReduce
 - WordCount.java 经典例子，不多解释。
 - Score.java 学生成绩统计。
 统计N个班级不同分数段的人数，输出每个班的成绩分布统计和N个班级总的成绩分布统计情况。
 学生数据用ran.py生成，格式为"学号 姓名 成绩"。使用两个mapreduce，开启两个job，
 第一个job结束以后开始启动第二个job。
 
 ### ...
 仅供参考，不当之处，欢迎指出。
 

