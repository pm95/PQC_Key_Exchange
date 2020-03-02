echo "Compiling Bob ... "

gcc Bob.c -lm -static ../PQCrypto-SIDH/lib434/libsidh.a -o bob && ./bob
