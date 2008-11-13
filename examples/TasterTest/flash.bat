avrdude -F -p atmega168 -P com1 -c stk500 -b 2400 -q -V -v -U flash:w:test168.hex
