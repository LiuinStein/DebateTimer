
# 山东理工大学辩论赛计时系统

开发这个程序的原因是学校法学院经常举行辩论赛，原先使用的计时器软件因为辩论赛规则改变了不能用了，然后要我给他们再开发一个  
  
原先的计时器软件服役已经有几年的时间了，据我分析是使用的Dephi语言编写的（二进制打开文件可以看到底部的XML文档中包含DephiApplication字样）  
  
原来的计时器制作的的确不好，时间和规则都是在程序里面写死的，如果辩论赛规则发生了变化，那么就要重新改动程序源代码，重新编译  

我制作的这个辩论赛计时系统可以自定义规则，同时可以将规则导出为json文件，下次使用的时候也可以从json文件导入规则，并且带有单独的图形化界面用来进行规则的改动，在解析json方面，使用基于MIT协议开源的jsoncpp库  

辩论赛的开始计时窗体，所有的控件和文字都会依据屏幕大小来自动变换到合适的位置及合适的大小，输出字体的大小依据需要输出的行数（时钟个数）及窗体的高度决定，控件的大小及位置依据窗体的高度和宽度的固定百分比例来确定。  
  
