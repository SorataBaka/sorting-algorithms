# ソートプログラム

## セットアップ

最初に、次のコマンドを一つずつ実行してください。これを実行すると色々出力されたコマンドファイルをそのままで実行できる。

```
$ make
$ cd bin
$ export PATH=$(pwd):$PATH
```

ソートプログラムを実行するとき

```
$ bucket assets/data1.dat
等
```

## コマンドライン

コマンドラインの使い方について

```
Usage: algcomp [file1 file2 ...] [--out <output_file>] [--alg <algorithm>]

Positional arguments:
  file1 file2 ...        One or more input files to process

Options:
  --out <output_file>    Write output to <output_file>
  --sortby <field>       Sort result table by one of: file, method, length, time, memory
  --alg <algorithm>      Choose sorting algorithm to use
                         Available algorithms:
                           all     - Run all algorithms
                           bubble  - Bubble Sort
                           bucket  - Bucket Sort
                           count   - Counting Sort
                           insert  - Insertion Sort
                           quick   - Quick Sort
                           shaker  - Shaker Sort

Examples:
  algcomp input.txt --out result.txt
  algcomp input.txt --alg quick
  algcomp input.txt --alg all --out sorted.txt
```
