#!/bin/bash

# (()) 为bash的类似计算符的玩意，然后$UID是判断当前的用户是谁？若是root则$为0
# if [ $UID == 0 ]; then
#     echo Hello Root user
# else
#     echo Hello user
# fi

# n1=3
# n2=4
# let n=n1+n2
# echo $n
# n=$[n1+n2]
# echo $n

# echo "scale=2;22/7" | bc
# n1=12
# echo '$n1'

# echo  "obase=10;ibase = 1;10" | bc 

function tmd(){
    a=(12 12 1 1 1)
    b=3
    if ((${a[b]} == 1))
    then    echo "a[b] = 1"
    else    echo "a[b] != 1"
    fi
}

function tt(){
    
}
tmd
