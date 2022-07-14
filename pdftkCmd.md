合并PDF：  

```bash
pdftk 1.pdf 2.pdf 3.pdf cat output 123.pdf
```

或者 (使用通配符):
```bash
pdftk *.pdf cat output combined.pdf
```


把多个PDF的不同页面组合成一个新的PDF文档(将one.pdf的前7页，two.pdf的前5页，one.pdf的第8页按先后顺序合并成combined.pdf)
```bash
pdftk A=one.pdf B=two.pdf cat A1-7 B1-5 A8 output combined.pdf
```


旋转PDF的第一页为顺时针90度（向东）（其余页方向不变，2-end表示第2页到最后一页）
```bash
pdftk in.pdf cat 1E 2-end output out.pdf
```

旋转PDF的第一页为逆时针（向西）90度，只提取第一页
```bash
pdftk in.pdf cat 1W output out.pdf
```
选择所有PDF页面180度：
```bash
pdftk in.pdf cat 1-endS output out.pdf
```
使用128强度加密PDF（安全模式，只读）
```bash
pdftk in.pdf output mydoc.128.pdf owner_pw foopass
```
同上，同时给PDF加上访问密码（会弹出一个密码输入框）
```bash
pdftk in.pdf output mydoc.128.pdf owner_pw foo user_pw baz
```
同上，但是运行打印：
```bash
pdftk in.pdf output mydoc.128.pdf owner_pw foo user_pw baz allow printing
```
解密PDF文档(foopass替换成pdf的owner_pw密码)：注意：前提是你得知道pdf的密码所以此功能只是解除所有者的密码，使阅读者不需要输密码
```bash
pdftk secured.pdf input_pw foopass output unsecured.pdf
```
合并两个PDF文档，其中一个是加密的，但最终文档不加密：
```bash
pdftk A=secured.pdf mydoc.pdf input_pw A=foopass cat output combined.pdf
```
解压PDF流，以便文本编辑：（不清楚是干什么用的）
```bash
pdftk mydoc.pdf output mydoc.clear.pdf uncompress
```
压缩PDF：
```bash
pdftk mydoc.pdf output mydoc.clear.pdf compress
```

修复PDF文档
```bash
pdftk broken.pdf output fixed.pdf
```
分解成单页（文件名以pg_开头）
```bash
pdftk mydoc.pdf burst
```
报告PDF信息，输出到文本
```bash
pdftk mydoc.pdf dump_data output report.txt
```


  
  
