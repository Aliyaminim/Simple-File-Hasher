# Simple-File-Hasher
This program can hash a single binary file or multiple binary files concurrently using multiprocessing. Each file is processed in a separate child process, and then their hashes are combined into a single overall hash using XOR operation.

## How to build
```bash
git clone https://github.com/Aliyaminim/Simple-File-Hasher.git
cd Simple-File-Hasher
cmake -S ./ -B build/
cd build/
cmake --build .
```

## How to run the program
```bash
./driver [file]
#or
./driver_multi [file1] [file2] ...
```

## How to generate a test and run it
You can generate a custom test by defining size of file and ratio of zero elements of 4 bytes in it.
```bash
./test/generator [size_in_elements_of_4bytes] [zero_elements_ratio]
#[filename] is generated
./driver [filename]
```

## How to test the program 
There're two options to test the program.

1) Test hashing a single file
2) Test hashing multiple files by specifying the number of files to combine (n <= 20)
```bash
cd ../test
bash testing.sh
#or
bash testing_multi.sh [n]
```
