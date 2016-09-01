#!/bin/bash

files=("assert" "ctype" "errno" "float" "limits" "locale" "math" "setjmp" "signal" "stdarg" "stddef" "stdio" "stdlib" "string" "time")


# 很危险，执行后会清空整个文件
# for file in ${files[*]};
# 	do
# 		> $file.md;
# 		echo \# $file.h > $file.md;
# done;
