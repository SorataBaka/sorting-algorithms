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
$ algcomp assets/data1.dat ...
等
```

## コマンドライン

コマンドラインの使い方について

```
Usage: algcomp [file1 file2 ...] [--out <output_file>] [--alg <algorithm>]

Positional arguments:
  file1 file2 ...        One or more input files to process

Options:
Usage: algcomp [file1 file2 ...] [--out <output_file>] [--alg <algorithm>] [--sortresult <field>] [--limit <N>]

Positional arguments:
  file1 file2 ...         One or more input files to process

Options:
  --out <output_file>     Write sorted output to a file named <algorithm>-<output_file>
  --alg <algorithm>       Choose sorting algorithm to use. Available algorithms:
                            all      Run all algorithms
                            bubble   Bubble Sort
                            bucket   Bucket Sort
                            count    Counting Sort
                            insert   Insertion Sort
                            quick    Quick Sort
                            shaker   Shaker Sort
  --sortresult <field>    Sort result table by one of the following:
                            file     Sort by file name
                            method   Sort by sorting method
                            length   Sort by data length
                            time     Sort by execution time
                            memory   Sort by memory usage
  --limit <N>             Only read at most N numbers from each input file
  --help                  Show this help message and exit

Examples:
  algcomp input.txt --out result.txt
  algcomp input1.txt input2.txt --alg quick
  algcomp input.txt --alg all --out sorted.txt --sortresult time --limit 1000
```
