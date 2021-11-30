#! /bin/bash   
# linux的51单片机
function main() {
	file=$1	
	sdcc "$1.c"

	packihx "${file}.ihx" > "${file}.hex"
	rm "${file}.asm" "${file}.map" "${file}.mem" "${file}.rel" "${file}.rst" "${file}.lk" "${file}.sym" "${file}.ihx" "${file}.lst"
	sudo ./stcflash.py "${file}.hex"
	mv "${file}.hex" hex/"${file}.hex"
	return	
}
main $1